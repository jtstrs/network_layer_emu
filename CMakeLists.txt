cmake_minimum_required(VERSION 3.22)
project(NetworkLayerEmulator)

add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PRIVATE include)

enable_testing()
add_subdirectory(tests)
