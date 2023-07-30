% DEI Practical assignment 2022/23
% Objective: 3D HCI Gesture learning
% Marcos Hellin
% Daniel Asensi Roch
% Elvi Mihai Sabau Sabau
% Eva Sabater
% Vadym Formanyuk


%Cargamos el modelo donde almacenamos la informacion del modelo
load modelo.mat;
%%Cargamos la secuencia a analizar
disp("Cargando secuencia...");
load('C:\Users\danie\Desktop\Cuarto Informatica\PrimerCuatrimestre\DEI\Practicas\Practica1\Secuencias\scan3d-fw-27Feb2014-094752.mat'); % Load dataset
disp("Secuencia cargada con exito");



%Inicializamos vectores de centroides y profundidad
centroidesCompletos = [];
profundidad =  [];

%Recorremos los 60 fotogramas
for i = 1:60
    %Mostramos la imagen
    imagesc(scan3d.img(:,:,:,1));
    %Creamos una mascara de color de la imagen que estamos analizando
    maskAuxColor = createMaskColor(scan3d.img(:,:,:,i),140,250,150,220,100,250);
    imagesc(maskAuxColor);
    %Creamos la mascara de profundidad para sacar los pixeles mas cercanos 
    maskAux = createMaskDepth(scan3d.depth(:,:,i),820);
    
    imagesc(maskAux);

    %Fusionamos las dos mascaras extraidas
    maskFinal(:,:,i) = maskAuxColor & maskAux;
    hold on
    %imagesc(maskFinal(:,:,i));
    
    %Extraemos las propiedades de la imagen
    centroide = regionprops(maskFinal(: , : ,i), "Centroid", "Area", "PixelIdxList");
    %PixelIdxList Índices lineales de los píxeles de la región, devueltos como un vector de p elementos.
    %Area Número real de píxeles en la región, devuelto como un escalar.
    %Centroide Centro de masa de la región
    
    %Sacamos el valor mas cercanos de todos
    [maxValue, index] = max([centroide.Area]);
        
    %Anadimos el centroide a la lista de centroides
    centroids = cat(1,centroide.Centroid);
    
    %Tupla con la columna 
    [rw, col]=size(centroide);
    
    
%recorremos las filas
for j=1:rw
    %Si coinciden los valores de la columna y su indice debemos comprobar
    %que este detro de la matriz de imagen sino se descarta el centroide
    if (j==index)
        %Comprobamos que el centroide se encuentre dentro de nuestra imagen
        if centroids(index,1)<=480 && centroids(index,2)<=640 
            profundidad=cat(1,profundidad,scan3d.depth(fix(centroids(index,2)),fix(centroids(index,1)),i));
            %disp(profundidad);
        end
        centroidesCompletos = cat(1,centroidesCompletos, [centroids(index,2), centroids(index,1),i ]);
    end
end


%Comprobamos que al menos uno de los centroides este dentro de la imagen
    if size(centroidesCompletos)~=0
        hayCentroides=1;
          hold on
          plot(centroidesCompletos(:,1),centroidesCompletos(:,2),'r.')
          
    else
        hayCentroides=0;
    end
end


if hayCentroides==1
    despX=[];
    despY=[];
    %calculo de distancias: para ello sacamos la media de las profundidades
    %Zi iniciales
    %Zf finales
    Zi=median([profundidad(1) profundidad(2) profundidad(3)]);% coordenada z inicial
    Zf=median([profundidad(end-1) profundidad(end-2) profundidad(end-3)]);% coordenada z final
    
    despZ=(double(Zi)-double(Zf));
    for i=2:size(centroidesCompletos)
        despY=[despY,abs(centroidesCompletos(i,1)-centroidesCompletos(i-1,1))];
        despX=[despX,abs(centroidesCompletos(i,2)-centroidesCompletos(i-1,2))];
    end
    despX=median(despX);%distancia aumentada en eje x
    despY=median(despY);%distancia aumentada en eje y   
    %despZ=median(despZ);
end


implay(scan3d.img)
implay(maskFinal);

%% Determinador de tipos

datos=[despX,despY,despZ];
%El modelo es el entrenado en el clasificador
resultado = predict(modelo, datos);
switch resultado
    case 1
        disp("Movimiento detect\ado:  Desplazamiento frontal")
    case 2
        disp("Movimiento detectado:  Desplazamiento circular")
    case 3
        disp("Movimiento detectado:  Desplazamiento lateral derecha")
    case 4
        disp("Movimiento detectado:  Desplazamiento hacia arriba")
end