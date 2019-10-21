//
//  stage_search.cpp
//  ALPS
//
//  Created by Xujie Si on 11/7/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#include "query.h"


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


namespace  ALPS {
  
  // -----------------------------------------------
  // --------------------  Stage Search ------------
  // -----------------------------------------------
  
  void filter_out_inactive(std::vector<DatalogProgram>& committee){
    std::vector<DatalogProgram> new_committee;
    for(DatalogProgram& prog : committee) {
      if(prog.prog_id > 0) {
        new_committee.push_back(std::move(prog));
      }
    }
    
    committee = std::move(new_committee);
  }
  
  void QueryEngine::print_out_programs(std::vector<DatalogProgram>& progs) {
    for(DatalogProgram& x : progs) {
      if(x.prog_id > 0) {
        std::cout << dp_ptr->str(x,false) << "\n";
      }
      else{
        std::cout << "<<<inactive program>>>\n";
      }
    }
  }
  
  int QueryEngine::count_invented_rules(DatalogProgram& prog) {
    int ct = 0;
    for(auto & pr : prog.state) {
      if(dp_ptr->invent_idbs.find(pr.first) != dp_ptr->invent_idbs.end()) {
        ++ct;
      }
    }
    
    return ct;
  }
  
  void QueryEngine::cancel_vote(DatalogProgram& new_prog) {
    // cancel vote effects
    for(auto& it : vote_stats) {
      it.second.erase( new_prog.prog_id );
    }
  }
  
  void QueryEngine::naive_execute(const DatalogProgram& prog ) {
    FixedPoint fp = prepare(prog);
    queryIDBs(fp);
  }
  
  std::vector<DatalogProgram> QueryEngine::exec_programs(std::vector<DatalogProgram>& progs){
    
    std::vector<DatalogProgram> derive_empty;
    
    for(DatalogProgram& p : progs) {
      vstatus = false;
      naive_execute(p);
      
      if(!vstatus) {
        derive_empty.push_back( std::move(p) );
      }
    }
    
    std::cout << "exec_programs : " << progs.size()
    << ", filter out inactive ones (derving empty): " << derive_empty.size() << "\n";
    
    filter_out_inactive(progs);
    return derive_empty;
  }
  
  std::vector<int> QueryEngine::select_question(const int size){
    int best = 1<<30;
    
    int skip_invent_ct = 0;
    int empty_ct = 0;
    std::set<int> votes;
    std::vector<int> question;
    for (auto pr : vote_stats) {
      if(pr.second.empty()) {
        ++empty_ct;
        continue;
      }
      
      const int  idb_index = pr.first.at(0);
      if(dp_ptr->invent_idbs.find(idb_index) != dp_ptr->invent_idbs.end()){
        ++skip_invent_ct;
        continue;
      }
      
      votes.insert( (int) pr.second.size());
      
      int dis = (int) pr.second.size() * 2 - size;
      if(dis < 0) dis =-dis;
      
      //order.push_back( std::make_pair(dis, index) );
      //++index;
      
      if(dis < best) {
        question = pr.first;
        best = dis;
        //std::cout << "Question becomes: " ;
        //std::copy(question.begin(), question.end(), std::ostream_iterator<int>(std::cout, ", ") );
        //std::cout << std::endl;
      }
    }
    
    if(question.empty()) {
      std::cout << "Warn(selection_question): cannot select a question to ask!! \n"
      << "vote_stats size: " << vote_stats.size() << ", empty_ct: " << empty_ct
      << ", skip_invent_ct: " << skip_invent_ct << "\n";
      if(vote_stats.size() != empty_ct + skip_invent_ct) {
        std::cout << "ERROR(selection_question): reason unknown\n";
      }
    }
    
    return question;
  }
  
  void QueryEngine::QBC_without_refine(std::vector<DatalogProgram>& committee, std::vector<DatalogProgram>& deriveEmpty,
                                       std::vector<DatalogProgram>& deriveFalse, std::vector<DatalogProgram>& failDeriveTrue,
                                       z3::expr_vector& and_pos_vec, z3::expr_vector& or_neg_vec,
                                       std::set<std::vector<int>>& pos_Qs, std::set<std::vector<int>>& neg_Qs){
    
    
    if(neg_Qs.size() > 0){
      bool update = false;
      z3::expr pre_or_qs = z3::mk_or(or_neg_vec);
      for(DatalogProgram& prog : committee) {
        if( test(prog, pre_or_qs)){
          //std::cout << "catch new derive false\n";
          update = true;
          deriveFalse.push_back( std::move(prog) );
        }
      }
    
      if(update) {
        filter_out_inactive(committee);
      }
    }
    
    const size_t neg_size = neg_Qs.size();
    
    vote_stats.clear();
    
    // vote by the current committee
    //deriveEmpty = exec_programs(committee);
    //execute_one_round_helper(committee);
    
    for(auto & prog : exec_programs(committee)){
      deriveEmpty.push_back(std::move(prog));
    }
    
    
    //int eliminated_ct = 0;
    
    while(true) {
      // select question to ask
      //std::vector<int> Q = select_question( (int) (committee.size() - eliminated_ct) );
      std::vector<int> Q = select_question( (int) committee.size());
      
      if(Q.empty()) {
        // all left questions are about invented predicates, which cannot be answered
        break;
      }
      
      std::set<int> vote_members;
      auto vote_info = vote_stats.find(Q);
      if(vote_info != vote_stats.end()) {
        vote_members = vote_info->second;
      }
      
      // check if all active members agree on the vote
      if( vote_members.size()  >= committee.size() ) {
        if(vote_members.size() > committee.size()) {
          std::cout << "Error(QBC_without_refine): should be exactly equal here \n";
        }
        
        
        if(vote_members.size() >= 1) {
          
          std::cout << "the following " << vote_members.size() << " programs converge on: \n";
          for(auto it : vote_stats) {
            if(it.second.size() > 0) {
              bool positive = dp_ptr->ask(it.first);
              std::cout << dp_ptr->nice_display(it.first) << "  "
              << (positive ? "positive" : "negative")
              << " votes: " << it.second.size() << "\n";
            }
          }
          
          for(int i=0;i<committee.size();++i) {
            std::cout << "\n>> " <<(i+1) << "-th program in committee:\n";
            std::cout << dp_ptr->str(committee[i], false);
            if(i+1 >= 5) {
              std::cout << "... (" << (committee.size() - 5) << " more)" << std::endl;
              break;
            }
          }
        }
        
        break;
      }
      
      
      bool positive = dp_ptr->ask(Q);
      std::cout << (positive ? "positive" : "negative")
      << " answer for Question: " << dp_ptr->nice_display(Q)
      << std::endl;
      
      int eliminated = false;
      
      if(positive) {
        auto st = pos_Qs.insert(Q);
        if(st.second){
          z3::expr q = convert_question(Q);
          and_pos_vec.push_back(q);
        }
        
        
        
        for(DatalogProgram& x : committee){
          if( vote_members.find(x.prog_id) == vote_members.end() ){
            cancel_vote(x);
            
            eliminated = true;
            //++eliminated_ct;
            failDeriveTrue.push_back( std::move(x) );
          }
        }
      }
      else {
        auto st = neg_Qs.insert(Q);
        if(st.second) {
          z3::expr q = convert_question(Q);
          or_neg_vec.push_back(q);
        }
        
        for(DatalogProgram& x : committee){
          if( vote_members.find(x.prog_id) != vote_members.end() ){
            cancel_vote(x);
            
            eliminated = true;
            //++eliminated_ct;
            deriveFalse.push_back( std::move(x) );
          }
        }
      }
      
      //std::cout << "\ncommittee: \n"; print_out_programs(committee);
      //std::cout << "\nfailDeriveTrue: \n"; print_out_programs(failDeriveTrue);
      //std::cout << "\nderiveFalse: \n"; print_out_programs(deriveFalse);
      
      if(eliminated) {
        filter_out_inactive(committee);
      }
    }
    
    // finish QBC process
    
    //std::cout <<"\nafter QBC, still active: \n";
    //print_out_programs(committee);
    
    //std::cout <<"fail to derive true: \n";
    //print_out_programs(failDeriveTrue);
    
    //std::cout <<"derive false: \n";
    //print_out_programs(deriveFalse);
    
    // double check if anyone derive false,
    // this is possible because we introduce new questions
    z3::expr or_qs = z3::mk_or(or_neg_vec);
    int new_false_ct = 0;
    if(neg_Qs.size() > neg_size){
      for(DatalogProgram& prog : failDeriveTrue) {
        if( test(prog, or_qs)){
          //std::cout << "catch new derive false\n";
          ++new_false_ct;
          deriveFalse.push_back( std::move(prog) );
        }
      }
    }
    
    if(new_false_ct > 0) {
      filter_out_inactive(failDeriveTrue);
    }
    
    
  }
  
  void QueryEngine::stage_search(){
    
    typedef int IDBIndex;
    typedef int IDBRuleIndex;
    std::set< std::pair<IDBIndex, IDBRuleIndex> > rules;
    
    bool take_care_of_invented = !dp_ptr->invent_idbs.empty();
    const int MAX_INVENT = 2;
    
    std::chrono::steady_clock::time_point begin_stage_search = std::chrono::steady_clock::now();
    
    
    dp_ptr->init_SingleRulePrograms();
    for(DatalogProgram& prog : dp_ptr->SingleRulePrograms) {
      auto it = prog.state.begin();
      rules.insert( std::make_pair(it->first, *it->second.begin()));
      
      //std::cout << "Program with a single rule (" << it->first << ", " <<  *it->second.begin() <<")\n" << dp_ptr->str(prog,false) << "\n";
    }
    
    
    // evaluate & qbc
    std::vector<DatalogProgram>& candidate_progs = dp_ptr->SingleRulePrograms;
    std::vector<DatalogProgram> deriveEmpty;
    std::vector<DatalogProgram> deriveFalse;
    std::vector<DatalogProgram> failDeriveTrue;
    
    std::set<std::vector<int>> pos_Qs;
    std::set<std::vector<int>> neg_Qs;
    
    z3::expr_vector and_pos_vec(cm_ptr->C);
    z3::expr_vector or_neg_vec (cm_ptr->C);
    and_pos_vec.push_back( cm_ptr->C.bool_val(true) );
    or_neg_vec.push_back( cm_ptr->C.bool_val(false) );
    
    for(DatalogProgram& prog : candidate_progs) {
      dp_ptr->hash_and_record(prog);
    }
    
    QBC_without_refine(candidate_progs, deriveEmpty, deriveFalse, failDeriveTrue, and_pos_vec, or_neg_vec, pos_Qs, neg_Qs);
    
    for(DatalogProgram& bad_prog : deriveFalse) {
      auto bad_it = bad_prog.state.begin();
      auto bad_pr = std::make_pair(bad_it->first, *bad_it->second.begin());
      //std::cout << "remove rule in program: \n" << dp_ptr->str(bad_prog,false);
      rules.erase(bad_pr);
    }
    
    int iteration_ct = 0;
    while (true) {
      ++iteration_ct;
      
      std::cout << "\n=== iteration: " << iteration_ct << "\n";
      std::cout <<"candidate_progs size: " << candidate_progs.size() << "\n";
      std::cout <<"deriveFalse size: " << deriveFalse.size() << "\n";
      std::cout <<"failDeriveTrue size: " << failDeriveTrue.size() << "\n";
      
      //if(iteration_ct > dp_ptr->K) {
      //    std::cout << "ERROR(stage_search): reach maximum iterations exit but still do not converge\n";
      //    break;
      //}
      
      std::vector<DatalogProgram> basis = std::move(failDeriveTrue);
      const int candidate_offset = (int) basis.size();
      for(DatalogProgram& prog : candidate_progs) {
        basis.push_back(std::move(prog));
      }
      candidate_progs.clear();
      failDeriveTrue.clear();
      
      
      
      for(DatalogProgram& prog : basis) {
        vote_stats.clear();
        
        naive_execute(prog);
        bool out_suc = vstatus;
        
        if(!out_suc) {
          std::cout << "ERROR(stage_search): base program failed to execute.\n";
          continue;
        }
        
        int invs = 0;
        if(take_care_of_invented) {
          invs = count_invented_rules(prog);
        }
        
        for(std::pair<IDBIndex, IDBRuleIndex> pr : rules) {
          if(invs >= MAX_INVENT && dp_ptr->invent_idbs.find(pr.first) != dp_ptr->invent_idbs.end()) {
            continue;
          }
          
          DatalogProgram new_prog = dp_ptr->add_rule(prog, pr);
          
          // should be a new program
          if(dp_ptr->hash_and_record(new_prog) == false) {
            continue;
          }
          
          naive_execute(new_prog);
          bool suc = vstatus; //fail_to_derive.empty();
          
          if(suc) {
            // make sure newly added rule derive new tuples
            bool diff = false;
            for(auto it : vote_stats) {
              int vsize = (int) it.second.size();
              if(vsize == 1) {
                diff = true;
                break;
              }
              else if (vsize > 2) {
                std::cout << "ERROR(stage_search): unexpected vote size\n";
                
                std::cout << "prog: " << prog.prog_id << "\n";
                std::cout << dp_ptr->str(prog,false);
                std::cout << "new_prog: " << new_prog.prog_id << "\n";
                std::cout << dp_ptr->str(new_prog, false);
                
                std::cout << "vote_stats:\n";
                for(auto& pr : vote_stats) {
                  std::cout << dp_ptr->nice_display(pr.first) << "  votes: " << pr.second.size() << "\n";
                }
              }
            }
            suc = diff;
          }
          
          
          if(suc) {
            // should not be a superset of a program deriving false tuples
            for(DatalogProgram& bad_prog : deriveFalse) {
              if(new_prog.is_superset_of(bad_prog)) {
                suc = false;
                break;
              }
            }
          }
          
          
          if(suc) {
            // news tuples should not be false;
            for(auto& q : neg_Qs) {
              auto bad_it = vote_stats.find(q);
              if( bad_it != vote_stats.end() && bad_it->second.size() > 0) {
                
                // cancel before moved
                cancel_vote(new_prog);
                deriveFalse.push_back(std::move(new_prog));
                suc = false;
                break;
              }
            }
          }
          
          
          // if still active, cancel its vote effects
          if(new_prog.prog_id > 0) {
            cancel_vote(new_prog);
          }
          
          
          if(suc) {
            // passed almost above checks, consider it in the next iteration
            candidate_progs.push_back(std::move(new_prog));
          }
          
          
          
        } // end of iterating rules
        
      } // end of iterating basis
      
      
      if(candidate_progs.empty()) {
        // do not have any new program generated
        std::cout << "no new programs, assume converged!\n";
        for(int i=candidate_offset; i < basis.size(); ++i) {
          candidate_progs.push_back( std::move(basis[i]) );
        }
        break;
      }
      
      for(int i=candidate_offset; i < basis.size(); ++i) {
        // only add those that are consistent with positive tuples known by so far
        candidate_progs.push_back( std::move(basis[i]) );
      }
      
      std::cout << "after adding new rule\n";
      std::cout <<"deriveFalse size: " << deriveFalse.size() << "\n";
      std::cout <<"candidate_progs size: " << candidate_progs.size() << "\n";
      
      std::cout <<"program size stats:\n";
      std::map<int,int> size_stats;
      std::map< std::pair<int,int>, int> rule_stats;
      for(DatalogProgram& prog : candidate_progs){
        /*
         vote_stats.clear();
         execute(prog);
         if(prog.state.begin()->second.size() > 0) {
         bool oracle = true;
         for(auto& pr : vote_stats) {
         if(dp_ptr->ask(pr.first) == false){
         oracle = false;
         }
         }
         if(oracle) {
         std::cout << "\nthis might be an oracle (all derived are true and suppose it is complete)\n";
         std::cout << dp_ptr->str(prog, false);
         }
         }
         */
        int sz = 0;
        for(auto& pr: prog.state){
          sz += (int)pr.second.size();
          for(int x : pr.second) {
            ++rule_stats[ std::make_pair(pr.first, x) ];
          }
        }
        ++size_stats[sz];
      }
      
      for(auto pr : size_stats) {
        std::cout << "program_size : " << pr.first << ", count: " << pr.second << "\n";
      }
      //for(auto pr : rule_stats) {
      //std::cout << "rule (" << pr.first.first << "," << pr.first.second << "), count : " << pr.second << "\n";
      //}
      
      
      QBC_without_refine(candidate_progs,deriveEmpty, deriveFalse, failDeriveTrue, and_pos_vec, or_neg_vec, pos_Qs, neg_Qs);
    } // end of while(true)
    
    std::chrono::steady_clock::time_point end_stage_search = std::chrono::steady_clock::now();
    
    // converged
    std::cout << "Converged!!!\n";
    std::cout <<"failDeriveTrue size: " << failDeriveTrue.size() << "\n";
    std::cout <<"deriveFalse size: " << deriveFalse.size() << "\n";
    std::cout <<"candidate_progs size: " << candidate_progs.size() << "\n";
    
    print_out_programs(candidate_progs);
    
    
    int gen_program_ct = 0;
    for(auto& pr : dp_ptr->visited) {
      gen_program_ct += pr.second.size();
    }
    std::cout << "\nGenerated " << gen_program_ct << " programs\n";
    std::cout << "Positives: " << pos_Qs.size() << "\n";
    std::cout << "Negatives: " << neg_Qs.size() << "\n";
    std::cout << "Overall_asked: " << (pos_Qs.size() + neg_Qs.size()) << "\n";
    std::cout << "Final_committee: " << candidate_progs.size() << "\n";
    std::cout << "Overall_time: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end_stage_search - begin_stage_search).count()
    << " ms.\n";
    
    
  } // end of stage_search
  
}
