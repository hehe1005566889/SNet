cmake_minimum_required(VERSION 3.20)

project(SNetTest)

file(GLOB_RECURSE src "*.cpp" "*.c")
add_executable(SNetTest ${src})

add_dependencies(SNetTest SNetLib)
target_link_libraries(SNetTest PRIVATE 
    SNetLib
)

target_include_directories(SNetTest PRIVATE 
    ${CMAKE_SOURCE_DIR}/SNetLib/Include 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_compile_definitions(SNetLib PRIVATE
    sn_debug
    sn_dyn_lib
    sn_enable_assert
    ${COMPILE_HEADER}
    ${PLATFORM_HEADER}
)
