cmake_minimum_required (VERSION 3.12)

project (RValue)
IF (WIN32)
    add_compile_options("/std:c++17")
    add_definitions(-DWIN32)
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	MESSAGE(STATUS "Now is windows")
ELSEIF (UNIX)
	MESSAGE(STATUS "Now is UNIX-like OS's.")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

ENDIF ()

add_executable(Tuple Tuple.cpp)
