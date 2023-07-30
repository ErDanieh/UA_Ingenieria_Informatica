% DEI Practical assignment 2014/15
% Objective: 3D HCI Gesture learning

%% Acquisition
load('./Secuencias/scan3d-o-27Feb2014-093907.mat'); % Load background

% Calculate a normal distribution for Background
scanWithNans=single(scan3d.depth);
scanWithNans(scanWithNans==0)=NaN;  % Replace 0 by Nans

meanScene=median(scanWithNans,3); % Mean calculation takig into account Nans
desvScene=std(scanWithNans,0,3); % Standard deviation calculation

% Calculate a normal distribution for Background
RedColour(:,:,:)=scan3d.img(:,:,1,:);
GreenColour(:,:,:)=scan3d.img(:,:,2,:);
BlueColour(:,:,:)=scan3d.img(:,:,3,:);

meanSceneColour(:,:,1)=median(RedColour,3); % Mean calculation takig into account Nans
meanSceneColour(:,:,2)=median(GreenColour,3); % Mean calculation takig into account Nans
meanSceneColour(:,:,3)=median(BlueColour,3); % Mean calculation takig into account Nans

desvSceneColour(:,:,1)=std(single(RedColour),0,3);
desvSceneColour(:,:,2)=std(single(GreenColour),0,3); % Mean calculation takig into account Nans
desvSceneColour(:,:,3)=std(single(BlueColour),0,3); % Mean calculation takig into account Nans

meanScene(isnan(meanScene))=0;

save('background.mat','meanScene', 'desvScene','meanSceneColour','desvSceneColour');

%load('./PracHCI/Secuencias/scan3d-fw-27Feb2014-094714.mat');
load('./Secuencias/scan3d-o-27Feb2014-093907.mat');
%% Direct Segmentation
figure;imagesc(scan3d.img(:,:,:,1)); %Show images

depthWithNans=single(scan3d.depth);
depthWithNans(depthWithNans==0)=NaN;

RedColour(:,:,:)=scan3d.img(:,:,1,:);
GreenColour(:,:,:)=scan3d.img(:,:,2,:);
BlueColour(:,:,:)=scan3d.img(:,:,3,:);


meanSceneColour=single(meanSceneColour);
maskAuxDepth = createMaskWithBS(depthWithNans,meanScene,desvScene,8);
maskAuxRed = createMaskWithBS(RedColour,meanSceneColour(:,:,1),desvSceneColour(:,:,1),2);
maskAuxGreen = createMaskWithBS(GreenColour,meanSceneColour(:,:,2),desvSceneColour(:,:,2),1);
maskAuxBlue = createMaskWithBS(BlueColour,meanSceneColour(:,:,3),desvSceneColour(:,:,3),1);

for i=1:size(maskAuxRed,3)
    maskColour(:,:,i) = maskAuxRed(:,:,i) & maskAuxGreen(:,:,i) & maskAuxBlue(:,:,i);
    maskColourDepth(:,:,i) = maskColour(:,:,i) & depthWithNans(:,:,i)<1600;
end
% Colour direct

RedSegmented=RedColour*NaN;
GreenSegmented=RedColour*NaN;
BlueSegmented=RedColour*NaN;
depthSegmented=scan3d.depth*NaN;
RGBSegmented=scan3d.img*0;


for i=1:size(maskAuxRed,3)
    imAux=RedColour(:,:,i);
    imAux2=imAux*NaN;
    imAux2(maskColourDepth(:,:,i))=imAux(maskColourDepth(:,:,i));
    RedSegmented(:,:,i)=imAux2;
    
    imAux=GreenColour(:,:,i);
    imAux2=imAux*NaN;
    imAux2(maskColourDepth(:,:,i))=imAux(maskColourDepth(:,:,i));
    GreenSegmented(:,:,i)=imAux2;
    
    imAux=BlueColour(:,:,i);
    imAux2=imAux*NaN;
    imAux2(maskColourDepth(:,:,i))=imAux(maskColourDepth(:,:,i));
    BlueSegmented(:,:,i)=imAux2;
    
    imAux=depthWithNans(:,:,i);
    imAux2=imAux*NaN;
    imAux2(maskColourDepth(:,:,i))=imAux(maskColourDepth(:,:,i));
    depthSegmented(:,:,i)=imAux2;
        
     RGBSegmented(:,:,1,i)=uint8(RedSegmented(:,:,i));
     RGBSegmented(:,:,2,i)=uint8(GreenSegmented(:,:,i));
     RGBSegmented(:,:,3,i)=uint8(BlueSegmented(:,:,i));
end

% Skin colour

for i=1:size(RGBSegmented,4)
    HSVimage=rgb2hsv(RGBSegmented(:,:,:,i));
    maskSkin(:,:,i)=HSVimage(:,:,3)>0.6;
        
end

for i=1:size(RGBSegmented,4)
    Regions=regionprops(maskSkin(:,:,i));
    reg=[];
    for k=1:length(Regions)
        reg(k)=Regions(k).Area;
    end
        [b,idx]=sort(reg,'descend');
        bb1=Regions(idx(1)).BoundingBox; % Primer blob
        bb1=ceil(bb1);
        bb2=Regions(idx(2)).BoundingBox; % Segundo blob
        bb2=ceil(bb2);
        valuesReg1=mean(mean(depthSegmented(bb1(1):bb1(1)+bb1(3),bb1(2):bb1(2)+bb1(4),i),2));
        valuesReg2=mean(mean(depthSegmented(bb2(1):bb2(1)+bb2(3),bb2(2):bb2(2)+bb2(4),i),2));
        if reg(idx(2))<500
            valuesReg2=1000;
        end
        if valuesReg1<valuesReg2
            Centroid(:,i)=Regions(idx(1)).Centroid;
        else
            Centroid(:,i)=Regions(idx(2)).Centroid;
        end
        
end

% Show Centroids
figure;
for i=1:size(RGBSegmented,4)
    imagesc(depthSegmented(:,:,i));
    hold on
    plot(Centroid(1,i),Centroid(2,i),'r.','markersize',50);
    hold off
    pause(0.5);
end
hold on
plot(Centroid(1,:),Centroid(2,:));

    


% Depth direct
maskAux = createMaskDepth(scan3d.depth(:,:,1),800);

% Colour + Depth

%% Temporal segmentation Saval-Calvo, et al. Background substraction



% Hand description 

% Bounding box

% Ellipse...

%% Tracking using description 

% Particle filter
% Kalman


%% 