project( example_app CXX)

set (SRC main.cpp)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ArgParser::ArgParser)
