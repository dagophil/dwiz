cmake_minimum_required(VERSION 3.5)

project(dwiz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Make the prefix path variable visible in cmake gui.
set(CMAKE_PREFIX_PATH "" CACHE PATH "CMake prefix path")

# Make the debug variable visible in cmake gui.
set(DWIZ_INSERT_DEBUG_CODE OFF CACHE BOOL "Insert debug code.")
if(DWIZ_INSERT_DEBUG_CODE)
    add_definitions(-DDWIZ_DEBUG)
endif()

# Set the output directory.
set(DWIZ_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/dist")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}")

# Add source directory to include paths.
include_directories(${CMAKE_SOURCE_DIR})

# Function that adds an executable and sets the output directory.
# Example: dwiz_add_executable(main main.cpp)
macro(dwiz_add_executable tar)
    add_executable(${tar} ${ARGN})
    set(DWIZ_CURRENT_OUTPUT_DIRECTORY "${DWIZ_OUTPUT_DIRECTORY}/${tar}")
    set_target_properties(${tar}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${DWIZ_CURRENT_OUTPUT_DIRECTORY}"
    )
endmacro()

# Function that copies a file from the current source directory to the current output directory.
# Example: copy_file("file.txt")
function(copy_file filename)
    if(ARGV1)
        set(filename_out ${ARGV1})
    else()
        set(filename_out ${filename})
    endif()
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${filename}" "${DWIZ_CURRENT_OUTPUT_DIRECTORY}/${filename_out}" COPYONLY)
endfunction()

# Add thread libs.
find_package(Threads REQUIRED)

# Find log4cxx.
find_path(LOG4CXX_INCLUDE_DIR log4cxx/log4cxx.h PATH_SUFFIXES log4cxx)
if (NOT LOG4CXX_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find log4cxx include dir.")
endif()
include_directories(${LOG4CXX_INCLUDE_DIR})
find_library(LOG4CXX_LIBRARY NAMES log4cxx liblog4cxx PATHS "lib")
if (NOT LOG4CXX_LIBRARY)
    message(FATAL_ERROR "Could not find log4cxx library.")
endif()

# Find qt.
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)
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
find_library(GMock_LIBRARY NAMES gmock libgmock PATHS "lib")
if(NOT GMock_LIBRARY)
    message(FATAL_ERROR "Could not find libgmock.")
endif()
find_library(GMockMain_LIBRARY NAMES gmock_main libgmock_main PATHS "lib")
if (NOT GMockMain_LIBRARY)
    message(FATAL_ERROR "Could not find libgmock_main.")
endif()

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
    enable_testing(true)
    dwiz_add_executable(test_main
        test/test_main.cpp
        ${TEST_SOURCES})
    target_link_libraries(test_main
        DwizClient
        Qt5::Test
        GTest::GTest
        ${GMock_LIBRARY}
    )
    copy_qt_lib(test_main Qt5::Core)
    copy_qt_lib(test_main Qt5::Gui)
    copy_qt_lib(test_main Qt5::Test)
    copy_qt_lib(test_main Qt5::Widgets)
    copy_file("test/.log-config" ".log-config")
    GTEST_ADD_TESTS(test_main "" AUTO)
endif()
