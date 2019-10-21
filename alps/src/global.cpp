#include "defns.h"

/******************************************************************************/
/*									      */
/*	Parameters set by options and variables accessible to many routines   */
/*									      */
/******************************************************************************/

//Boolean
//**PartialOrder,		/* partial orders on variables*/
//**Compatible;		/* Compatible[i][j] = true if types i, j have
//                     at least one common value  */

char
**ConstName;		/* names of all discrete constants */


Boolean
IGNORE_NEG = false,
MissingVals   = false;	/* missing values in input? */


TypeInfo
*Type;			/* types */

Relation
fakeRelation = Nil,
*Reln,			/* relations */
*RelnOrder,      	/* order to try relations */
Target;			/* relation being induced */

int
MAXVARS	    = 52,	/* max number of variables */
MAXARGS     = 5,	/* max arity of any relation */

VERBOSITY   = 1,	/* level of output */

MaxConst    = 0,	/* no. constants */
MaxType	    = 0,	/* no. types */
MaxRel	    = 0;	/* highest relation no */
