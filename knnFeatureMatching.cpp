#include "opencvmex.hpp"
#include <stdint.h>

using namespace cv;

void checkforInputs(int nrhs,const mxArray *prhs[])
{
    if (nrhs != 4)
    {
        mexErrMsgTxt("Incorrect number of inputs. Function expects 4 inputs.");
    }
    
    if (!(mxIsUint8(prhs[1])&&mxIsUint8(prhs[3])&& mxIsStruct(prhs[0])&& mxIsStruct(prhs[2])))
    {       
        mexErrMsgTxt("Input image must be uint8.");
    }

}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{   
    checkforInputs(nrhs, prhs);// check wheteher inputs are correct.
    
    cv::Ptr<cv::Mat> description1 = ocvMxArrayToImage_uint8(prhs[1], true);
    cv::Ptr<cv::Mat> description2 = ocvMxArrayToImage_uint8(prhs[3], true);
    
    std::vector<KeyPoint> validptimg1;
    ocvStructToKeyPoints(prhs[0], validptimg1);
    
    std::vector<KeyPoint> validptimg2;
    ocvStructToKeyPoints(prhs[2], validptimg2);
    
    Ptr<DescriptorMatcher> knnmatcher= cv::DescriptorMatcher::create("BruteForce-Hamming");// pointer to DescriptorMatcher object 
         
    std::vector<std::vector<DMatch>> imatches;
    
    knnmatcher->knnMatch(*description2, *description1, imatches, 2);
    
    std::vector<DMatch> matches;
    

    int i;
    for(i=0;i<imatches.size();i++)
    {
        if((imatches[i][0].distance/imatches[i][1].distance)<0.8)
        {
            matches.push_back(imatches[i][0]);
        }
    }
   
    std::vector<KeyPoint> locationmatchedimg1(matches.size());
    std::vector<KeyPoint> locationmatchedimg2(matches.size());
      
    for(i=0;i<matches.size();i++)
    {      
       locationmatchedimg1[i].pt=validptimg1[matches[i].trainIdx].pt;
       locationmatchedimg1[i].angle=validptimg1[matches[i].trainIdx].angle;
       locationmatchedimg2[i].pt=validptimg2[matches[i].queryIdx].pt;
       locationmatchedimg2[i].angle=validptimg2[matches[i].queryIdx].angle;       
    }
     
    plhs[0] = ocvKeyPointsToStruct(locationmatchedimg1);
    plhs[1] = ocvKeyPointsToStruct(locationmatchedimg2);
    
}


    
    
