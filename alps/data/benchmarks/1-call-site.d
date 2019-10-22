V: v1,v2,v3,v5,v6,v7,v8,v9,v10,v11.
H: i1,i2,h9,h11.
F: f1,f2.
C: c1,c2,c3.
M: m1,m2.
Z: z0,z1.

*points_initial(V,H)
v1,i1
v2,i2
v5,i1
v9,h9
v11,h11
.
*store(V,F,V)
v7,f2,v5
v5,f1,v1
v9,f2,v5
v9,f1,v11
.
*load(V,F,V)
v2,f2,v8
v5,f1,v10
v5,f1,v7
.
*invocation(C,H,C,M)
c1,i1,c2,m1
c3,i2,c2,m1
c2,h9,c1,m1
c3,h11,c1,m1
.
*actual(H,Z,V)
i1,z0,v5
i1,z1,v7
i2,z0,v6
i2,z1,v2
.
*formal(M,Z,V)
m1,z0,v5
m1,z1,v7
m2,z0,v3
m2,z1,v6
.
pointsto(C,V,H)
.
heappointsto(H,F,H)
i1,f1,i1
i2,f2,i1
i1,f2,i1
h9,f2,i1
.
*assign(C,V,C,V)
c2,v5,c1,v5
c2,v7,c1,v7
c2,v5,c3,v6
c2,v7,c3,v2
.
