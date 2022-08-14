cmake_minimum_required(VERSION 3.10)
project(OpenVR-SpaceCalibrator)

add_library(gl3w STATIC ../lib/gl3w/src/gl3w.c)
target_include_directories(gl3w PRIVATE ../lib/gl3w/include)
add_library(imgui STATIC ../lib/imgui/imgui.cpp ../lib/imgui/imgui_draw.cpp ../lib/imgui/imgui_impl_glfw.cpp
						 ../lib/imgui/imgui_impl_opengl3.cpp)
target_include_directories(imgui PRIVATE ../lib/gl3w/include)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
set(Eigen3_DIR ../lib/Eigen) # TODO check

find_package(glfw3 REQUIRED NO_MODULE)

add_executable(openvr-spacecalibrator Calibration.cpp Configuration.cpp EmbeddedFiles.cpp IPCClient.cpp
									  OpenVR-SpaceCalibrator.cpp UserInterface.cpp)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib/gl3w/include)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib/openvr/)
target_include_directories(openvr-spacecalibrator PRIVATE ../lib)
target_link_libraries (openvr-spacecalibrator Eigen3::Eigen)
target_link_libraries (openvr-spacecalibrator gl3w)
target_link_libraries (openvr-spacecalibrator glfw)
target_link_libraries (openvr-spacecalibrator imgui)
target_link_libraries (openvr-spacecalibrator ${CMAKE_SOURCE_DIR}/../lib/openvr/lib/linux64/libopenvr_api.so)