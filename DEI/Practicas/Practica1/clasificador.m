% DEI Practical assignment 2022/23
% Clasificador de J

load DSentrenamiento.mat;
load DStest.mat;
disp("Creando modelo...");
%% Training
%secuencias entrenamiento
xtr=DSentrenamiento(:,1:3);
%clases
ytr=DSentrenamiento(:,4);
xt=DStest(:,1:3);%secuencias test
yt=DStest(:,4);%clases
% % entrenando 
disp("Realizando algoritmo")
modelo = fitcknn(xtr,ytr,'NumNeighbors',3,'Distance','cityblock');
% % test
disp("Realizando predicciones...")
resultado = predict(modelo, xt);
acierto = sum(resultado == yt)/length(yt)*100;
sp =['Acierto del modelo = ', num2str(acierto),'%'];
disp(sp)
disp("Modelo generado con exito")
save modelo.mat;