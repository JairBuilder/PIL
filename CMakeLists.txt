cmake_minimum_required(VERSION 3.18)
project(pi)

set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include_directories(./)

file(GLOB_RECURSE SOURCES "src/*.cpp")

#add_executable(main ${SOURCES} ./test/test_lexer.cpp)
#add_executable(main ${SOURCES} ./test/test_parser.cpp)
#add_executable(main ${SOURCES} ./test/test_evaluator.cpp)
#add_executable(main ${SOURCES} ./eval_repl.cpp)
add_executable(main ${SOURCES} ./test/test_vm.cpp)
