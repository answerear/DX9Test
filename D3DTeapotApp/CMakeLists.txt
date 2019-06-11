#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(D3DTeapotApp)


# Setup project include files path
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    "${DirectX9_INCLUDE_DIR}"
    "${SDL2_INCLUDE_DIR}"
    )


# Setup project header files
set_project_files(Common ${D3D9_COMMON_PATH}/ .h)
set_project_files(App ${CMAKE_CURRENT_SOURCE_DIR}/ .h)

# Setup project source files
set_project_files(Common ${D3D9_COMMON_PATH}/ .cpp)
set_project_files(App ${CMAKE_CURRENT_SOURCE_DIR}/ .cpp)


# Setup executable project for Windows.
add_executable(
    ${BIN_NAME} WIN32
    ${SOURCE_FILES}
    )

target_link_libraries(
    ${LIB_NAME}
    ${SDL2_LIBRARY}
    ${DirectX9_LIBRARIES}
    )


# Setup install files and path for Windows.
install(TARGETS ${BIN_NAME}
    RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
    LIBRARY DESTINATION bin/debug CONFIGURATIONS Debug
    ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
    )


