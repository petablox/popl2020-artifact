country: de,se,dk.
id: 1,2,3,4.
status: untreated,treated.

*treat(status)
treated
.
*untreat(status)
untreated
.
*input1(id,country,status)
1,se,treated
2,dk,untreated
3,se,untreated
4,de,treated
.
inv(country)
.
ans(id,country,status)
1,se,treated
.
