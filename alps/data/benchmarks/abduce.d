P: bob,dbob,mbob,ddbob,mdbob,dmbob,mmbob,joe,djoe,mjoe,ddjoe,mdjoe,dmjoe,mmjoe.

*father(P,P)
dbob,bob
ddbob,dbob
dmbob,mbob
djoe,joe
ddjoe,djoe
dmjoe,mjoe
.
*mother(P,P)
mbob,bob
mdbob,dbob
mmbob,mbob
mjoe,joe
mdjoe,djoe
mmjoe,mjoe
.
inv(P,P)
.
grandparent(P,P)
ddbob,bob
mdbob,bob
dmbob,bob
mmbob,bob
ddjoe,joe
mdjoe,joe
dmjoe,joe
mmjoe,joe
;
bob,joe
joe,bob
bob,ddbob
dbob,bob
mbob,bob
ddbob,dbob
mdbob,dbob
dmbob,mbob
mmbob,mbob
djoe,bob
.
