cmake_minimum_required(VERSION 3.20)

project(SNetLib)

# Add Source To Root Lib Project
add_subdirectory(Source)
target_include_directories(SNetLib PRIVATE 
   Include
)

IF (WIN32)
# Find the Winsock library
find_package(WinSock REQUIRED)
# Add the Winsock include directories
include_directories(${WINSOCK_INCLUDE_DIRS})
# Link against the Winsock library
target_link_libraries(your_target_name ${WINSOCK_LIBRARIES})
ENDIF()

target_compile_definitions(SNetLib PRIVATE
    sn_debug
    sn_dyn_lib
    sn_enable_assert
    ${COMPILE_HEADER}
    ${PLATFORM_HEADER}
)
