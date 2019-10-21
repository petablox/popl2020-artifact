#ifndef QUERY_H
#define QUERY_H


#include "template.h"
#include "datalog.h"
#include "context.h"
#include "fixedpoint.hpp"

#include <vector>
#include <set>
#include <map>
//#include <tuple>


namespace ALPS {


struct QueryEngine {

	int warn_ct = 0;

	DPManager* dp_ptr;
	ContextManager* cm_ptr;

	std::hash<std::string> str_hash;
	std::map<long long, std::set<std::string> > removedPrograms;

	//std::map<std::vector<int>, int> vote_stats;
	std::map<std::vector<int>, std::set<int> > vote_stats;
    bool vstatus;
  
	std::set<int> fail_to_derive;

	//  data structure  for debugging
	std::map<int, std::set< std::pair<int,int> >> edges;
	std::vector< std::vector<int> > layers;
	void draw_layer_graph(std::set<int>&);

	// random selection
	std::set< std::pair<int,int> > random_picked;
	bool random_mode = false;

    // for debugging
  std::set<int> keep_track;

	z3::expr build_func_constr(z3::context& context,
			std::map<int, z3::expr>& z3_vars,
			std::pair<Relation, std::vector<int>>& pair);

	void initial_execution(std::vector<DatalogProgram>&);
	std::vector<int> query_one_round();

	std::vector<int> random_pick_old();
	bool test_converge_old();

	std::vector<int> random_pick();
	bool test_converge();


	//FixedPoint prepare(const DatalogProgram & dp,
	//		std::set<std::pair<Relation, std::vector<int>>>&queries);

	FixedPoint prepare(const DatalogProgram & dp);

	bool execute(const DatalogProgram & dp);
	//z3::expr construct_query(const std::pair<Relation, std::vector<int>>& Q);
	//void queryIDBs(std::set<std::pair<Relation, std::vector<int>>>& queries, FixedPoint& fp, bool=false);
	z3::expr construct_query(Relation);
	void queryIDBs(FixedPoint& fp, bool=false);
	bool validate_with_full_IDBs();

	void parse_and_update(z3::expr&, int, int, bool=false);

	bool test(const DatalogProgram&, z3::expr);

	z3::expr convert_question(std::vector<int>&);

	void eliminate_and_refine_old(std::vector<DatalogProgram>& A, std::vector<DatalogProgram>& B, bool,
			z3::expr&, z3::expr&, std::vector<int>& );

	bool canDerive(const DatalogProgram&, const std::vector<int>&);
	std::pair<bool,bool> testDerivation(DatalogProgram&, bool, std::vector<int>&, std::vector<std::vector<int> >&);


	void eliminate_and_refine2(std::vector<DatalogProgram>& A,
			std::vector<DatalogProgram>& B, bool, std::vector<int>&,
			std::vector<std::vector<int> >&);

  void showVotesAndGS();
  
	void work();

	void work_refinement();
	void work_baseline();
  
  // ====== APIs for single rule search =====
  //void single_rule_search();
//  void simulate_run(std::vector<DatalogProgram>&, std::vector<DatalogProgram>&);
//  std::vector<DatalogProgram> enumerateAll(std::vector< std::set<std::pair<int, int>> >&);
//  std::vector<int> collect_features(const std::map<int, std::set<int> >& );
  
  // ====== APIs for stage search =====
  //void stage_search();
//  void QBC_without_refine(std::vector<DatalogProgram>& , std::vector<DatalogProgram>&,
//                          std::vector<DatalogProgram>& , std::vector<DatalogProgram>&,
//                          z3::expr_vector&, z3::expr_vector&,
//                          std::set<std::vector<int>>&, std::set<std::vector<int>>&);
//  std::vector<int> select_question(const int size);
//  void print_out_programs(std::vector<DatalogProgram>&);
//  int count_invented_rules(DatalogProgram&);
//  void cancel_vote(DatalogProgram&);
//  void naive_execute(const DatalogProgram& );
//  std::vector<DatalogProgram> exec_programs(std::vector<DatalogProgram>&);

};


} // end of namepsace ALPS




#endif
