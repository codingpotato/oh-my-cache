function(add_test_executable)
  cmake_parse_arguments(ADD
                        OPTIONS
                        NAME
                        SOURCES
                        ${ARGN})
  add_executable(${ADD_NAME} ${ADD_SOURCES})
  target_compile_features(${ADD_NAME} PRIVATE cxx_std_17)
  target_compile_options(${ADD_NAME} PRIVATE -Werror -Wall -Wextra)
endfunction(add_test_executable)

add_test_executable(NAME
                    vector_traversal
                    SOURCES
                    vector_traversal.cpp)

add_test_executable(NAME
                    parallel_traversal
                    SOURCES
                    parallel_traversal.cpp)

add_test_executable(NAME
                    parallel_traversal_locality
                    SOURCES
                    parallel_traversal_locality.cpp)

add_test_executable(NAME
                    is_bool_atomic
                    SOURCES
                    is_bool_atomic.cpp)
