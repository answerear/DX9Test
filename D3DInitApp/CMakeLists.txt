#-------------------------------------------------------------------------------
# This file is part of the CMake build system for Tiny3D
#
# The contents of this file are placed in the public domain.
# Feel free to make use of it in any way you like.
#-------------------------------------------------------------------------------

set_project_name(D3DInitApp)


# Setup project include files path
include_directories(
	"${D3D9_COMMON_PATH}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
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

add_custom_command(TARGET ${BIN_NAME}
    PRE_LINK
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}
    )

# Setup install files and path for Windows.
install(TARGETS ${BIN_NAME}
    RUNTIME DESTINATION bin/debug CONFIGURATIONS Debug
    LIBRARY DESTINATION bin/debug CONFIGURATIONS Debug
    ARCHIVE DESTINATION lib/debug CONFIGURATIONS Debug
    )


