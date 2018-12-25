# video_stabilizer

# motivation
Looking for examples on electronic image stabilization implementation, I came across an example in MATLAB named "_Video Stabilization Using Point Feature Matching_" https://in.mathworks.com/help/vision/examples/video-stabilization-using-point-feature-matching.html
In the end of this webpage, there is a comparison between the mean of the raw video frames and of the corrected frames. As expected, the mean of raw video frames show that video is distorted while the mean of corrected frames depicts that the video has become distortion free.
To view this example on MATLAB, type this command "_openExample('vision/videostabilize_pm')_" and then to run the example code, command is "_videostabilize_pm_"

On closer inspection of the code written to run stabilization algorithms on full video, it is found that only first 10 frames are used to demonstrate the example. In the example, the line of the code that run loop with ii being count of number of frames (loop counter) is :-  "_while ~isDone(hVideoSrc) && ii < 10_"

Editing the code and removing restriction on ii i.e. running same set of operations on all the frames in the video, gives a very different result when compared to what is shown in MATLAB example. The mean of the corrected frames is almost as blurry as mean of raw video frames.

# description
The real-time feature-based electronic image stabilization algorithm consists of five major steps:
1) Feature detection and description
2) Feature matching
3) Motion estimation
4) Image mosaicking
5) Motion filtering

In this project, first three steps are implemented in C++ using OpenCV library. These C++ source code files are then compiled in MATLAB using a compatible C++ compiler to obtain mex (MATLAB Executable) files. OpenCV interface package consists of inbuilt OpenCV libraries, data type conversion between MATLAB and OpenCV.

Detailed description of all the algorithms in C++ files (built using OpenCV library) is present in Wiki. Files containing MATLAB code (transformationmatrixgen.m & videostabilizer.m) are well commented to provide comprehensive explanation. 

# requirement & setup
Following are required to be installed for running program on local machine:
1. MATLAB
2. Computer Vision System Toolbox in MATLAB
3. OpenCV interface in MATLAB
4. C++ compiler (Microsoft Visual C++ 2013 or higher is highly recommended)

# usage
1. Download and install Computer Vision System Toolbox from Add-ons option in top window panel of MATLAB.
2. Download and install OpenCV interface by MATLAB command "_visionSupportPackages_".
3. Setup C++ compiler using command "_mex setup c++_"
4. Download all code files in a folder and set the same folder as current working directory in MATLAB.
5. Compile all the C++ files using command "_mexOpenCV filename_", example "_mexOpenCV detectORBFeatures.cpp_".
6. Run program using MATLAB command "_videostabilizer_"
