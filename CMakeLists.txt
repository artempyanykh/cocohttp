cmake_minimum_required(VERSION 3.24)
project(cocohttp VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 20)

set(VCPKG_ROOT "vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

add_subdirectory(src)
add_subdirectory(sample)


