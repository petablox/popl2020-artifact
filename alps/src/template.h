#ifndef CLAUSE_TEMPLATE_H
#define CLAUSE_TEMPLATE_H

#include "defns.h"

#include <vector>
#include <string>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>

namespace ALPS {

struct TPredicate;
struct TClause;
struct TemplateManager;
struct RelationManager;
struct TRelation;

struct IClause;


struct TPredicate {
	int pid;
	int arity;
	std::vector<int> vdom;

	TPredicate() :
			pid(0), arity(0) {
	}

	TPredicate(const TPredicate& ) = default;

	TPredicate(TPredicate&& pr) noexcept : pid(pr.pid), arity(pr.arity), vdom(std::move(pr.vdom)) {}

	TPredicate& operator= (TPredicate&& pr) noexcept {
		pid = pr.pid;
		arity = pr.arity;
		//std::swap(pid, pr.pid);
		//std::swap(arity, pr.arity);
		//std::swap(vdom, pr.vdom);
		vdom = std::move(pr.vdom);

		pr.pid = -1;
		pr.arity = -1;
		return *this;
	}

	TPredicate& operator = (const TPredicate& pr) {
		pid = pr.pid;
		arity = pr.arity;
		vdom = pr.vdom;
		return *this;
	}


	bool operator == (const TPredicate& pr) const {
		return pid == pr.pid
				&& arity == pr.arity
				&& arity == vdom.size()
				&& std::equal(vdom.begin(), vdom.end(), pr.vdom.begin());
	}

	std::string toStr() const;
};

struct TClause {
	TPredicate hd;
	std::vector<TPredicate> vbody;

	TClause() {}

	TClause(const TClause& ) = default;

	TClause(TClause&& cl) noexcept : hd(std::move(cl.hd)), vbody(std::move(cl.vbody)) {}
	TClause& operator= (TClause&& cl) noexcept {
		hd = std::move(cl.hd);
		//hd = cl.hd; // this is the bug
		vbody = std::move(cl.vbody);
		return *this;
	}

	bool operator == (const TClause& tc) const {
		return hd == tc.hd
				&& vbody.size() == tc.vbody.size()
				&& std::equal(vbody.begin(), vbody.end(), tc.vbody.begin());
	}

	bool moreGeneralThan(const TClause& tc, std::map<int,int>&, std::map<int,int>&) const;

	bool existDisconnectedPred() const;
	bool existUnboundVarInHead() const;
	std::string toStr() const;
};

// a wrapper of the old Relation
struct TRelation {
	Relation pRel;
	TRelation(Relation p): pRel(p){}

	Relation getRel() const {return pRel;}
	int getArity() const {return pRel->Arity;}
	TypeInfo getType(int k) const {return pRel->TypeRef[k+1]; }
	std::string getRelName() const {return std::string(pRel->Name);}

	std::string getRelNameWithTypes() const;

	std::vector<std::string> getStrs() const;

	int getSpace() const;
	std::vector<int> getKthTuple(int K) const;

	bool possibleMatch(const TPredicate &) const;

	bool isEDB() const { return pRel->PossibleTarget == false;}
	bool isIDB() const { return pRel->PossibleTarget;}

};


// instantiated clause
struct IClause {
	TClause tc;
	TRelation cl_hd;
	std::vector<TRelation> cl_body;

	IClause(const TClause& c, const TRelation& r, std::vector<TRelation>& vrel) :
			tc(c), cl_hd(r), cl_body(std::move(vrel)) {
	}

	IClause(const IClause&&) = delete;

	IClause(IClause&& cl) noexcept: tc(std::move(cl.tc)), cl_hd(cl.cl_hd), cl_body(std::move(cl.cl_body)) {
	}

	IClause& operator= (IClause&& cl) noexcept {
		tc = std::move(cl.tc);
		cl_hd = cl.cl_hd;
		//cl.cl_body = std::move(cl.cl_body); // a bug
		cl_body = std::move(cl.cl_body);

		return *this;
	}

	std::string toStr(bool withTemplate=true) const;
	void explain() const;

	std::vector< std::pair<Relation, std::vector<int>> > zip() const;

	// P0(v..) :- ..., P0(v..),...
	bool is_useless() const;
    
    bool equivalentTo(const IClause& ic) const;
};

struct TemplateManager {
	std::vector<TClause> templates;

	std::map<int, std::set<int>> general_po;
	std::map<int, std::set<int>> specific_po;

	typedef std::map<int,int> PII;
	std::map<int, std::map<int, std::pair<PII,PII> >> general_proof;


	void loadTemplates(std::string fpath);
	void showTemplates() const;

	void buildPartialOrder();
	void normalizePO();

	std::set<int> getMostGeneral() const;
	std::set<int> getMostSpecific() const;
	std::set<int> getIndependent() const;


	void logPO2dot(std::string f);

	TemplateManager() {}

	TemplateManager(TemplateManager&& tm) noexcept :
			templates(std::move(tm.templates)),
			general_po(std::move(tm.general_po)),
			specific_po(std::move(tm.specific_po)),
			general_proof(std::move(tm.general_proof)) {}

	TemplateManager& operator = (TemplateManager&& tm) noexcept {
		templates = std::move(tm.templates);
		general_po = std::move(tm.general_po);
		specific_po = std::move(tm.specific_po);
		general_proof = std::move(tm.general_proof);

		return *this;
	}

	std::vector<TClause> findAllPossilbeMatchings(const TRelation&) const;

	int indexOf(const TClause& tc) const;
};



struct RelationManager {
	std::vector<TRelation> vEDBRel;
	std::vector<TRelation> vIDBRel;

	void loadRelations(Relation*, int);
	void showRelations() const;
	std::vector<TRelation> finPossibleInst(const TPredicate&, bool onlyIDB=true) const;
};


} // namespace ALPS

#endif
