cmake_minimum_required (VERSION 3.12)

project (Multithreading)
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

set(CMAKE_CXX_STANDARD 17)


add_executable(Base src/Base.cpp)
add_executable(Mutex src/Mutex.cpp)
add_executable(Condition src/Condition.cpp)
add_executable(Atom src/Atom.cpp)
add_executable(CallOnce src/CallOnce.cpp)
add_executable(PromiseFuture src/PromiseFuture.cpp)
