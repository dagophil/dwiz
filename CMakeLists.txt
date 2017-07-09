cmake_minimum_required(VERSION 3.5)

project(dwiz)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make the prefix path variable visible in cmake gui.
set(CMAKE_PREFIX_PATH "" CACHE PATH "CMake prefix path")

# Set the output directory.
set(DWIZ_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/dist")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}")

# Add source directory to include paths.
include_directories(${CMAKE_SOURCE_DIR})

# Find qt and copy the libs.
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Copy qt library files to the output directory of the target.
# Example: copy_qt_lib(main Qt5::Core)
function(copy_qt_lib tar libname)
    add_custom_command(
        TARGET ${tar}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${libname}>
            $<TARGET_FILE_DIR:${tar}>
    )
endfunction()

# Add sub directories.
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)

