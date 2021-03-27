project( example_app CXX)

cmake_minimum_required(VERSION 3.17)
set( CMAKE_CXX_STANDARD 20)
set( CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_ARG_PARSER} ${CONAN_LIBS_FMT})
