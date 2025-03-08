set(src main.c queue.c)

add_executable(${PROJECT_NAME} ${src})

set(GTEST_PATH ${PROJECT_SOURCE_DIR}/deps/googletest/include)
