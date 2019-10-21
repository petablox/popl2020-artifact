Inv: 1,2,3,4,5.
Demand: d1,d2,d3.
Company: google,facebook,linkedin,yahoo,non.

*In(Inv,Demand,Company,Company)
1,d1,google,facebook
2,d1,non,linkedin
3,d2,google,non
4,d2,non,yahoo
5,d3,google,non
.
*not_null(Company)
google
facebook
linkedin
yahoo
.
Out(Company,Demand)
facebook,d1
google,d1
google,d2
google,d3
linkedin,d1
yahoo,d2
.
