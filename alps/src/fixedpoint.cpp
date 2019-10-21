//
//  fixedpoint.cpp
//  ALPS
//
//  Created by Xujie Si on 11/7/17.
//  Copyright © 2017 Xujie Si. All rights reserved.
//

#include "fixedpoint.hpp"


namespace ALPS {
  
  FixedPoint::FixedPoint(ContextManager* pCM) : pContext(&(pCM->C)), defaultS(pContext->str_symbol("defaultS")) {
    z3_fp = Z3_mk_fixedpoint( *pContext );
    Z3_fixedpoint_inc_ref(*pContext,z3_fp);
    
    recent = Z3_L_UNDEF;
    // register relation definitions
    for (auto pr : pCM->funcMap) {
      Z3_fixedpoint_register_relation(*pContext, z3_fp, pr.second);
    }
    
    pCM->appendEDBConstr(z3_fp);
    
    prog_id = -1;
    
  }
  
  void FixedPoint::add_rules(std::vector<z3::expr>& rules) {
    for (z3::expr& r : rules) {
      Z3_fixedpoint_add_rule(*pContext, z3_fp, r, defaultS);
    }
  }
  
  void FixedPoint::add_rule(z3::expr rule) {
    Z3_fixedpoint_add_rule(*pContext, z3_fp, rule, defaultS);
  }
  
  bool FixedPoint::query(Z3_ast Q) {
    recent = Z3_fixedpoint_query( *pContext, z3_fp, Q);
    if(recent == Z3_L_UNDEF) {
      std::cerr << "query result is UNDEF" << std::endl;
    }
    return recent == Z3_L_TRUE;
  }
  
  z3::expr FixedPoint::get_answer(){
    if(recent != Z3_L_TRUE) {
      std::cerr << "ERROR: cannot get_answer unless recent status is true" << std::endl;
    }
    
    Z3_ast ast_res = Z3_fixedpoint_get_answer( *pContext, z3_fp);
    z3::expr detailed_res( *pContext, ast_res);
    
    return detailed_res;
  }

}
