project(template_cmake_project)
cmake_minimum_required(VERSION 3.17)

add_compile_options( -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast 
                    -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion 
                    -Wsign-conversion -Wmisleading-indentation  -Wduplicated-cond -Wduplicated-branches 
                    -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/gcovr.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

enable_testing()
add_subdirectory(arg_parser)
add_subdirectory(test_app)
