#ifndef DATALOG_H
#define DATALOG_H

#include "template.h"
#include "matching.h"

#include <vector>
#include <functional>
#include <string>

namespace ALPS {

typedef std::vector< std::pair<Relation, std::vector<int>> > ConcreteRule;

struct QueryEngine;
struct DPManager;
struct DatalogProgram;
struct IDBTR;

enum ChooseOption {
	GENERAL,
	SPECIFIC,
	ALL
};

// templates and rules for an IDB
struct IDBTR {
	TRelation rel;
	TemplateManager tm;
	std::vector<IClause> rules;

	std::map<int, std::set<int>> tmpl2rules;
	//std::set<std::set<int> > mostG;
	//std::set<std::set<int> > mostS;

	IDBTR(const TRelation & r) : rel(r){}

	IDBTR(IDBTR&& idb) noexcept :
			rel(idb.rel),
			tm(std::move(idb.tm)),
			rules(std::move(idb.rules)),
			tmpl2rules(std::move(idb.tmpl2rules)) {}
			//mostG(std::move(idb.mostG)),
			//mostS(std::move(idb.mostS)) {}

	IDBTR& operator = (IDBTR&& idb) noexcept {
		//std::cout <<"assign move is called" << std::endl;
		rel = idb.rel;

		tm = std::move(idb.tm);
		rules = std::move(idb.rules);
		tmpl2rules = std::move(idb.tmpl2rules);
		//mostG = std::move(idb.mostG);
		//mostS = std::move(idb.mostS);

		return *this;
	}

	void init();
	std::set<int> extractRules(const std::set<int>&) const;

    std::vector<std::set<int>> chooseK(int k, ChooseOption option) const;
    std::vector<std::set<int>> chooseK_exact(int k, ChooseOption option) const;

	std::set<int> generalize(int rule_index) const;
	std::set<int> specialize(int rule_index) const;

};

struct DatalogProgram {
	static int programCt;

	const DPManager* dpm;
	int prog_id;
	std::map<int, std::set<int>> state;

	DatalogProgram(const DPManager* p) : prog_id(++programCt), dpm(p) {}
	DatalogProgram(const DatalogProgram&) = delete; // disable copy constructor, make DatalogProgram like linear-type

	DatalogProgram(DatalogProgram&& dp) noexcept : prog_id(dp.prog_id), dpm(dp.dpm), state(std::move(dp.state)) {
		dp.prog_id = -1;
		dp.dpm = nullptr;
	}

	DatalogProgram& operator = (DatalogProgram&& dp)  = delete;

	bool operator < (const DatalogProgram& dp) const {
		return prog_id < dp.prog_id;
	}
    
    // ====================================
    // ==== APIs added for stage search ===
    // ====================================

    bool is_subset_of(const DatalogProgram& dp) const{
        const auto& S = dp.state;
        
        if(state.size() > S.size()) {
            return false;
        }
        
        for(auto& it : state) {
            auto s_it = S.find(it.first);
            if( s_it == S.end() ) {
                return false;
            }
            for(int v : it.second) {
                if(s_it->second.find(v) == s_it->second.end()) {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool is_superset_of(const DatalogProgram& dp) const{
        // note that superset is not the negation of subset
        // as each of two sets may contain unique items
        const auto& S = state;
        if(state.size() < S.size()) {
            return false;
        }

        for(auto& it : dp.state) {
            auto s_it = S.find(it.first);
            if( s_it == S.end() ) {
                return false;
            }
            for(int v : it.second) {
                if(s_it->second.find(v) == s_it->second.end()) {
                    return false;
                }
            }
        }
        return true;
    }

};


struct IDBValue {
	TRelation rel;
	std::set< std::vector<int> > pos;

	std::set< std::vector<int> > asked_pos;
	std::set< std::vector<int> > asked_neg;

	IDBValue(const TRelation& r) : rel(r) {}

	IDBValue(const IDBValue&) = delete;

	IDBValue(IDBValue&& iv) noexcept:
			rel(iv.rel),
			pos(std::move(iv.pos)),
			asked_pos(std::move(iv.asked_pos)),
			asked_neg(std::move(iv.asked_neg)){}

	IDBValue operator=(IDBValue&&) = delete;

	bool ask_and_update(std::vector<int>& v);
};


struct DPManager {

    std::set<int> dbg_track;
    
	const Matching& M;
	std::vector<IDBTR> idbRules;
	std::vector<IDBValue> idbValues;
    std::set<int> invent_idbs;

	std::vector<DatalogProgram> Gs;
	std::vector<DatalogProgram> Ss;
    std::vector<DatalogProgram> SingleRulePrograms;
    

	std::hash<std::string> str_hash;
	std::map<long long, std::set<std::string>> visited;

	//std::set<DatalogProgram> Gs;
	//std::set<DatalogProgram> Ss;

	//std::vector< std::vector<int> > execute(const DatalogProgram&);

	std::vector<ConcreteRule> getConcreteRules(const DatalogProgram&);
	std::string str(const DatalogProgram&,bool withTemplate = true);


	DPManager(const Matching& match) : M(match) {}

    void init_helper_efficient(ChooseOption option);
    
	void init_helper(ChooseOption option);
	void initGSX();
    void init_SingleRulePrograms();
    
    void exploreProjection(const TRelation& , std::vector<TClause>& );
    void addFilter(std::vector<TClause>& );
    void addFilter2(std::vector<TClause>& );
    void addNewBindingInHead(std::vector<TClause>& );
    void addNewBindingInBody(std::vector<TClause>& );
    void exploreChain2(const TRelation& , std::vector<TClause>& );
    void exploreChain3(const TRelation& , std::vector<TClause>& );

	void exploreCandidateRules();
	void fillIDBValues(); // shoudl be called after exploreCandidateRules

	std::vector<DatalogProgram> refineProg(const DatalogProgram& prog, bool specialize);

	std::vector<DatalogProgram> refineProgWithTarget(const DatalogProgram& prog, bool specialize, int idb_index);

	std::set<int> backwardAnalysis(const DatalogProgram& prog, int idb_index) const;

	int findIDBIndex(Relation r) const;

	bool pass_filters(const DatalogProgram&);

	bool hash_and_record(const DatalogProgram&);

	bool may_derive_something(const DatalogProgram&) const;

	bool total_rules_too_large(const DatalogProgram& ) const;

	//bool too_deep(const DatalogProgram&) const;

	std::vector< std::set<int> > get_dependents(const DatalogProgram& prog, int idb_index) const;

	bool ask(const std::vector<int>&);

	void test_specialize();

	void examine_each_IDBTR(QueryEngine* pEngine);
	DatalogProgram expand();

	std::string nice_display(const std::vector<int>& Q)const;
    
    //
    DatalogProgram add_rule(DatalogProgram& prog, std::pair<int,int> r);
};

} // namespace ALPS

#endif
