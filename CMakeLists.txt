cmake_minimum_required(VERSION 3.12)

project(oh-my-cache
        VERSION 0.1
        DESCRIPTION "Modern CPP Project Template"
        LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
