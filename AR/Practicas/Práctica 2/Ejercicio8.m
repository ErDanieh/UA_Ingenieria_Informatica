% Se cargan los parámetros dinámicos del robot PA-10
r = DynamicParams(loadPA10Params());

% Se definen las posiciones articulares en radianes para tres casos distintos
% [Base, Shoulder, Elbow, Wrist1, Wrist2, Wrist3]
qs = [0, deg2rad(45), deg2rad(90), 0, deg2rad(-45),0];
q1 = [0, deg2rad(45), deg2rad(45), 0, deg2rad(90),0];
q2 = [deg2rad(20), deg2rad(90), deg2rad(45),deg2rad(-22.5), deg2rad(60), 0];

% Se añade una carga al robot en su extremo y se obtiene la fuerza gravitacional ejercida en cada caso
r.payload(2.5, [0, 0, 0.1]);
Res0 = r.gravload(qs);
Res1 = r.gravload(q1);
Res2 = r.gravload(q2);

% Se calcula el torque necesario para contrarrestar la gravedad en cada posición, con una fuerza en la base de 1N y cero en el resto
Vqs_0 = r.itorque(qs,[1 0 0 0 0 0]);
Vq1_0 = r.itorque(q1,[1 0 0 0 0 0]);
Vq2_0 = r.itorque(q2,[1 0 0 0 0 0]);

% Se añade una carga en una posición ligeramente desplazada y se obtiene la fuerza gravitacional en cada caso
r.payload(2.5,[0.5, 0, 0.1]);
Res0 = r.gravload(qs)
Res1 = r.gravload(q1)
Res2 = r.gravload(q2)

% Se calcula el torque necesario para contrarrestar la gravedad en cada posición, con una fuerza en la base de 1N y cero en el resto
Vqs_1 = r.itorque(qs,[1 0 0 0 0 0])
Vq1_1 = r.itorque(q1,[1 0 0 0 0 0])
Vq2_1 = r.itorque(q2,[1 0 0 0 0 0])