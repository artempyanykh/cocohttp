add_executable(sample1 sample1.cpp)
target_compile_features(sample1 PUBLIC cxx_std_20)
target_link_libraries(sample1 PRIVATE cocohttp)
target_include_directories(sample1 PRIVATE "${PROJECT_SOURCE_DIR}/src")
