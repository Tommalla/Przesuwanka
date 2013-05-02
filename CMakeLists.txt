cmake_minimum_required (VERSION 2.8)

set(COMMON_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COMMON_FLAGS}")
set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_FLAGS} -D QT_NO_DEBUG_OUTPUT")

project (Przesuwanka)

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory (src)


