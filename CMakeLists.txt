#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)


set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../" CACHE PATH "Tiny3D install prefix")

project(DX9Test)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif ()

if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()


set(TINY3D_OS "")

if (WIN32)
    # Windows
    message(STATUS "Platform : Windows")

    add_definitions(-DD3D9_OS_WINDOWS)
    add_definitions(-DD3D9_OS_DESKTOP)
    add_definitions(-D_HAS_EXCEPTIONS=0)

    set(SDL2LIB_SUFFIXES "prebuilt/win32/${MSVC_CXX_ARCHITECTURE_ID}")
    
    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif (ANDROID)
    # Android
    message(FATAL_ERROR "Platform : Android not supported !!!")
elseif (APPLE AND IOS)
    # iOS
    message(FATAL_ERROR "Platform : iOS not supported !!!")
elseif (APPLE AND NOT IOS)
    # Mac OS X
    message(FATAL_ERROR "Platform : Mac OS X not supported !!!")
elseif (UNIX AND NOT APPLE)
    # Linux
    message(FATAL_ERROR "Platform : Linux not supported !!!")
endif (WIN32)


if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-DT3D_OS_X64)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    add_definitions(-DT3D_OS_X86)
endif ()

# Set all relative directory
#set(TINY3D_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin/${TINY3D_OS}" CACHE PATH "Tiny3D binary path")
#set(TINY3D_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/${TINY3D_OS}" CACHE PATH "Tiny3D library path")
#set(TINY3D_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Tiny3D include path")
#set(TINY3D_RES_DIR "${CMAKE_INSTALL_PREFIX}/resources" CACHE PATH "Tiny3D resourcs path")

# Set this directory for debugging app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TINY3D_OS}" CACHE STRING "Tiny3D binaries files" FORCE)

message(STATUS "Runtime dir : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} BUILTTYPE)
    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/bin/${TINY3D_OS}/${OUTPUTCONFIG}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${TINY3D_OS}/${OUTPUTCONFIG}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${BUILTTYPE} "${PROJECT_SOURCE_DIR}/lib/${TINY3D_OS}/${OUTPUTCONFIG}")
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# Set cmake module path.
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Packages"
    )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

include(FindPkgMacros)
include(ProjectCMakeModule)

# Find SDL2 library for all projects.
set(SDL2DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/SDL2" CACHE PATH "SDL2 library path")
find_package(SDL2)

if (NOT SDL2_FOUND)
    message(FATAL_ERROR "Cound not find dependency: SDL2")
endif ()

# Find DirectX 9 for all projects.
find_package(DirectX)

if (NOT DirectX9_FOUND)
    message(FATAL_ERROR "Could not find dependency: DirectX 9")
endif ()

set(D3D9_COMMON_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Common")

add_subdirectory(D3DInitApp)
add_subdirectory(D3DCubeApp)
add_subdirectory(D3DTeapotApp)
add_subdirectory(D3DXCreateApp)
add_subdirectory(D3DColorTriangleApp)

