.name "Victarion"
.comment "we do not sow"


and r16, %0, r16
zjmp %:begin

back:
sti r1, %:l1, %1
sti r1, %:l2, %1
sti r1, %:l3, %1
sti r1, %:l4, %1
sti r1, %:l5, %1
sti r1, %:l6, %1
sti r1, %:l7, %1
sti r1, %:l8, %1
sti r1, %:l9, %1
sti r1, %:l10, %1
loop_back:
sti r3, r4, r4
sti r2, r4, r4
l1:	live %1
sti r3, r4, r4
sti r2, r4, r4
l2:	live %1
sti r3, r4, r4
sti r2, r4, r4
l3:	live %1
sti r3, r4, r4
sti r2, r4, r4
l4:	live %1
sti r3, r4, r4
sti r2, r4, r4
l5:	live %1
sti r3, r4, r4
sti r2, r4, r4
l6:	live %1
sti r3, r4, r4
sti r2, r4, r4
l7:	live %1
sti r3, r4, r4
sti r2, r4, r4
l8:	live %1
sti r3, r4, r4
sti r2, r4, r4
l9:	live %1
sti r3, r4, r4
sti r2, r4, r4
l10: live %1
#sub r4, r6, r4
and r16, %0, r16
zjmp %:loop_back


begin:
ld %150994944, r2
ld %128188416, r3
ld %-450, r4
ld %150, r5
ld %50, r6

begin2:
sti r1, %:flive, %1
sti r1, %:live, %1
sti r1, %:live1, %1
sti r1, %:live2, %1
sti r1, %:live3, %1
sti r1, %:live4, %1
sti r1, %:live5, %1
sti r1, %:live6, %1
sti r1, %:live7, %1

fork %:front
live: live %1
fork %:back
liveb: live %1
fork %:factory
live1:	live %1
live2:	live %1
live3:	live %1
live4:	live %1
live5:	live %1
live6:	live %1
live7:	live %1
and r16, %0, r16
zjmp %:liveb

factory:
flive:	live %1
fork %:begin2
and r16, %0, r16
zjmp %:factory


front:
sti r1, %:k1, %1
sti r1, %:k2, %1
sti r1, %:k3, %1
sti r1, %:k4, %1
sti r1, %:k5, %1
sti r1, %:k6, %1
sti r1, %:k7, %1
sti r1, %:k8, %1
sti r1, %:k9, %1
sti r1, %:l10, %1
loop_front:
sti r3, r5, r5
sti r2, r5, r5
k1:	live %1
sti r3, r5, r5
sti r2, r5, r5
k2:	live %1
sti r3, r5, r5
sti r2, r5, r5
k3:	live %1
sti r3, r5, r5
sti r2, r5, r5
k4:	live %1
sti r3, r5, r5
sti r2, r5, r5
k5:	live %1
sti r3, r5, r5
sti r2, r5, r5
k6:	live %1
sti r3, r5, r5
sti r2, r5, r5
k7:	live %1
sti r3, r5, r5
sti r2, r5, r5
k8:	live %1
sti r3, r5, r5
sti r2, r5, r5
k9:	live %1
sti r3, r5, r5
sti r2, r5, r5
k10: live %1
#add r5, r6, r5
and r16, %0, r16
zjmp %:loop_front

