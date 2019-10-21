#ifndef DEFNS_H
#define DEFNS_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/******************************************************************************/
/*									      */
/*	Type definitions, including synonyms for structure pointers	      */
/*									      */
/******************************************************************************/


typedef unsigned char Var;

typedef char	Boolean;
//		Ordering;	/* valid instances are <,=,>,# */


				/* A tuple is stored as an array of int / fp.

				   * T[0] = tuple number
						+ POSMARK (pos tuples)
				   * T[i] = constant number, or fp value

				   NB: If continuous (fp) values are used,
				       type Const must be the same size as
				       float --if this is not the case, change
				       Const to long.

				   Relation tuple sets are indexed by 3D array.

				   * I[i][j][k] = no. of kth tuple with T[j] = i

				   The last entry is followed by FINISH  */


typedef int			Const,
				*Tuple;

typedef int			***Index;


typedef struct _rel_rec		*Relation;

typedef struct _type_rec	*TypeInfo;


/******************************************************************************/
/*									      */
/*	Structure definitions						      */
/*									      */
/******************************************************************************/


	/* Relation */

	/* Note:

	   Relations are represented by the (positive) tuples they contain;
	   if the closed world assumption is not in force, negative tuples
	   known not to be in the relation can be given explicitly.

	   A key specifies a sensible way that a relation can be accessed
	   by noting which arguments must have bound values.  There can
	   be any number of keys; if there are none, all possible ways
	   of accessing the relation are ok. */
	   
struct _rel_rec
{
	const char		*Name;
	int		Arity,		/* number of arguments */
			NKeys,		/* number of keys (0=all ok) */
			*Key,		/* keys, each packed in an int */
			*Type;		/* types of arguments */
	TypeInfo	*TypeRef;	/* redundant pointers to types */
	Tuple		*Pos,		/* positive tuples */
			*Neg;		/* negative tuples or Nil (CWA) */
	Index		PosIndex,	/* index for positive tuples */
			NegIndex;	/* ditto for explicit negative tuples */
	int		PosDuplicates,	/* number of duplicate pos tuples*/
			NTrialArgs,	/* number of args to try (gain) */
			NTried;		/* number of them evaluated */
//	Clause		*Def;		/* definition is array of clauses */
	Boolean		BinSym,		/* true for binary symmetric relns */
			PossibleTarget,
			**PosOrder,	/* argument order info for R() */
			**NegOrder,	/*    "       "    "    " ~R() */
			*ArgNotEq;	/* args that cannot be the same var
					   (indexed by ArgPair) */
	float		Bits;		/* current encoding cost */
};

	/* Type */

struct _type_rec
{	char		*Name;		/* type name */
	Boolean		Continuous,	/* continuous (non-discrete) */
			Ordered,	/* ordered discrete type */
			FixedPolarity;
	int		NValues,	/* number of discrete constants */
			NTheoryConsts;  /* number of theory constants */
	Const		*Value,		/* constants */
			*TheoryConst;	/* theory constants */
	int		*CollSeq;	/* CollSeq[k] = x if (global) constant
					   k is x'th const of this type */
};


#define  FP(X)			(*((float *)(&X)))


#define  Verbose(x)		if (VERBOSITY >= x)



#define  Nil			0
/* #define  false			0  */
/* #define  true			1  */
#define  Max(a,b)		( (a)>(b) ? a : b ) 
#define  Min(a,b)		( (a)<(b) ? a : b ) 

#define  ForEach(V,First,Last)	for(V=First;V<=Last;V++) 


#define  Mask			 077777777
#define  PosMark		0100000000	/* Max tuples = 16.7M */
#define  Positive(T)		((T)[0]&PosMark)


#define  ReadToEOLN		while ( getchar() != '\n' )

#define  Alloc(N,T)		(T *) pmalloc((N)*sizeof(T))
#define  AllocZero(N,T)		(T *) pcalloc(N, sizeof(T))
#define  Realloc(V,N,T)		V = (T *) prealloc(V, (N)*sizeof(T))

#define  ungetchar(A)		ungetc(A, stdin)

#define	 ArgPair(A2,A1)		(((A2-1)*(A2-2))/2 + A1-1)





/******************************************************************************/
/*									      */
/*	Various constants						      */
/*									      */
/******************************************************************************/


#define  FINISH	   10000000	/* large constant used as a terminator */

#define	 UNBOUND    0357357	/* odd marker used in interpret.c, join.c */

#define  MISSING_DISC     1	/* missing value "?" is the first constant */

#define  MISSING_FP 0.03125	/* arbitrary number used as the floating
				   point equivalent of MISSING_DISC - if
				   it clashes with a genuine data value, just
				   change this */

#define	 OUT_OF_RANGE	  2	/* denotes constant outside closed world */


/******************************************************************************/
/*									      */
/*	Synopsis of functions						      */
/*									      */
/******************************************************************************/

/* input.c */

Boolean	  ReadType();
void	  ReadTypes();
Tuple	  ReadTuple(Relation R);
Tuple	  *ReadTuples(Relation R, Boolean Pos);
Relation CreateFakeIDBRel(int arity);
Relation  ReadRelation();
void	  ReadRelations();
int	  FindType(char *N);
char	  *CopyString(const char *s);
void	  Error(int,const char* s1=NULL, const char* s2=NULL);
void	  DuplicateTuplesCheck(Relation R);
int	  CountDuplicates(Tuple *T, int N, int Left, int Right);
Boolean	  SymmetryCheck(Relation R);
char	  ReadName(char *s);
Const	  FindConstant(const char *N, Boolean MustBeThere);
int	  Number(Tuple *T);

//void	  CheckTypeCompatibility();
//Boolean	  CommonValue(int N1, Const *V1, int N2, Const *V2);

Index	  MakeIndex(Tuple *T, int N, Relation R);
void	  UnequalArgsCheck(Relation R);
Boolean	  NeverEqual(Tuple *T, Var F, Var S);

/* utility.c */

void	  *pmalloc(unsigned arg);
void	  *prealloc(void * arg1, unsigned arg2);
void	  *pcalloc(unsigned arg1, unsigned arg2);
void	  pfree(void *arg);
float	  CPUTime();


#endif
