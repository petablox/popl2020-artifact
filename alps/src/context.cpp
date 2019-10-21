
#include "context.h"
#include "extern.h"

#include <sstream>
#include <algorithm>
#include <map>

namespace ALPS {

namespace {

int estimateBits(int sz) {
	int K = 1;
	while (sz) {
		++K;
		sz >>= 1;
	}

	return K;
}


//std::string translate(unsigned int x) {
//	std::stringstream ss;
//	ss << ConstName[x];
//
//	return ss.str();
//}

} // end of anonymous namespace

void ContextManager::buildSorts(TypeInfo* TArr, int N) {
	const int START = 1; // to confirm
	const int END = N; // to confirm

	for(int i=START; i < END; ++i) {
		TypeInfo t = TArr[i];

		int K = estimateBits(t->NValues);
		z3::sort s = C.bv_sort( K );

		sortMap.insert( std::make_pair(t, s) );
	}

	MaxBits = estimateBits(MaxConst);
}

void ContextManager::updateFuncDecls(Relation rel){
	//std::cout << "process " << rel->Name << std::endl;

	z3::sort_vector sv(C);

	for(int j=1; j <= rel->Arity; ++j){
		/*
		TypeInfo t = rel->TypeRef[j];
		auto it = sortMap.find(t);
		if(it == sortMap.end()) {
			std::cerr << "ERROR, buildFuncDecls get unknown type: " << t->Name << std::endl;
		}

		sv.push_back( it->second );
		*/

		sv.push_back( C.bv_sort(MaxBits) );
	}

	z3::func_decl pred = C.function(rel->Name, sv, C.bool_sort());

	auto it = funcMap.find(rel);
	if(it != funcMap.end()) {
		funcMap.erase(it);
	}
	auto result = funcMap.insert( std::make_pair(rel, pred) );
	if(!result.second) {
		std::cerr << "update FuncDecls failed for " << rel->Name << std::endl;
	}
}

void ContextManager::buildFuncDecls(Relation* RArr, int N) {
	const int START = 0; // to confirm
	const int END = N; // to confirm

	for(int i=START; i < END; ++i) {
		Relation rel = RArr[i];

		if(rel->Name[0] == '=' || rel->Name[0] == '>') {
			continue;
		}

		updateFuncDecls(rel);
	}
}


void ContextManager::loadEDBFacts(Relation* RArr, int N) {
	for(int i=0; i<N; ++i) {
		Relation rel = RArr[i];
		if(rel->Name[0] == '=' || rel->Name[0] == '>') {
			continue;
		}

		std::set<std::vector<unsigned int>> st;


		if(!(rel->PossibleTarget)) {
			Tuple* tp = rel->Pos;
			while(*tp){

				std::vector<unsigned int> v;
				for(int j=1; j <= rel->Arity; ++j){
					v.push_back( (unsigned int) (*tp)[j] );
				}

				st.insert(std::move(v));

				++tp;
			}
		}

		EDBFacts.insert( std::make_pair(rel, std::move(st)) );
	}
}


void ContextManager::appendEDBConstr(Z3_fixedpoint& fp) {
	for (auto pr : EDBFacts) {
		Relation rel = pr.first;

		auto it = funcMap.find(rel);
		if (it == funcMap.end()) {
			std::cerr << "ERROR, buildEDBFacts got unknown relation : "
					<< rel->Name << std::endl;
		}

		z3::func_decl f = it->second;

		const std::set<std::vector<unsigned int> >& st = pr.second;

		for (auto v : st) {
			Z3_fixedpoint_add_fact(C, fp, f, (unsigned int)v.size(), v.data());
		}
	}
}

  void ContextManager::expandEDBWithKnownFacts(std::map<Relation, std::set<std::vector<unsigned int>>>& known_idbs){
    for(auto& pr : known_idbs) {
      auto it = EDBFacts.find(pr.first);
      if(it == EDBFacts.end()) {
        EDBFacts.insert( std::move(pr) );
      }
      else{
        for(auto & v : pr.second) {
          it->second.insert(std::move(v));
        }
      }
    }
  }

} // end of namepsace ALPS
