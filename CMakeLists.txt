cmake_minimum_required(VERSION 3.5)

project(dwiz)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make the prefix path variable visible in cmake gui.
set(CMAKE_PREFIX_PATH "" CACHE PATH "CMake prefix path")

# Make the debug variable visible in cmake gui.
set(DWIZ_DEBUG OFF CACHE BOOL "Insert debug code.")
if(DWIZ_DEBUG)
    add_definitions(-DDWIZ_DEBUG)
endif()

# Set the output directory.
set(DWIZ_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/dist")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}")

# Add source directory to include paths.
include_directories(${CMAKE_SOURCE_DIR})

# Find qt.
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Function that copies qt library files to the output directory of the target.
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

# Find googletest.
find_package(GTest REQUIRED)

# Macro that adds the given files to the list with test source files.
# Example: add_test_files(file0.cpp file1.cpp)
macro(add_test_files)
    file(RELATIVE_PATH relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach(srcFile ${ARGN})
        if (relPath)
            list(APPEND TEST_SOURCES "${relPath}/${srcFile}")
        else()
            list(APPEND TEST_SOURCES "${srcFile}")
        endif()
    endforeach()
    if (relPath)
        set(TEST_SOURCES ${TEST_SOURCES} PARENT_SCOPE)
    endif()
endmacro()

# Add sub directories.
add_subdirectory(common)
add_subdirectory(common_qt)
add_subdirectory(client)
add_subdirectory(server)

# Add test executable.
if (TEST_SOURCES)
    add_executable(test_main ${TEST_SOURCES})
    set_target_properties(test_main
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}/test"
    )
    target_link_libraries(test_main GTest::Main)
    add_test(NAME test COMMAND test_main)
endif()
