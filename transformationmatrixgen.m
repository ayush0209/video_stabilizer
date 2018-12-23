function H = transformationmatrixgen(imgA, imgB)
%This function estimate inter-frame geometric transformation. 
%It generates 6 parameter 2D affine matrix.

%Converting frames to uint8
 imgA1=im2uint8(imgA);
 imgB1=im2uint8(imgB);
 
%Detecting Feature(Corner) Points using ORB Feature detector(FAST Corner Detector)
pA=detectORBFeatures(imgA1);
pB=detectORBFeatures(imgA1);

%Extracting Features from detected Corner Points using ORB Feature extractor(BRIEF Extractor)
[featuresimgA1, validpA]=extractORBFeatures(imgA1, pA);
[featuresimgB1, validpB]=extractORBFeatures(imgB1, pB);

%Performing feature matching between two frames to find points matched.
[pAmatched,pBmatched]=knnFeatureMatching(validpA, featuresimgA1, validpB, featuresimgB1);

%removing some ouliers from matched points.
c=1;
nn=size(pAmatched.Location,1);
pAmatchedloc=pAmatched.Location;
pBmatchedloc=pBmatched.Location;
while c<=nn
dist1= (pAmatchedloc(c,1)-pBmatchedloc(c,1))^2;
dist2= (pAmatchedloc(c,2)-pBmatchedloc(c,2))^2;
dist(c,1)=dist1+dist2;differ=abs(pAmatched.Orientation(c,1)-pBmatched.Orientation(c,1));
if ((dist(c,1)>1600)||(differ>=1))
pAmatchedloc(c,:)=0;pBmatchedloc(c,:)=0;
end
c=c+1;
end

%trans=vision.GeometricTransformEstimator();
%[Ransactransformation,ransacinliners]=step(trans,pAmatchedloc,pBmatchedloc);
%Ransactform=affine2d(Ransactransformation);
%H=Ransactform.T;

tform = estimateGeometricTransform(pBmatchedloc, pAmatchedloc, 'affine');
H = tform.T;

