//
//  fixedpoint.hpp
//  ALPS
//
//  Created by Xujie Si on 11/7/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#ifndef fixedpoint_hpp
#define fixedpoint_hpp

#include "context.h"

#include <vector>
#include <set>
#include <map>


namespace ALPS {
  
  struct FixedPoint{
    Z3_fixedpoint z3_fp;
    z3::context * pContext;
    z3::symbol defaultS;
    Z3_lbool recent;
    int prog_id;
    
    FixedPoint(ContextManager* pCM);
    
    FixedPoint(const FixedPoint&) = delete;
    
    FixedPoint(FixedPoint&& fp) noexcept :
    pContext(fp.pContext),
    z3_fp(fp.z3_fp),
    recent(fp.recent),
    defaultS(fp.defaultS),
    prog_id(fp.prog_id){
      fp.pContext = nullptr;
      fp.prog_id = -1;
    }
    
    FixedPoint& operator = (FixedPoint& fp) = delete;
    FixedPoint& operator = (const FixedPoint& fp) = delete;
    
    
    FixedPoint& operator = (FixedPoint&& fp) noexcept {
      defaultS = fp.defaultS;
      pContext = fp.pContext;
      z3_fp = fp.z3_fp;
      recent = fp.recent;
      prog_id = fp.prog_id;
      
      fp.pContext = nullptr;
      fp.prog_id = -1;
      
      return *this;
    }
    
    void set_prog_id(int id) {prog_id = id;}
    
    void add_rules(std::vector<z3::expr>& rules);
    
    void add_rule(z3::expr rule);
    
    bool query(Z3_ast);
    z3::expr get_answer();
    
    void register_relation(Z3_func_decl f) {
      Z3_fixedpoint_register_relation( *pContext, z3_fp, f);
    }
    
    ~FixedPoint() {
      if(pContext == nullptr) {
        // values have been moved, do nothing
        std::cerr << "values have been moved, do nothing" << std::endl;
      }
      else {
        Z3_fixedpoint_dec_ref(*pContext,z3_fp);
      }
    }
    
  };

}

#endif /* fixedpoint_hpp */
