% Se define una matriz de transformación
T = transl(-3, 10, 10) * trotx(-90) * troty(90);

% Redondeamos la matriz
T_rounded = round(T);

% Mostramos la matriz redondeada en un gráfico
trplot(T_rounded);