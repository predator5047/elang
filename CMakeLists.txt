cmake_minimum_required(VERSION 2.8)
project(elang)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/src/parser.cpp)
FLEX_TARGET(Scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/src/scanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SRCS ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} src/main.cpp
	src/ast.cpp src/value.cpp)

add_executable(erun ${SRCS})



