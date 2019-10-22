supplier_key: S3,S1,S2.
part_id: P1,P2,P3,P4,P5,P6,P7.
part_name: PN1,PN3,PN2,PN5,PN4,PN7,PN6.

*input1(supplier_key,part_id)
S1,P1
S1,P4
S2,P2
S2,P3
S3,P5
.
*input2(part_id,part_name)
P1,PN1
P2,PN2
P3,PN3
P4,PN4
P5,PN5
P6,PN6
P7,PN7
.
ans(part_name)
PN1
PN2
PN3
PN4
PN5
.
