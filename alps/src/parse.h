//
//  parse.h
//  ALPS
//
//  Created by Xujie Si on 1/16/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#ifndef parse_h
#define parse_h

#include <string>
#include <vector>
#include <set>

namespace ALPS {
  
  struct RelationValue {
  };
  
  
  struct RelationInfo {
    std::string name;
    int arity;
    std::vector<int> typeIndexes;
    
    bool isIDB;
    
    std::vector<RelationValue> vals;
    
  };
  
  
  struct TypeInfo {
    std::string name;
    std::set<std::string> values;
    
    size_t getNumOfVals() const {return values.size(); }
  };

  
} // end of namespace ALPS



#endif /* parse_h */
