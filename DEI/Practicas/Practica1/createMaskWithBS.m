
function mask=createMaskWithBS(im,meanScene,desvScene,times)

    for i=1:size(im,3)
        mask(:,:,i)=abs(single(im(:,:,i))-meanScene)>(times*desvScene);
    end

end