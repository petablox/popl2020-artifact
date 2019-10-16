F_key: f1,f2,f3,f4.
C_name: class5,class4,class3,class2,class1.
F_name: faculty4,faculty3,faculty2,faculty1.
level: JR,SR.
S_name: stu8,stu6,stu7,stu4,stu5,stu2,stu3,stu1.
S_key: S3,S4,S5,S6,S7,S8,S1,S2.

*Junior(level)
JR
.
*focus(F_name)
faculty1
.
*Class(C_name,F_key)
class1,f1
class2,f2
class3,f1
class4,f3
class5,f4
.
*Enroll(S_key,C_name)
S1,class1
S2,class1
S3,class2
S3,class5
S4,class2
S4,class4
S5,class3
S6,class3
S6,class2
S7,class5
S8,class4
.
*Faculty(F_key,F_name)
f1,faculty1
f2,faculty2
f3,faculty3
f4,faculty4
.
*Student(S_key,S_name,level)
S1,stu1,JR
S2,stu2,SR
S3,stu3,JR
S4,stu4,SR
S5,stu5,JR
S6,stu6,SR
S7,stu7,JR
S8,stu8,JR
.
inv1(F_key)
.
inv2(C_name)
.
inv3(S_key)
.
ans(S_name)
stu1
stu5
.
