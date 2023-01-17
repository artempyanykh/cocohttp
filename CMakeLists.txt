cmake_minimum_required(VERSION 3.24)

set(VCPKG_ROOT "vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(cocohttp VERSION 0.0.1)
add_subdirectory(src)
add_subdirectory(sample)


