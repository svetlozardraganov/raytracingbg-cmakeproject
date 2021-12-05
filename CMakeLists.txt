# CMakeList.txt : CMake project for RaytracingBG_CMakeProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("RaytracingBG_CMakeProject")

# Add source to this project's executable.
add_executable (RaytracingBG_CMakeProject "main.cpp" "camera.cpp" "camera.h" "color.h" "constants.h" "geometry.cpp" "geometry.h" "matrix.cpp" "matrix.h" "sdl.cpp" "sdl.h" "shading.cpp" "shading.h" "util.h" "vector.h")


# TODO: Add tests and install targets if needed.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(RaytracingBG_CMakeProject ${SDL2_LIBRARIES})