cmake_minimum_required(VERSION 3.5.0)
project(CPT316-Simple-Compiler VERSION 0.1.0 LANGUAGES C CXX)

add_executable(CPT316-Simple-Compiler src/main.cpp)

include(CTest)
enable_testing()