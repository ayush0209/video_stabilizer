
filename = 'shaky_car.avi';
hVideoSrc = vision.VideoFileReader(filename, 'ImageColorSpace', 'Intensity');
imgA = step(hVideoSrc);

imgB = step(hVideoSrc); 
hVPlayer = vision.VideoPlayer; % Create video viewer
halphablender = vision.AlphaBlender('Operation', 'Binary mask', 'MaskSource','Input port'); 


[w, h] = deal(320, 240); % Size of the mosaic
outputView = imref2d([h,w]);

% Processing all frames in the video
movMean = step(hVideoSrc);
imgB = movMean;
imgBp = imgB;
correctedMean = imgBp;
ii = 2;
Hcumulative = eye(3);
while ~isDone(hVideoSrc)
imgA = imgB; % z^-1
imgAp = imgBp; % z^-1
imgB = step(hVideoSrc);
movMean = movMean + imgB;
% Estimate transform from frame A to frame B, and fit as an s-R-t
H = transformationmatrixgen(imgA,imgB);
Hcumulative = H* Hcumulative;
imgBp = imwarp(imgB,affine2d(Hcumulative),'OutputView',imref2d(size(imgB)));


%mask = imwarp(ones(size(imgB)), affine2d(Hcumulative), 'OutputView',imref2d(size(imgB)));
%mosaic = step(halphablender, ff, imgBp, mask);


% Displaying as color composite with last corrected frame
step(hVPlayer, imgBp);  
correctedMean = correctedMean +imgBp;
ii = ii+1;
end
correctedMean = correctedMean/(ii-2);
movMean = movMean/(ii-2);

release(hVideoSrc);
release(hVPlayer);


figure; imshowpair(movMean, correctedMean, 'montage');
title(['Raw input mean', repmat(' ',[1 50]), 'Corrected sequence mean']);