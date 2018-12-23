
#include "opencvmex.hpp"

using namespace cv;

void checkInputs(int nrhs, const mxArray *prhs[])
{
    if (nrhs != 1)
    {
        mexErrMsgTxt("Incorrect number of inputs. Function expects 1 input.");
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

    Ptr<ORB> orbDetector = cv::ORB::create();
      
    std::vector<KeyPoint> keypoints; 
    
    orbDetector->detect(*img, keypoints); 
        
    plhs[0] = ocvKeyPointsToStruct(keypoints);  
}

