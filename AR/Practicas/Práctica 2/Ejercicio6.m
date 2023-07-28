% Definición del robot PA10-6GDL y carga de parámetros dinámicos 
PA10 = DynamicParams(loadPA10Params());

% Definición de posiciones articulares
qs = [0, deg2rad(45), deg2rad(90), 0, deg2rad(-45), 0]
q1 = [0, deg2rad(45), deg2rad(45), 0, deg2rad(90), 0]
q2 = [deg2rad(20), deg2rad(90), deg2rad(45), deg2rad(-22.5), deg2rad(60), 0]

% Cálculo de torques utilizando la función rne() de Robot Toolbox
% Primera posición
tau = PA10.rne(qs, [0 0 0 0 0 0], [0 0 0 0 0 0])

% Segunda posición
tau = PA10.rne(q1, [0 0 0 0 0 0], [0 0 0 0 0 0])

% Tercera posición
tau = PA10.rne(q2, [0 0 0 0 0 0], [0 0 0 0 0 0])