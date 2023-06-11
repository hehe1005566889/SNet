cmake_minimum_required(VERSION 3.20)

file(GLOB_RECURSE src "*.cpp" "*.c")
add_library(SNetLib ${src})
