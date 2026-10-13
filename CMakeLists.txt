cmake_minimum_required(VERSION 3.16)
project(g4starter)

# ---------------------------------------------------------------------------
# Locate the Geant4 installation
# ---------------------------------------------------------------------------
find_package(Geant4 REQUIRED)

# ---------------------------------------------------------------------------
# Match the C++ standard used to compile Geant4, queried via geant4-config.
# This is more reliable than Geant4_CXX_STANDARD, which some installs omit.
# ---------------------------------------------------------------------------
find_program(GEANT4_CONFIG geant4-config
    HINTS ${Geant4_DIR}/../../../bin   # <install>/lib/cmake/Geant4 -> <install>/bin
    REQUIRED)

execute_process(
    COMMAND ${GEANT4_CONFIG} --cxxstd
    OUTPUT_VARIABLE GEANT4_CXX_STD
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT GEANT4_CXX_STD MATCHES "^[0-9]+$")
    message(FATAL_ERROR
        "geant4-config --cxxstd returned an unexpected value: '${GEANT4_CXX_STD}'")
endif()

set(CMAKE_CXX_STANDARD          ${GEANT4_CXX_STD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

message(STATUS "Geant4 version  : ${Geant4_VERSION}")
message(STATUS "C++ standard    : ${CMAKE_CXX_STANDARD} (from geant4-config --cxxstd)")

# Pull in Geant4 compile definitions, include paths, and link libraries
include(${Geant4_USE_FILE})

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(g4starter ${SOURCES})

target_include_directories(g4starter PRIVATE include)

target_link_libraries(g4starter PRIVATE ${Geant4_LIBRARIES})

# ---------------------------------------------------------------------------
# Binary output
# ---------------------------------------------------------------------------
set_target_properties(g4starter PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
