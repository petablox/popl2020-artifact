#ifndef MATCHING_H
#define MATCHING_H

#include "template.h"
#include <vector>
#include <map>

namespace ALPS {



struct Matching {

  // all templates
  TemplateManager tm;

  // Relation Definitions
  RelationManager relm;

  /*
    - for each template, use DFS to enumerate all possible matches with arity / type pruning

    - each matching/instantiation is a candidate rule, eliminate inconsistent ones

    - enumerate K consistent programs
    -- in case of no consistent programs, mutate templates and try again

   */

  std::vector<IClause> findAllMatchings(const TRelation & rel) const;

  std::vector<IClause> findMatchingsWithTemplate(const TRelation& rel, const TClause& tc) const;

  void exploreBody(const TClause& tc,
		  std::vector<TRelation>& rels,
		  std::map<int, Relation>& relMap,
		  std::map<int, TypeInfo>& tyMap,
		  std::vector<std::vector<TRelation>>& results) const;

  void work();
  //void work2();
};




}// end of namespace ALPS

#endif
