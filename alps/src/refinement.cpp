//
//  refinement.cpp
//  ALPS
//
//  Created by Xujie Si on 11/7/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#include "query.h"
#include "config.hpp"

#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <iterator>
#include <functional>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstdlib>

#include <z3++.h>

namespace ALPS {
  
  void QueryEngine::eliminate_and_refine2(std::vector<DatalogProgram>& A,
                                          std::vector<DatalogProgram>& B, bool positive,
                                          std::vector<int>& Q, std::vector<std::vector<int> >& Qs) {
    
    std::chrono::steady_clock::time_point processA_begin = std::chrono::steady_clock::now();
    
    std::vector<DatalogProgram> dps;
    int remove_ct = 0;
    
    long long longest_run = 0;
    
    for (DatalogProgram& x : A) {
      std::chrono::steady_clock::time_point _b = std::chrono::steady_clock::now();
      auto res = testDerivation(x, positive, Q, Qs);
      if (res.first && ! res.second) {
        dps.push_back(std::move(x));
      } else {
        ++remove_ct;
        
        // cancel vote
        for(auto& it : vote_stats) {
          it.second.erase( x.prog_id );
        }
      }
      
      std::chrono::steady_clock::time_point _e = std::chrono::steady_clock::now();
      long long t = std::chrono::duration_cast<std::chrono::milliseconds>(_e - _b).count();
      if(longest_run < t) {
        longest_run = t;
      }
    }
    
    A = std::move(dps);
    
    std::chrono::steady_clock::time_point processA_end = std::chrono::steady_clock::now();
    std::cout << "(Time_Measure) eliminate_refine2_phaseA takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(processA_end - processA_begin).count()
    << " ms, longest_run: " << longest_run << " max_threads: " << A.size() << "\n";
    
    longest_run = 0;
    std::chrono::steady_clock::time_point processB_begin = std::chrono::steady_clock::now();
    
    
    int refine_ct = 0;
    for (DatalogProgram& x : B) {
      std::chrono::steady_clock::time_point _b = std::chrono::steady_clock::now();
      
      //bool debug = false;
      //if(keep_track.count(x.prog_id)) {
      //    std::cout <<"Attentation (debug):\n" << dp_ptr->str(x,false) << "\n";
      //    debug = true;
      //}
      
      auto res = testDerivation(x, positive, Q, Qs);
      if (res.first && ! res.second) {
        dps.push_back(std::move(x));
      }
      else{
        int ins = 0;
        for(auto& pr : x.state) {
          ins += pr.second.size();
        }
        bool debug = (ins == 3);
        debug = false;
        
        if(debug){
          std::cout << "refine program: \n" << dp_ptr->str(x,false) << std::endl;
          std::cout << "status: " << ( res.first ? "derive positive" : " dont derive positive" )
          << ";  " << (res.second ? "derive negative" : "dont derive negative") << std::endl;
        }
        
        // cancel vote
        for(auto& it : vote_stats) {
          it.second.erase( x.prog_id );
        }
        
        std::queue<DatalogProgram> Queue;
        Queue.push(std::move(x));
        
        while (!Queue.empty()) {
          ++refine_ct;
          DatalogProgram p ( std::move(Queue.front() ));
          Queue.pop();
          
          if(debug) {
            std::cout << dp_ptr->str(p,false) << std::endl;
          }
          
          bool specialize = !positive;
          std::vector<DatalogProgram> vs = dp_ptr->refineProgWithTarget(p,
                                                                        specialize, Q[0]);
          for (DatalogProgram& y : vs) {
            
            //try to vote
            if(!execute(y)) {
              continue;
            }
            
            
            auto res = testDerivation(y, positive, Q, Qs);
            
            if(debug) {
              std::cout << dp_ptr->str(y,false) << std::endl;
              std::cout << "status: " << ( res.first ? "derive positive" : " dont derive positive" )
              << ";  " << (res.second ? "derive negative" : "dont derive negative") << std::endl;
              
            }
            
            if(positive) {
              if(res.second) {
                // ignore, cancel vote
                for(auto& it : vote_stats) {
                  it.second.erase( y.prog_id );
                }
                
              }
              else if(res.first) {
                dps.push_back(std::move(y));
              }
              else{
                // cancel vote, keep refining
                for(auto& it : vote_stats) {
                  it.second.erase( y.prog_id );
                }
                
                Queue.push(std::move(y));
              }
            }
            else{
              if(res.first) {
                if(res.second){
                  // cancel vote, keep refining
                  for(auto& it : vote_stats) {
                    it.second.erase( y.prog_id );
                  }
                  
                  Queue.push(std::move(y));
                }
                else{
                  dps.push_back(std::move(y));
                }
              }
              else{
                // ignore, cancel vote
                for(auto& it : vote_stats) {
                  it.second.erase( y.prog_id );
                }
              }
            }
          }
        }
      }
      
      std::chrono::steady_clock::time_point _e = std::chrono::steady_clock::now();
      long long t = std::chrono::duration_cast<std::chrono::milliseconds>(_e - _b).count();
      if(longest_run < t) {
        longest_run = t;
      }
    }
    
    B = std::move(dps);
    
    std::cout << "removed_ct=" << remove_ct << ", refine_ct = " << refine_ct
    << ", size: " << dp_ptr->Gs.size() << std::endl;
    
    std::chrono::steady_clock::time_point processB_end = std::chrono::steady_clock::now();
    std::cout << "(Time_Measure) eliminate_refine2_phaseB takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(processB_end - processB_begin).count()
    << " ms, longest_run: " << longest_run << " max_threads: " << B.size() << "\n";
    
  }

  
  void QueryEngine::work_refinement() {
    /*
     DatalogProgram prog( dp_ptr );
     prog.state[0] = {10,11};
     prog.state[1] = {6};
     dp_ptr->Gs.push_back( std::move(prog) );
     
     for(auto & p : dp_ptr->Gs) {
     vote_stats.clear();
     execute(p);
     bool status = validate_with_full_IDBs();
     
     showVotesAndGS();
     
     if(status) {
     std::cout << "correct candidate: " << std::endl;
     std::cout << dp_ptr->str(p,false) << std::endl;
     }
     }
     */
    
    std::chrono::steady_clock::time_point refinement_begin = std::chrono::steady_clock::now();
    
    z3::expr_vector and_pos_vec(cm_ptr->C);
    z3::expr_vector or_neg_vec (cm_ptr->C);
    
    std::vector<std::vector<int>> pos_Qs;
    std::vector<std::vector<int>> neg_Qs;
    
    
    and_pos_vec.push_back( cm_ptr->C.bool_val(true) );
    or_neg_vec.push_back( cm_ptr->C.bool_val(false) );
    
    int round = 0;
    
    long large_size = dp_ptr->Gs.size();
    long small_size = dp_ptr->Ss.size();
      
    while (true) {
      ++round;
      
      std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
      
      //std::vector<int> Q = random_mode ? random_pick_old() : execute_one_round();
      std::vector<int> Q = random_mode ? random_pick() : query_one_round();
      
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Round " << round << " execution takes "
      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
      << " ms.\n";
      
      if(Q.size() == 0) {
        break;
      }
      
      std::chrono::steady_clock::time_point before_refine = std::chrono::steady_clock::now();
      
      bool positive = dp_ptr->ask(Q);
      
      
      std::cout << (positive ? "positive" : "negative")
      << " answer for Question: " << dp_ptr->nice_display(Q)
      << std::endl;
      
      //std::copy(Q.begin(), Q.end(), std::ostream_iterator<int>(std::cout, ", ") );
      //std::cout << std::endl;
      
      if (positive) {
        
        pos_Qs.push_back(Q);
        
        z3::expr q = convert_question(Q);
        and_pos_vec.push_back(q);
        z3::expr and_qs = z3::mk_and(and_pos_vec);
        z3::expr or_qs = z3::mk_or(or_neg_vec);
        
        //z3::expr qs = and_qs && (!or_qs);
        
        std::cout << "before elimination & refinement, Gs.size= "
        << dp_ptr->Gs.size() << ", Ss.size= " << dp_ptr->Ss.size()
        << std::endl;
        
        std::cout << "Goal : will remove some Gs and generalize some Ss" << std::endl;
        eliminate_and_refine2(dp_ptr->Gs, dp_ptr->Ss, true, Q, neg_Qs);
        
        std::cout << "after elimination & refinement, Gs.size= "
        << dp_ptr->Gs.size() << ", Ss.size= " << dp_ptr->Ss.size()
        << std::endl;
        
      } else {
        neg_Qs.push_back(Q);
        
        z3::expr q = convert_question(Q);
        or_neg_vec.push_back(q);
        z3::expr or_qs = z3::mk_or(or_neg_vec);
        z3::expr and_qs = z3::mk_and(and_pos_vec);
        
        //z3::expr qs = and_qs && (!or_qs);
        
        std::cout << "before elimination & refinement, Gs.size= "
        << dp_ptr->Gs.size() << ", Ss.size= " << dp_ptr->Ss.size()
        << std::endl;
        
        
        std::cout << "Goal : will remove some Ss and specialize some Gs" << std::endl;
        
        //eliminate_and_refine( dp_ptr->Ss, dp_ptr->Gs, false, and_qs, or_qs, Q);
        eliminate_and_refine2(dp_ptr->Ss, dp_ptr->Gs, false, Q, pos_Qs);
        
        std::cout << "after elimination & refinement, Gs.size= "
        << dp_ptr->Gs.size() << ", Ss.size= " << dp_ptr->Ss.size()
        << std::endl;
        
      }
        
        if (large_size == dp_ptr->Gs.size() && small_size == dp_ptr->Ss.size()) {
            break;
        } else {
            large_size = dp_ptr->Gs.size();
            small_size = dp_ptr->Ss.size();
        }
      
      std::chrono::steady_clock::time_point after_refine = std::chrono::steady_clock::now();
      
      std::cout << "Round " << round << " refinement takes "
      << std::chrono::duration_cast<std::chrono::milliseconds>(after_refine - before_refine).count()
      << " ms.\n";
      
      std::cout << "Round " << round << " overall takes "
      << std::chrono::duration_cast<std::chrono::milliseconds>(after_refine - start).count()
      << " ms.\n";
      
      //break;
    }
    
    
    std::cout << "converged at round: " << round << std::endl;
    
    std::cout << "remaining general programs: " << dp_ptr->Gs.size() << std::endl;
    int ct = 0;
    for(const DatalogProgram& x : dp_ptr->Gs) {
      std::cout << "\n\n" << dp_ptr->str(x);
      ++ct;
      //if(ct+1 >= 3) {
      //  std::cout << "\n\n...(" << (dp_ptr->Gs.size() - 3) <<" more)\n\n";
      //  break;
      //}
    }
    
    std::cout << "remaining specific programs: " << dp_ptr->Ss.size() << std::endl;
    ct = 0;
    for(const DatalogProgram& x : dp_ptr->Ss) {
      std::cout << "\n\n" << dp_ptr->str(x);
      ++ct;
      //if(ct+1 >= 3) {
      //  std::cout << "\n\n...(" << (dp_ptr->Ss.size() - 3) <<" more)\n\n";
      //  break;
      //}
    }
    
#ifdef LOG_REFINEMENT_LAYER_GRAPH
    std::set<int> greens;
    for(const DatalogProgram& x : dp_ptr->Gs) greens.insert(x.prog_id);
    for(const DatalogProgram& x : dp_ptr->Ss) greens.insert(x.prog_id);
    draw_layer_graph(greens);
#endif
    
    
    std::chrono::steady_clock::time_point refinement_end = std::chrono::steady_clock::now();
    
    std::cout << "Refinement takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(refinement_end - refinement_begin).count()
    << " ms.\n";
    
  }

  
  void QueryEngine::work() {
    const Configuration& Config = Configuration::getConfig();
    
    std::chrono::steady_clock::time_point work_begin = std::chrono::steady_clock::now();
    
    // Phase-I:  examine IDB rules
    if(Config.K > 1){
      //std::cout << "will examine IDBTRs ...\n";
      
      // stage-search will have better way to get rid of useless programs (including single rule program)
      dp_ptr->examine_each_IDBTR(this);
    }
    
    
    // use warm-up mechanism instead of brute-force initialization
    {
    }
    
    // Phase-II: initialize most general and most specific programs
    {
      //std::chrono::steady_clock::time_point initGS_begin = std::chrono::steady_clock::now();
      //std::cout << "\n\nwill initGS ... \n";
      dp_ptr->initGSX();
      
      // std::chrono::steady_clock::time_point initGS_end = std::chrono::steady_clock::now();
      // std::cout << "(Time_Measure) initGSX takes "
      // << std::chrono::duration_cast<std::chrono::milliseconds>(initGS_end - initGS_begin).count()
      // << " ms, longest_run: -1 max_threads: 1 \n";
    }
    
    
    // Phase-III: initial votes
    {
      // Now we use the "at most twice" mechanism
      // execute only once at the beginning
      
      initial_execution(dp_ptr->Gs);
      initial_execution(dp_ptr->Ss);
    }
    
    // Phase-IV: start refinement
    {
      //if(dp_ptr->enableX) {
      //  work_baseline();
      //}
      //else{
      work_refinement();
      //}
    }
    
    std::chrono::steady_clock::time_point work_end = std::chrono::steady_clock::now();
    
    std::cout << "End-to-End takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(work_end - work_begin).count()
    << " ms.\n";
    
  } // end of  QueryEngine::work()

} // end of namespace ALPS
