% EJERCICIO PRACTICO 3%

% Datos 
%Primero, se definen los parámetros del robot y sus límites articulares
L(1) = Link('d', 0.317, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-177, 177]));
L(2) = Link('d', 0, 'a', 0.45, 'alpha', 0, 'offset', -pi/2, 'qlim', deg2rad([-64, 124]));
L(3) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', pi/2, 'qlim', deg2rad([-107, 158]));
L(4) = Link('d', 0.48, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-255, 255]));
L(5) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', 0, 'qlim', deg2rad([-165, 165]));
L(6) = Link('d', 0.07, 'a', 0, 'alpha', 0, 'offset', 0, 'qlim', deg2rad([-255, 255]));


pa10 = SerialLink(L,'name', 'PA10-6GDL');

% Posicion de home
figure(1);
qh = deg2rad([0 0 0 0 0 0]);
qhQ = pa10.fkine(qh);
pa10.plot(qh);
qhQ

% Posicion de escape
figure(2);
qe =deg2rad([0 30 90 0 60 0]);
qeQ = pa10.fkine(qe);
pa10.plot(qe);
qeQ


% Posicion de seguridad
figure(3);
qs = deg2rad([0 45 90 0 -45 0]);
qsQ = pa10.fkine(qs);
pa10.plot(qs);
qsQ

% Posicion q1
figure(4);
q1 = deg2rad([0 45 45 0 90 0]);
q1Q = pa10.fkine(q1);
pa10.plot(q1);
q1Q


% Posicion q2
figure(5);
q2 = deg2rad([20 90 45 -22.5 60 0]);
q2Q = pa10.fkine(q2);
pa10.plot(q2);
q2Q