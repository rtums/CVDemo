cmake_minimum_required(VERSION 3.10)
project(OpenCVDemo)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(Stitch)
# uncomment if you have GLFW, DevIL, GLUT
#add_subdirectory(SiftGPUStitch)


add_subdirectory(Util)

add_subdirectory(Track)
add_subdirectory(Detection)
add_subdirectory(OpenCVDraw)
add_subdirectory(hog)
add_subdirectory(filter)
add_subdirectory(StereoMatching)
add_subdirectory(mbb)
add_subdirectory(hist)

# some test code for wins only
# add_subdirectory(HDRPlus)