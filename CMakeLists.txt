cmake_minimum_required(VERSION 3.20)

project(SNet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ======================================

IF (APPLE)
message(STATUS "[Info] Compile System Is Apple")
set(COMPILE_HEADER sn_unix_base)
set(PLATFORM_HEADER sn_macOS)
ELSEIF (WIN32)
message(STATUS "[Info] Compile System Is Window")
set(COMPILE_HEADER sn_winnt)
set(PLATFORM_HEADER sn_windows)
ELSEIF (LINUX)
message(STATUS "[Info] Compile System Is LINUX")
set(COMPILE_HEADER sn_unix_base)
set(PLATFORM_HEADER sn_linux)
ELSE()

ENDIF()


add_subdirectory(SNetLib)
add_subdirectory(SNetTest)