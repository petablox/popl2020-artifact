/******************************************************************************/
/*									      */
/*	Variables defined in global.c					      */
/*									      */
/******************************************************************************/

#ifndef EXTERN_H
#define EXTERN_H


extern Boolean IGNORE_NEG,MissingVals;

extern TypeInfo *Type;
extern char **ConstName;

//extern Boolean
//**PartialOrder,
//**Compatible;

extern Relation
fakeRelation,
*Reln,
*RelnOrder,
Target;

extern int
MAXVARS,
MAXARGS,
VERBOSITY,
MaxConst,
MaxType,
MaxRel;


#endif
