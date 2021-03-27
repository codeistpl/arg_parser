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
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

foreach (TEST  ${TESTS})
    get_filename_component(TEST_NAME ${TEST} NAME_WE)
    message(${TEST_NAME})
    add_executable(${TEST_NAME} ${TEST})
    target_include_directories(${TEST_NAME} PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
    target_link_libraries(${TEST_NAME} ${MODULE_NAME} GTest::GTest GTest::Main ${CONAN_LIBS_FMT})        
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
endforeach(TEST)
