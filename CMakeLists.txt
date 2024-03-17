cmake_minimum_required(VERSION 3.18)
project(ParaCL CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(BISON REQUIRED)
find_package(FLEX  REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(ENV{CMAKE_BUILD_TYPE} "Release")
endif()

flex_target(lexer  parsing/scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cxx DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/lexer.hxx)
bison_target(parser parsing/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cxx)

add_flex_bison_dependency(lexer parser)

add_executable(${PROJECT_NAME} main.cxx driver/driver.cxx ast/Node.cxx ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ast driver parsing)
