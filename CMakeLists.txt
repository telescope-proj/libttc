cmake_minimum_required(VERSION 3.20)
project(ttc LANGUAGES C CXX)

include_directories(include)

set(SOURCES
    src/ttc.cpp
    src/etcpak/Dither.cpp
    src/etcpak/ProcessDxtc.cpp
    src/etcpak/ProcessRGB.cpp
    src/etcpak/Tables.cpp
)

add_compile_options(
  "-Wall"
  "-Werror"
  "-Wfatal-errors"
  "-ffast-math"
  "-fdata-sections"
  "-ffunction-sections"
  "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>"
  "$<$<CONFIG:RELEASE>:-O3>"
)

add_library(ttc STATIC ${SOURCES})

set_property(TARGET ttc PROPERTY C_STANDARD 99)

target_include_directories(ttc
    INTERFACE
        include
    PRIVATE
        src
)
