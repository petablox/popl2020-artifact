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

//#define LOG_REFINEMENT_LAYER_GRAPH

namespace ALPS {

namespace {
    

std::vector<int> extract_bv_values(z3::expr& E) {
	std::vector<int> v;
	std::string app_name = E.decl().name().str();
	if(app_name == "and"){
		// tuple with multiple fields, arity > 1
		//std::cout << "extract_bv_value: " << E  << std::endl;
			int m_args = E.num_args();
			for (int j = 0; j < m_args; ++j) {
				z3::expr var_val = E.arg(j);
				z3::expr val = var_val.arg(1);
				v.push_back( val.get_numeral_int() );
			}
	}
	else {
		// tuple with only one field, arity = 1
		//std::cout << "extract_bv_values, app_name= " << app_name << std::endl;

		z3::expr val = E.arg(1);
		v.push_back(val.get_numeral_int() );
	}



	return v;
}

const char* str(int x) {
	std::stringstream ss;
	ss << "v" << x;
	return ss.str().c_str();
}

} // end of anonymous namespace


z3::expr QueryEngine::build_func_constr(z3::context& context,
		std::map<int, z3::expr>& z3_vars,
		std::pair<Relation, std::vector<int>>& pair) {

	Relation rel = pair.first;

	auto it = cm_ptr->funcMap.find(rel);
	if (it == cm_ptr->funcMap.end()) {
		std::cerr << "ERROR, QueryEngine::helper got unknown relation : "
				<< rel->Name << std::endl;
	}

	z3::func_decl f = it->second;

	z3::expr_vector params(context);
	for (int x : pair.second) {
		auto it2 = z3_vars.find(x);
		if (it2 == z3_vars.end()) {
			std::cerr << "ERROR, QueryEngine::helper got undefined var: "
					<< str(x) << std::endl;
		}

		params.push_back(it2->second);
	}

	return f(params);
}

void QueryEngine::parse_and_update(z3::expr& E, int idx, int prog_id, bool cancelVote) {
	//std::cout << "parse_and_update, E=" << E << std::endl;
	std::string app_name = E.decl().name().str();
	if (app_name == "or") {
		int n_args = E.num_args();
		for (int i = 0; i < n_args; ++i) {
			z3::expr e = E.arg(i);
			std::vector<int> tp = extract_bv_values(e);

			// prepend idx
			tp.insert(tp.begin(), idx);
			if(cancelVote){
				//--vote_stats[tp];
				vote_stats[tp].erase(prog_id);
			}
			else{
				//++vote_stats[tp];
				vote_stats[tp].insert(prog_id);
                vstatus = true; // only for naive_execute
			}

			//std::cout <<"tp: ";
			//std::copy(tp.begin(), tp.end(), std::ostream_iterator<int>(std::cout, ","));
			//std::cout << std::endl;
		}
	} else if (app_name == "and" || app_name == "=") {
		std::vector<int> tp = extract_bv_values(E);
		tp.insert(tp.begin(), idx);
		if(cancelVote){
			//--vote_stats[tp];
			vote_stats[tp].erase(prog_id);
		}
		else{
			//++vote_stats[tp];
			vote_stats[tp].insert(prog_id);
            vstatus = true; // only for naive_execute
		}
	} else {
		std::cerr << "unknown application name: " << app_name << std::endl;
	}
}


z3::expr QueryEngine::construct_query(Relation rel){
	z3::context& context = cm_ptr->C;
	z3::sort bv_sort = context.bv_sort(cm_ptr->MaxBits);

	z3::func_decl f = cm_ptr->funcMap.find(rel)->second;
	const int arity = rel->Arity;

	z3::expr_vector ex_vs(context);
	for (int x=0; x < arity; ++x) {
		z3::expr vx = context.constant(str(x), bv_sort);
		ex_vs.push_back(vx);
	}

	return z3::exists(ex_vs, f(ex_vs));
}

void QueryEngine::queryIDBs(FixedPoint& fp, bool cancelVote) {

	const size_t sz = dp_ptr->idbRules.size();

	for(int idb_index = 0; idb_index < sz; ++idb_index){
		Relation rel = dp_ptr->idbRules[ idb_index ].rel.pRel;
		if ( fp.query( construct_query(rel) ) ){
			z3::expr detailed_res = fp.get_answer();
			parse_and_update(detailed_res, idb_index, fp.prog_id, cancelVote);
		}
		else {
			if(!cancelVote){
				++warn_ct;
			}
		}
	}

}


FixedPoint QueryEngine::prepare(const DatalogProgram & dp) {
	z3::context& context = cm_ptr->C;
	z3::sort bv_sort = context.bv_sort(cm_ptr->MaxBits);

	std::vector<z3::expr> z3_rs;

	std::vector<ConcreteRule> rs = dp_ptr->getConcreteRules( dp );

	for (ConcreteRule& r : rs) {
		// define vars
		std::set<int> vars;
		for (auto pr : r) {
			for (int x : pr.second) {
				vars.insert(x);
			}
		}

		std::map<int, z3::expr> z3_vars;
		z3::expr_vector all_vs(context);
		for (int x : vars) {
			//z3::expr va = c.constant("a", bv3);
			z3::expr vx = context.constant(str(x), bv_sort);
			z3_vars.insert( std::make_pair(x, vx) );
			all_vs.push_back(vx);
		}

		z3::expr head = build_func_constr(context, z3_vars, r[0]);

		//queries.insert(r[0]);

		z3::expr_vector ev(context);
		const size_t n = r.size();
		for (int i = 1; i < n; ++i) {
			z3::expr e = build_func_constr(context, z3_vars, r[i]);
			ev.push_back(e);
		}
		// z3::expr r2 = z3::forall(va, vb, vc, z3::implies( z3::mk_and(ev), path(va,vc) ));

		z3::expr rule = z3::forall(all_vs, z3::implies(z3::mk_and(ev), head));

		z3_rs.push_back(rule);
	}

	FixedPoint fp(cm_ptr);
	fp.add_rules(z3_rs);
	fp.set_prog_id(dp.prog_id);

	return fp;
}

bool QueryEngine::execute(const DatalogProgram& dp) {
    
    //std::cout << "execute, prog_id = " << dp.prog_id << std::endl;
  
	bool status = true;
    //std::cout << dp_ptr->str(dp) << std::endl;
	FixedPoint fp = prepare(dp);
	const int before = warn_ct;
	queryIDBs(fp);
	const int after = warn_ct;
	//if(before != after && !random_mode && !(Config.enableX)) {
    if(before != after) {
        fail_to_derive.insert( dp.prog_id );
		//std::cout << "will cancel vote for program: \n" << dp_ptr->str(dp) << std::endl;
		queryIDBs(fp, true);

		status = false;
	}

	return status;
}

z3::expr QueryEngine::convert_question(std::vector<int>& Q){
	const int idb_index = Q[0];
	Relation rel = dp_ptr->idbRules[idb_index].rel.pRel;
	auto it = cm_ptr->funcMap.find(rel);
	if (it == cm_ptr->funcMap.end()) {
		std::cerr << "ERROR, QueryEngine::test got unknown relation : "
				<< rel->Name << std::endl;
	}
	z3::func_decl f = it->second;


	z3::context& context = cm_ptr->C;
	z3::expr_vector params( context);
	const size_t sz = Q.size();
	for(int i=1; i< sz; ++i) {
		z3::expr val = context.bv_val( Q[i] ,cm_ptr->MaxBits);
		params.push_back(val);
	}

	return f(params);
}

bool QueryEngine::test(const DatalogProgram& dp, z3::expr Q) {
	FixedPoint fp = prepare(dp);
	return fp.query( Q );
}

bool QueryEngine::test_converge_old() {
	vote_stats.clear();
	int ct = 0;
	std::vector<const DatalogProgram*> vp;
	for(const DatalogProgram& p : dp_ptr->Ss) {
		vp.push_back( &p);
	}
	for(const DatalogProgram& p : dp_ptr->Gs) {
		vp.push_back( &p);
	}

	for(const DatalogProgram* p : vp) {
		++ct;
		execute(*p);

		for(auto pr : vote_stats) {
			if(pr.second.empty()) {
				continue;
			}
			if(pr.second.size() != ct){
				return false;
			}
		}
	}

	return true;
}
std::vector<int> QueryEngine::random_pick_old(){
	std::vector<int> res;

	// test converge
	if( test_converge() ) {
		return res;
	}

	while (res.size() == 0) {
		const int idb_index = std::rand() % dp_ptr->idbRules.size();
		const IDBTR& idb = dp_ptr->idbRules[idb_index];
		const int S = idb.rel.getSpace();
		const int K = std::rand() % S;

		auto pr = std::make_pair(idb_index, K);
		if (random_picked.find(pr) == random_picked.end()) {
			random_picked.insert(pr);
			res = idb.rel.getKthTuple(K);
			res.insert(res.begin(), idb_index);
		}
	}



	return res;
}

bool QueryEngine::test_converge() {
	size_t ct = -1;

	for(const auto & it : vote_stats ) {
		if(it.second.empty()) {
			continue;
		}

        const int  idb_index = it.first.at(0);
        if(dp_ptr->invent_idbs.find(idb_index) != dp_ptr->invent_idbs.end()){
            continue;
        }
 
		if(ct == -1){
			ct = it.second.size();
		}
		if(ct != it.second.size()){
			return false;
		}
	}
	return true;
}

std::vector<int> QueryEngine::random_pick(){
	std::vector<int> res;
	std::vector< std::vector<int> > pool;

	// test converge
	if( test_converge() ) {
        if( validate_with_full_IDBs() ) {
            std::cout << "validation result: Accept" << std::endl;
        }
        else{
            std::cout << "validation result: Wrong Answer" << std::endl;
        }
		return res;
	}

	for(const auto & it : vote_stats ) {
		if(it.second.empty()) {
			continue;
		}

        const int  idb_index = it.first.at(0);
        if(dp_ptr->invent_idbs.find(idb_index) != dp_ptr->invent_idbs.end()){
            continue;
        }
 
		pool.push_back(it.first);
	}

	if(pool.size()) {
		const int index = std::rand() % pool.size();
		return pool[index];
	}

	return res;
}

void QueryEngine::initial_execution(std::vector<DatalogProgram>& progs) {
    std::chrono::steady_clock::time_point exec_begin = std::chrono::steady_clock::now();
    long long longest_run = 0;
    
	auto it = progs.begin();
	while(it != progs.end()) {
        std::chrono::steady_clock::time_point _b = std::chrono::steady_clock::now();

        execute(*it);
		++it;
        
        std::chrono::steady_clock::time_point _e = std::chrono::steady_clock::now();
        long long t = std::chrono::duration_cast<std::chrono::milliseconds>(_e - _b).count();
        if(longest_run < t) {
            longest_run = t;
        }

	}

    /*
     // instead of directly cancel voting, we should consider to generalize it.
	int cancel_ct = 0;
	std::vector<DatalogProgram> dps;
	for(DatalogProgram& x :progs) {
		if(fail_to_derive.find(x.prog_id) == fail_to_derive.end()) {
			dps.push_back( std::move(x) );
		}
		else{
			++cancel_ct;
		}
	}

	progs =std::move(dps);

	std::cout << "cancel votes for " << cancel_ct << " programs, now size: " << progs.size() << std::endl;
    */
    
    std::chrono::steady_clock::time_point exec_end = std::chrono::steady_clock::now();

    std::cout << "(Time_Measure) execute_one_round_helper takes "
    << std::chrono::duration_cast<std::chrono::milliseconds>(exec_end - exec_begin).count()
    << " ms, longest_run: " << longest_run <<" max_threads: " << progs.size() << "\n";

}

bool QueryEngine::validate_with_full_IDBs() {
	bool succ = true;
    for (auto& pr : vote_stats) {
        if(pr.second.empty() ) {
            continue;
        }
		const std::vector<int>& Q = pr.first;
        // skip invented idbs
        if(dp_ptr->invent_idbs.find(Q.at(0)) != dp_ptr->invent_idbs.end()) {
            continue;
        }
        
		if(! dp_ptr->ask(Q)){
			std::cout << dp_ptr->nice_display(Q) << " is predicated to be true, but actually false\n";
			succ = false;
		}
	}
	const size_t sz = dp_ptr->idbValues.size();
	for(int i=0; i < sz; ++i) {
        // skip invented idbs
        if(dp_ptr->invent_idbs.find(i) != dp_ptr->invent_idbs.end()) {
            continue;
        }

		const IDBValue& iv = dp_ptr->idbValues[i];
		for(const std::vector<int>& v : iv.pos) {
			std::vector<int> Q(v.begin(), v.end());
			Q.insert(Q.begin(), i);

			auto it = vote_stats.find(Q);
			if(it == vote_stats.end() || it->second.empty()) {
				std::cout << dp_ptr->nice_display(Q) << " is missing by the committee\n";
				succ = false;
			}
		}
	}
	return succ;
}

    
    void QueryEngine::showVotesAndGS() {
        std::cout << "\ntuple stats: \n";
        for (const auto& pr : vote_stats) {
            std::cout << pr.second.size() << " votes for "
            << dp_ptr->nice_display(pr.first) << std::endl;
            std::cout << "voters: ";
            std::copy(pr.second.begin(), pr.second.end(), std::ostream_iterator<int>(std::cout, ","));
            std::cout << std::endl;
        }
        std::cout << "Gs: ";
        for(auto& p : dp_ptr->Gs) {
            std::cout << p.prog_id << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Ss: ";
        for(auto& p : dp_ptr->Ss) {
            std::cout << p.prog_id << " ";
        }
        std::cout << std::endl;
    }
    
std::vector<int> QueryEngine::query_one_round() {

	fail_to_derive.clear();
	warn_ct = 0;

    std::set<int> gids;
    for(auto& p : dp_ptr->Gs) {
        gids.insert(p.prog_id);
    }
    std::set<int> sids;
    for(auto& p : dp_ptr->Ss) {
        gids.insert(p.prog_id);
    }
    
    std::set<int> useless_ids;
    std::set<int> votes;
    std::vector<int> question;

    const int total_votes = (int) (dp_ptr->Gs.size() + dp_ptr->Ss.size());
    std::cout <<"total_votes: " << total_votes << std::endl;
    
    const int ideal = total_votes  / 2;
    int best = 1<<30;

    for (auto& pr : vote_stats) {
        if(pr.second.empty()) {
            continue;
        }

        const int  idb_index = pr.first.at(0);
        if(dp_ptr->invent_idbs.find(idb_index) != dp_ptr->invent_idbs.end()){
            continue;
        }
      
		votes.insert( (int) pr.second.size());

		int dis = (int) pr.second.size() - ideal;
		if(dis < 0) dis =-dis;

		//order.push_back( std::make_pair(dis, index) );
		//++index;

		if(dis < best) {
            
            bool not_eliminated = false;
            for(auto x : pr.second) {
                if( gids.find(x) != gids.end() ) {
                    not_eliminated = true;
                    break;
                }
                
                if( sids.find(x) != sids.end() ) {
                    not_eliminated = true;
                    break;
                }
                useless_ids.insert(x);
            }

            if(not_eliminated){
                question = pr.first;
                best = dis;
            }
			//std::cout << "update best: dis=" << dis << ", best=" << best << std::endl;
			//std::cout << "Question becomes: " ;
			//std::copy(question.begin(), question.end(), std::ostream_iterator<int>(std::cout, ", ") );
			//std::cout << std::endl;
		}
	}
    
    for(auto x : useless_ids) {
        for(auto& it : vote_stats) {
            it.second.erase(x);
        }
    }

    if(votes.size() == 0) {
        showVotesAndGS();
    }

	std::cout << "best distance: " << best << std::endl;

	if(votes.size() == 1) {
		if( *votes.begin() == total_votes ) {

			std::cout << "only one size of vote: " << *votes.begin() << ", so converged." << std::endl;

			if( validate_with_full_IDBs() ) {
				std::cout << "validation result: Accept" << std::endl;
			}
			else{
				std::cout << "validation result: Wrong Answer" << std::endl;
                /*
                showVotesAndGS();
                votes.clear();
                for(auto & p : dp_ptr->Gs) {
                    execute(p);
                }
                
                bool status = validate_with_full_IDBs() ;
                std::cout << "revaliataion: " << (status ? "Yes" : "No") << std::endl;
                showVotesAndGS();
                 */
			}
            
            

			// converged !!!
			return std::vector<int>();
		}
	}
    else {
        std::cout << "different votes: " << votes.size() << std::endl;
    }


	/*
	std::sort(order.begin(), order.end());
	// find the first positive one
	for(auto pr : order){
		int index = pr.second;
		auto it = vote_stats.begin();
		while(index --) {
			++it;
		}
		std::vector<int> v = it->first;

		if(dp_ptr->ask(v )){
			question = v;
			break;
		}
	}*/


	//std::cout << "Question: " ;
	//std::copy(question.begin(), question.end(), std::ostream_iterator<int>(std::cout, ", ") );
	//std::cout << std::endl;

	return question;
}


bool QueryEngine::canDerive(const DatalogProgram& dp, const std::vector<int>& Q) {
	auto it = vote_stats.find(Q);
	if(it == vote_stats.end() || it->second.find(dp.prog_id) == it->second.end()) {
		return false;
	}
	return true;
}

std::pair<bool,bool> QueryEngine::testDerivation(DatalogProgram& x, bool positive, std::vector<int>& Q, std::vector<std::vector<int> >& Qs) {
	bool derive_positive = true;
	bool derive_negative = false;
	if(positive) {
		derive_positive = canDerive(x, Q);
		if (derive_positive) {
			for (std::vector<int>& vi : Qs) {
				if (canDerive(x, vi)) {
					derive_negative = true;
					break;
				}
			}
		}
	}
	else{
		derive_negative = canDerive(x, Q);
		if(!derive_negative) {
			for (std::vector<int>& vi : Qs) {
				if (!canDerive(x, vi)) {
					derive_positive = false;
					break;
				}
			}
		}
	}

	return std::make_pair(derive_positive, derive_negative);
}



void QueryEngine::eliminate_and_refine_old(std::vector<DatalogProgram>& A,
		std::vector<DatalogProgram>& B, bool positive, z3::expr& pos_qs, z3::expr& neg_qs,
		std::vector<int>& Q) {
	// any general program that cannot cover Q should be eliminated.

	std::vector<DatalogProgram> dps;
	int remove_ct = 0;


	//std::cout << "A.size() = " << A.size() <<

	for (DatalogProgram& x : A) {
		if (test(x, pos_qs) && !test(x, neg_qs)) {
			dps.push_back(std::move(x));
		} else {
			++remove_ct;

			// cancel vote
			FixedPoint fp = prepare(x);
			queryIDBs(fp, true);

			//std::string s = dp_ptr->str(x);
			//long long h = str_hash(s);
			//removedPrograms[h].insert(s);
		}
	}

	A = std::move(dps);

	//std::cout << "Number of programs to eliminate: "
	//		<< remove_ct << ", out of " << A.size()
	//		<< std::endl;
	//std::cout << "dps.size = " << dps.size() << std::endl;
	//std::cout << "A new size: " << A.size() << std::endl;


	// generalize specific program that cannot cover  Q
#ifdef LOG_REFINEMENT_LAYER_GRAPH
	int x_id;
	const int L = layers.size();
#endif

	int refine_ct = 0;
	for (DatalogProgram& x : B) {

#ifdef LOG_REFINEMENT_LAYER_GRAPH
		x_id = x.prog_id;
#endif
        
		if (test(x, pos_qs) && ! test(x,neg_qs) ) {
			dps.push_back(std::move(x));
		} else {

			// cancel vote
			FixedPoint fp = prepare(x);
			queryIDBs(fp, true);


			//std::cout <<"positive=" << positive << ", going to refine \n" << dp_ptr->str(x);
			//std::cout << "before: refine_ct = " << refine_ct << std::endl;

			std::queue<DatalogProgram> Queue;
			Queue.push(std::move(x));

			while (!Queue.empty()) {
				++refine_ct;

				//std::cout <<"Queue.size = " << Queue.size() << std::endl;

				DatalogProgram p ( std::move(Queue.front() ));
				Queue.pop();

				// here, we actually don't need to test if deleted or not
				// as init/refineProg will never return a visited program

				//std::cout << "\nrefine: \n" << dp_ptr->str(p) << std::endl;
				//std::cout << "refined results: \n";

				bool specialize = !positive;
				std::vector<DatalogProgram> vs = dp_ptr->refineProgWithTarget(p,
						specialize, Q[0]);
				for (DatalogProgram& y : vs) {

#ifdef LOG_REFINEMENT_LAYER_GRAPH
					edges[x_id].insert(std::make_pair(L, y.prog_id));
#endif

					const bool contain_pos = test(y, pos_qs);
					const bool contain_neg = test(y, neg_qs);

					if(positive) {
						// positive example, we now generalize specific program
						if(contain_neg) {
							// ignore
						}
						else if(contain_pos) {
							// vote for the first time
							if(execute(y)) {
								// get expected generalization
								dps.push_back(std::move(y));
							}

						}
						else {
							// keep refining
							Queue.push(std::move(y));
						}
					}
					else {
						// negative example, we now specialize
						if(contain_pos){
							if(contain_neg) {
								// keep refining
								Queue.push( std::move(y) );
							}
							else {
								// vote for the first time
								if(execute(y)) {
									// get expected generalization
									dps.push_back(std::move(y));
								}
							}
						}
					}

					//if (test(y, pos_qs) && !test(y, neg_qs)) {
					//	dps.push_back(std::move(y));
					//} else {
					//	Queue.push(std::move(y));
					//}
				}
			}

			//std::cout << "after: refine_ct = " << refine_ct << std::endl;

		}
	}

	B = std::move(dps);

	std::cout << "removed_ct=" << remove_ct << ", refine_ct = " << refine_ct
			<< ", size: " << dp_ptr->Gs.size() << std::endl;

}



void QueryEngine::work_baseline() {
	int round = 0;
	while (true) {
		++round;

		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

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

		std::vector<DatalogProgram> dps;
		int remove_ct = 0;

		for (DatalogProgram& x : dp_ptr->Gs) {
			bool res = canDerive(x, Q);

			if (res == positive) {
				dps.push_back(std::move(x));
			} else {
				++remove_ct;

				// cancel vote
				for (auto& it : vote_stats) {
					it.second.erase(x.prog_id);
				}
			}
		}

		dp_ptr->Gs = std::move(dps);

		std::cout << "removed_ct=" << remove_ct << ", refine_ct = " << 0
				<< ", size: " << dp_ptr->Gs.size() << std::endl;

		std::chrono::steady_clock::time_point after_refine = std::chrono::steady_clock::now();

	    std::cout << "Round " << round << " refinement takes "
	              << std::chrono::duration_cast<std::chrono::milliseconds>(after_refine - before_refine).count()
	              << " ms.\n";

	    std::cout << "Round " << round << " overall takes "
	              << std::chrono::duration_cast<std::chrono::milliseconds>(after_refine - start).count()
	              << " ms.\n";

	}

	std::cout << "Synthesized programs by baseline\n";
	for(const DatalogProgram& x : dp_ptr->Gs) {
		std::cout << "\n\n" << dp_ptr->str(x);
	}

}



void QueryEngine::draw_layer_graph(std::set<int>& greens){

	std::string fpath = "layerG.dot";

	std::ofstream fout(fpath);
	fout << "digraph G {\n";


	const size_t L = layers.size();

	//for(std::vector<int>& v : layers){

	for(int i=0; i < L; ++i) {
		std::vector<int>& v = layers[i];

		fout << "  subgraph {\n";
		fout << "    rank = same;";
		for(int x : v) {
			fout <<"layer" << i << "_P" << x << "; ";
		}
		fout << "\n  }\n";
	}


	for(int i = 0; i < L; ++i) {
		std::vector<int>& v = layers[i];
		for(int x : v) {
			std::set< std::pair<int,int> > st = edges[x];
			std::set<int> st2;

			if (i + 1 < L) {
				for (int y : layers[i + 1]) {
					if (x == y) {
						st2.insert(y);
					}
				}
			}


			for(auto pr : st){
				//std::cout <<"layer=" <<i <<", x=" << x << ", pr.first = " << pr.first  << ", pr.second = " << pr.second << std::endl;
				if(i+1 == pr.first) {
					//std::cout <<"x=" << x << ", pr.second = " << pr.second << std::endl;
					st2.insert(pr.second);
				}
			}

			if(st2.size()) {
				fout <<" layer" << i << "_P" << x << " -> {";

				for(int y : st2) {
					fout << " layer" << (i+1) << "_P" << y <<" ";
				}

				fout << "  };\n";
			}
		}
	}

	/*
	for (auto pr : edges) {
		int x = pr.first;
		if (pr.second.size()) {
			fout << "P" << x << " -> {";
			for (int y : pr.second) {
				fout << "P" << y << " ";
			}
			fout << " };\n";
		}
	}*/

	/*
	for (int i = 0; i < sz; ++i) {
		std::string s = templates[i].toStr();
		int j = 0;
		while(j < s.length()){
			if(s[j] == '-') break;
			++j;
		}
		fout << "v" << i << " [label=\"" << s.substr(j+1) << "\"];\n";
	}
    */

	for(int i=0; i < L; ++i) {
		std::vector<int>& v = layers[i];
		for(int x : v){
			if(greens.find(x) != greens.end())
			fout <<"layer" << i << "_P" << x << " [style=filled color=\"yellow\"]; \n";
		}
	}


	fout << "}\n";

	fout.close();
}
    

    
    

} // end of namepsace ALPS
