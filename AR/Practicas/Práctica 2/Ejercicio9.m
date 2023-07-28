% EJERCICIO PRACTICO 9%


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

% Pedazo plots. %
TR1 = jtraj(qh, q1, 50)
r.plot(TR1);

TR2 = jtraj(qh, q2, 50)
r.plot(TR2);

TR3 = jtraj(qh, qs, 50)
r.plot(TR3);


% [q , qd, qdd] = jtraj(qh, q2, 50); %
% [q , qd, qdd] = jtraj(qh, qs, 50); %
[q , qd, qdd] = jtraj(qh, qs, 50);

plot(qd);