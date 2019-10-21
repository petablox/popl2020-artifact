V: v1,v2,v3,v5,v6,v7,v8,v9,v10,v11.
H: i1,i2,h9,h11.
F: f1,f2.
C: c1,c2,c3,c4.
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
v9,f2,v2
.
*load(V,F,V)
v2,f2,v8
v5,f1,v10
v5,f1,v7
.
*invocation(C,C,H,C,C,M)
c1,c1,i1,c2,c3,m1
c3,c1,i2,c2,c3,m1
c2,c3,h9,c1,c1,m1
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
pointsto(C,C,V,H)
c1,c1,v1,i1
c1,c1,v5,i1
c3,c1,v2,i2
c2,c3,v9,h9
c2,c3,v5,i1
c2,c3,v7,i2
c1,c1,v10,i1
c1,c1,v7,i1
c2,c3,v7,i1
c3,c1,v8,i1
c2,c3,v10,i1
.
heappointsto(H,F,H)
i1,f1,i1
i2,f2,i1
i1,f2,i1
h9,f2,i1
.
*assign(C,C,V,C,C,V)
c2,c3,v5,c1,c1,v5
c2,c3,v7,c1,c1,v7
c2,c3,v5,c3,c1,v6
c2,c3,v7,c3,c1,v2
c2,c3,v8,c3,c4,v2
c2,c3,v8,c2,c4,v2
c2,c3,v8,c2,c1,v2
.
