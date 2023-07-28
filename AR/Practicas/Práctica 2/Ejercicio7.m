% EJERCICIO PRACTICO 7%

% Creamos una instancia de la clase DynamicParams y cargamos los parámetros del robot PA10
r = DynamicParams(loadPA10Params())

% Definimos tres posiciones articulares (en radianes) del robot
qs = [0, deg2rad(45), deg2rad(90), 0, deg2rad(-45),0]
q1 = [0, deg2rad(45), deg2rad(45), 0, deg2rad(90),0]
q2 = [deg2rad(20), deg2rad(90), deg2rad(45),deg2rad(-22.5), deg2rad(60), 0]

% Definimos la gravedad en el eje z (en m/s^2)
r.gravity = [0 0 1.62]

% Calculamos la carga gravitatoria en las tres posiciones articulares
G0 = r.gravload(qs)
G1 = r.gravload(q1)
G2 = r.gravload(q2)

% Calculamos los torques inerciales en la posición inicial (qs) para 3 configuraciones distintas de la matriz de inercia
M0_0 = r.itorque(qs,[1 0 0 0 0 0])
M0_1 = r.itorque(qs,[1 1 0 0 0 0])
M0_2 = r.itorque(qs,[1 1 1 0 0 0])

% Calculamos los torques inerciales en la posición q1 para 3 configuraciones distintas de la matriz de inercia
M1_0 = r.itorque(q1,[1 0 0 0 0 0])
M1_1 = r.itorque(q1,[1 1 0 0 0 0])
M1_2 = r.itorque(q1,[1 1 1 0 0 0])

% Calculamos los torques de Coriolis en la posición inicial (qs) para 2 configuraciones distintas de las velocidades articulares
C0_1 = r.coriolis(qs, [0 pi 0 0 0 0])
C0_2 = r.coriolis(qs, [pi pi 0 0 0 0])

% Calculamos los torques de Coriolis en la posición q1 para 2 configuraciones distintas de las velocidades articulares
C1_1 = r.coriolis(q1, [0 pi 0 0 0 0])
C1_2 = r.coriolis(q1, [pi pi 0 0 0 0])