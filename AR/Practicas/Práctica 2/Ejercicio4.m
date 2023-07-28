%Ejercicio 4%

% Definición del robot PA10-6GDL
L(1) = Link('d', 0.317, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-177, 177]));
L(2) = Link('d', 0, 'a', 0.45, 'alpha', 0, 'offset', -pi/2, 'qlim', deg2rad([-64, 124]));
L(3) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', pi/2, 'qlim', deg2rad([-107, 158]));
L(4) = Link('d', 0.48, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-255, 255]));
L(5) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', 0, 'qlim', deg2rad([-165, 165]));
L(6) = Link('d', 0.07, 'a', 0, 'alpha', 0, 'offset', 0, 'qlim', deg2rad([-255, 255]));

r = SerialLink(L,'name', 'PA10-6GDL');

qh = [0 0 0 0 0 0];
qhQ = r.fkine(qh);

qe = [0 0.5236 1.5708 0 1.0472 0];
qeQ = r.fkine(qe);

qs = [0 0.7854 1.5708 0 -0.7854 0];
qsQ = r.fkine(qs);

q1 = [0 0.7854 0.7854 0 1.5708 0];
q1Q = r.fkine(q1);

q2 = [0.3491 1.5708 0.7854 -0.39270 1.0472 0];
q2Q = r.fkine(q2);


T = r.fkine(qh);
qinversa = r.ikine6s(T);
r.plot(qinversa);
Tinversa = r.fkine(qinversa);
T
qinversa
Tinversa

T1 = r.fkine(qe);
qinversa1 = r.ikine6s(T1);
r.plot(qinversa1);
Tinversa1 = r.fkine(qinversa1);
T1
qinversa1
Tinversa1

T2 = r.fkine(qs);
qinversa2 = r.ikine6s(T2);
r.plot(qinversa2);
Tinversa2 = r.fkine(qinversa2);
T2
qinversa2
Tinversa2

T3 = r.fkine(q1);
qinversa3 = r.ikine6s(T3);
r.plot(qinversa3);
Tinversa3 = r.fkine(qinversa3);
T3
qinversa3
Tinversa3

T4 = r.fkine(q2);
qinversa4 = r.ikine6s(T4);
r.plot(qinversa4);
Tinversa4 = r.fkine(qinversa4);
T4
qinversa4
Tinversa4
