% Definición de los objetos Link
L(1) = Link('d', 0.317, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-177, 177]));
L(2) = Link('d', 0, 'a', 0.45, 'alpha', 0, 'offset', -pi/2, 'qlim', deg2rad([-64, 124]));
L(3) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', pi/2, 'qlim', deg2rad([-107, 158]));
L(4) = Link('d', 0.48, 'a', 0, 'alpha', -pi/2, 'offset', 0, 'qlim', deg2rad([-255, 255]));
L(5) = Link('d', 0, 'a', 0, 'alpha', pi/2, 'offset', 0, 'qlim', deg2rad([-165, 165]));
L(6) = Link('d', 0.07, 'a', 0, 'alpha', 0, 'offset', 0, 'qlim', deg2rad([-255, 255]));

% Definición del objeto SerialLink
PA10 = SerialLink([L(1) L(2) L(3) L(4) L(5) L(6)], 'name', 'PA10-6GDL');

% Pruebas del robot en diferentes posiciones
q1 = [0 -pi/2 0 0 0 0];
q2 = [0 0 -pi/2 0 0 0];
q3 = [0 0 0 pi/2 0 0];
q4 = [0 0 0 0 0 pi/2];

% Imprimir matriz jacobiana, su determinante y graficar el robot en la posición correspondiente
disp("Prueba 1:");
jacobian1 = jacob0(PA10, q1);
disp(jacobian1);
disp(det(jacobian1));
PA10.plot(q1);

disp("Prueba 2:");
jacobian2 = jacob0(PA10, q2);
disp(jacobian2);
disp(det(jacobian2));
PA10.plot(q2);

disp("Prueba 3:");
jacobian3 = jacob0(PA10, q3);
disp(jacobian3);
disp(det(jacobian3));
PA10.plot(q3);

disp("Prueba 4:");
jacobian4 = jacob0(PA10, q4);
disp(jacobian4);
disp(det(jacobian4));
PA10.plot(q4);