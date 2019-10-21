#ifndef CONTEXT_H
#define CONTEXT_H


#include "template.h"

#include <vector>
#include <set>
#include <map>
#include <z3++.h>


namespace ALPS {


struct EDBValue {

};


struct ContextManager{
	z3::context C;


	int MaxBits;

	std::map<TypeInfo, z3::sort> sortMap;

	std::map<Relation, z3::func_decl> funcMap;
	std::map<Relation, std::set<std::vector<unsigned int>>> EDBFacts;

	void buildSorts(TypeInfo* TArr, int N);
	void buildFuncDecls(Relation* RArr, int N);

	void updateFuncDecls(Relation r);

	void loadEDBFacts(Relation* RArr, int N);

	void appendEDBConstr(Z3_fixedpoint& fp) ;
  
  void expandEDBWithKnownFacts(std::map<Relation, std::set<std::vector<unsigned int>>>&);
};


} // end of namepsace ALPS




#endif
