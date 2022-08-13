cmake_minimum_required(VERSION 3.10)
project(OpenVR-SpaceCalibrator)
add_executable(openvr-spacecalibrator Calibration.cpp Configuration.cpp EmbeddedFiles.cpp IPCClient.cpp
									  OpenVR-SpaceCalibrator.cpp UserInterface.cpp)
