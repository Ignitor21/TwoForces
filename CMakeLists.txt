cmake_minimum_required(VERSION 3.13)
project(ParaCL)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0")

flex_target (lexer  scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cxx)
bison_target(parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cxx)

add_flex_bison_dependency(lexer parser)

add_executable(${PROJECT_NAME} calc++.cxx  driver.cxx ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})