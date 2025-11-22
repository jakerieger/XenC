cmake_minimum_required(VERSION 3.14)
project(XenC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

# Fetch 3rd party dependencies
include(cmake/fetch_deps.cmake)
include(vendor/vendor.cmake)

# Build sandbox test app
add_subdirectory(sandbox)

file(GLOB sources ${SRC_DIR}/*.h ${SRC_DIR}/*.c)

add_library(xenc STATIC
    ${VENDOR_SOURCES}
    ${sources}
)

target_link_libraries(xenc PUBLIC
    glfw
    glm::glm
)

target_include_directories(xenc PUBLIC
    ${SRC_DIR}
    ${VENDOR_DIR}
)