get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${MODULE_NAME} LANGUAGES CXX)

file(GLOB SRC ./*.cpp)
list(LENGTH SRC SRC_SIZE)
file(GLOB TESTS ./*_test.cpp)
list(LENGTH TESTS TESTS_SIZE)
file(GLOB MOCKS ./*_mock.cpp)
list(LENGTH MOCKS MOCKS_SIZE)

list(REMOVE_ITEM SRC ${TESTS})
#list(REMOVE_ITEM SRC ${MOCKS})

message("src" ${SRC})
message("tests" ${TESTS})
message("mocks" ${MOCKS})

#library

add_library(${MODULE_NAME} OBJECT ${SRC})
target_include_directories(${MODULE_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
add_library(ArgParser::ArgParser ALIAS ${MODULE_NAME})

#tests

add_executable(${MODULE_NAME}_tests ${TESTS})
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
message(${MODULE_NAME} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${MODULE_NAME}_tests PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
    
target_link_libraries(${MODULE_NAME}_tests ${MODULE_NAME} GTest::GTest GTest::Main fmt)

add_test(NAME ${MODULE_NAME}_tests COMMAND ${MODULE_NAME}_tests
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
