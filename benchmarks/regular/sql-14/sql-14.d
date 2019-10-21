Attributes: IsActive,Class,Name.
Value: P,AAA,Q,CCC,R,BBB,True,False.
Id: 1,2,3,4,5,6,7,8,9.
Plan: A,B,C.

*active(Attributes)
IsActive
.
*correct(Value)
True
.
*input1(Id,Plan,Attributes,Value)
1,A,Name,AAA
2,A,Class,P
3,A,IsActive,True
4,B,Name,BBB
5,B,Class,Q
6,B,IsActive,False
7,C,Name,CCC
8,C,Class,R
9,C,IsActive,True
.
inv(Plan)
.
ans(Id,Plan,Attributes,Value)
1,A,Name,AAA
2,A,Class,P
3,A,IsActive,True
7,C,Name,CCC
8,C,Class,R
9,C,IsActive,True
.
