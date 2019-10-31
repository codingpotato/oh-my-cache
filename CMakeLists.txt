cmake_minimum_required(VERSION 3.12)

project(oh-my-cache VERSION 0.1 DESCRIPTION "Oh my cache" LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)

function(add_test_executable)
  cmake_parse_arguments(ADD
                        OPTIONS
                        NAME
                        SOURCES
                        ${ARGN})
  add_executable(${ADD_NAME} ${ADD_SOURCES})
  target_compile_features(${ADD_NAME} PRIVATE cxx_std_17)
  target_compile_options(${ADD_NAME} PRIVATE -Werror -Wall -Wextra)
  target_link_libraries(${ADD_NAME} PRIVATE Threads::Threads)
endfunction(add_test_executable)

add_test_executable(NAME
                    vector_traversal
                    SOURCES
                    src/vector_traversal.cpp)

add_test_executable(NAME
                    parallel_traversal
                    SOURCES
                    src/parallel_traversal.cpp)

add_test_executable(NAME
                    parallel_traversal_locality
                    SOURCES
                    src/parallel_traversal_locality.cpp)

add_test_executable(NAME
                    is_bool_atomic
                    SOURCES
                    src/is_bool_atomic.cpp)

add_test_executable(NAME
                    oop
                    SOURCES
                    src/oop.cpp)

add_test_executable(NAME
                    non_oop
                    SOURCES
                    src/non_oop.cpp)

add_test_executable(NAME
                    matrix_multiply
                    SOURCES
                    src/matrix_multiply.cpp)

add_test_executable(NAME
                    matrix_multiply_locality
                    SOURCES
                    src/matrix_multiply_locality.cpp)
