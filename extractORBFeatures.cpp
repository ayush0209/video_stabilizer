
#include "opencvmex.hpp"

using namespace cv;

void checkInputs(int nrhs, const mxArray *prhs[])
{
    if (nrhs != 2)
    {
        mexErrMsgTxt("Incorrect number of inputs. Function expects 2 inputs.");
    }
    
    if (!mxIsUint8(prhs[0]))
    {       
        mexErrMsgTxt("Input image must be uint8.");
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{  
    checkInputs(nrhs, prhs);
    
    cv::Ptr<cv::Mat> img = ocvMxArrayToImage_uint8(prhs[0], true);

    std::vector<KeyPoint> keypoints;
    
    ocvStructToKeyPoints(prhs[1], keypoints);
    
    Ptr<ORB> orbDescriptor = ORB::create();    
    
    Mat descriptors;    
    orbDescriptor->compute(*img, keypoints, descriptors); 

    plhs[0] = ocvMxArrayFromImage_uint8(descriptors);
    plhs[1] = ocvKeyPointsToStruct(keypoints);
}

