
#include "template.h"
#include "matching.h"


#include <vector>
#include <map>
#include <iostream>
#include <sstream>


namespace ALPS {

namespace {
//bool testConsistency(const IClause& cl) {
//	return false;
//}

bool checkAndUpdate(const TPredicate& pred,
		const TRelation& rel,
		std::map<int, Relation>& relMap,
		std::map<int, TypeInfo>& tyMap) {

	if(rel.getArity() != pred.arity) {
		//std::cout << "checkAndUpdate: arity does not match\n";
		return false;
	}

	// std::map<int, Relation>::iterator
	auto it = relMap.find(pred.pid);
	if(it != relMap.end() && rel.getRel() != it->second) {
		//std::cout << "checkAndUpdate: relation is not expected\n";
		//std::cout << "pred=" << pred.toStr() << ", current rel:" << rel.getRelName()
		//		<< ", expected rel:" << it->second->Name << std::endl;
 		return false;
	}

	for(int i=0; i < pred.arity; ++i) {
		int v = pred.vdom[i];
		auto it2 = tyMap.find(v);
		if(it2 != tyMap.end() && it2->second != rel.getType(i)) {
			//std::cout << "checkAndUpdate: type is not expected\n";

			return false;
		}
	}

	// passed arity / type checks, now updates

	if(it == relMap.end()){
		relMap.insert( std::make_pair(pred.pid, rel.getRel()) );
	}

	for(int i=0; i < pred.arity; ++i) {
		int v = pred.vdom[i];
		auto it2 = tyMap.find(v);
		if(it2 == tyMap.end()) {
			tyMap.insert( std::make_pair(v, rel.getType(i)) );
		}
        else if(it2->second != rel.getType(i)) {
            return false;
        }
	}

	return true;
}

} // end of anonymous namespace

void Matching::exploreBody(const TClause& tc, std::vector<TRelation>& rels,
		std::map<int, Relation>& relMap, std::map<int, TypeInfo>& tyMap, std::vector<std::vector<TRelation>>& results) const {

	if( rels.size() == tc.vbody.size() ) {
		results.push_back( rels );
		return;
		//return true;
	}
	int k = (int) rels.size();
	const TPredicate & pred = tc.vbody[k];

	std::vector<TRelation> relCandidates = relm.finPossibleInst(pred, false);


	// make a local copy for each map for later backtracking if necessary
	std::map<int, Relation> localRelMap = relMap;
	std::map<int, TypeInfo> localTyMap = tyMap;

	for(const TRelation& r : relCandidates) {
		if (checkAndUpdate(pred, r, relMap, tyMap)) {
			rels.push_back(r);
			exploreBody(tc, rels, relMap, tyMap, results);
			rels.pop_back();
		}

		// restore the map status
		relMap = localRelMap;
		tyMap = localTyMap;
	}
}

std::vector<IClause> Matching::findMatchingsWithTemplate(const TRelation& rel,
		const TClause& tc) const {

	std::vector<IClause> matchings;

	std::map<int, Relation> relMap;
	std::map<int, TypeInfo> tyMap;

	std::vector<TRelation> tmp_vr;
	std::vector<std::vector<TRelation>> vvr;
	if (checkAndUpdate(tc.hd, rel, relMap, tyMap)) {
		exploreBody(tc, tmp_vr, relMap, tyMap, vvr);
		for (std::vector<TRelation>& vr : vvr) {
			matchings.push_back(IClause(tc, rel, vr));
		}
	}

	return matchings;
}


std::vector<IClause> Matching::findAllMatchings(const TRelation & rel) const {
	std::vector<IClause> matchings;

	std::vector<TClause> candidates = tm.findAllPossilbeMatchings(rel);

	for(const TClause& tc : candidates) {
		for(IClause& x : findMatchingsWithTemplate(rel, tc)){
			matchings.push_back( std::move(x) );
		}
	}

	return matchings;
}


void Matching::work() {
	std::stringstream ss;

	ss << "Template Stats: ";
	for(TRelation& rel : relm.vIDBRel) {
		ss << rel.getRelName() << ": ";
		//std::cout << "Explore IDB: " << rel.getRelName() << std::endl;

		const std::vector<IClause>& res = findAllMatchings(rel);

		ss << res.size() << ", ";
		//std::cout << "Possible instantiations: " << res.size() << std::endl;
		//std::cout << "after findAllMatchings:" << std::endl;
		//for(const IClause& icl : res) {
		//	icl.explain();
		//}
	}

	std::cout << ss.str() << std::endl;
}

}  // end of namespace ALPS

