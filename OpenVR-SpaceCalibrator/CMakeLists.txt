cmake_minimum_required(VERSION 3.10)
project(OpenVR-SpaceCalibrator)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(Eigen3_DIR ../lib/Eigen) # TODO check
add_executable(openvr-spacecalibrator Calibration.cpp Configuration.cpp EmbeddedFiles.cpp IPCClient.cpp
									  OpenVR-SpaceCalibrator.cpp UserInterface.cpp)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib/gl3w/include)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib/openvr/)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib)
target_link_libraries (openvr-spacecalibrator  Eigen3::Eigen)