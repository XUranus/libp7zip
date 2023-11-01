cmake_minimum_required (VERSION 3.14)
set(Project 7zwrapper)
project(${Project} C CXX)
set(SOURCE_DIR ${${Project}_SOURCE_DIR})

message("Project = ${Project}")
message("SOURCE_DIR = ${SOURCE_DIR}")
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("COVERAGE = ${COVERAGE}")

# message (STATUS "Build documentation open")
# include ("docs/BuildDoxygen.cmake")
# build_doxygen()

# supress MSVC/GCC warnings
if(${CMAKE_HOST_WIN32})
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
else()
    add_compile_options(-Wno-format-security)
endif()

file(
    GLOB_RECURSE
    SEVENZIP_WRAPPER_SOURCES
    "7ZipWrapper.cpp"
)

file(
    GLOB_RECURSE
    SEVENZIP_WRAPPER_HEADERS
    "7ZipWrapper.h"
)

message("SEVENZIP_WRAPPER_SOURCES = ${SEVENZIP_WRAPPER_SOURCES}")
message("SEVENZIP_WRAPPER_HEADERS = ${SEVENZIP_WRAPPER_HEADERS}")

include_directories(
    "p7zip"
)

# build a dynamic library
message("Build libvolumebackup dynamic library ${SEVENZIP_WRAPPER_DYNAMIC_LIBRARY_TARGET}")
set(SEVENZIP_WRAPPER_DYNAMIC_LIBRARY_TARGET ${Project})
add_library(
    ${SEVENZIP_WRAPPER_DYNAMIC_LIBRARY_TARGET}
    SHARED
    ${SEVENZIP_WRAPPER_SOURCES} ${SEVENZIP_WRAPPER_HEADERS}
)
set_property(
    TARGET ${SEVENZIP_WRAPPER_DYNAMIC_LIBRARY_TARGET}
    PROPERTY CXX_STANDARD 11
)

# to generate export library when build dynamic library, pass LIBRARY_EXPORT macro
target_compile_definitions(
    ${SEVENZIP_WRAPPER_DYNAMIC_LIBRARY_TARGET}
    PRIVATE -DLIBRARY_EXPORT
)

# build a static library
message("Build libsevenzipwrapper static library ${SEVENZIP_WRAPPER_STATIC_LIBRARY_TARGET}")
set(SEVENZIP_WRAPPER_STATIC_LIBRARY_TARGET ${Project}_static)
add_library(
    ${SEVENZIP_WRAPPER_STATIC_LIBRARY_TARGET}
    STATIC
    ${SEVENZIP_WRAPPER_SOURCES} ${SEVENZIP_WRAPPER_HEADERS}
)
set_property(
    TARGET ${SEVENZIP_WRAPPER_STATIC_LIBRARY_TARGET}
    PROPERTY CXX_STANDARD 11
)

# build example cli demo
message("Build 7z example cli")
add_executable(
    7zdemocli
    example.cpp
)

target_link_libraries(
    7zdemocli
    7zwrapper
)