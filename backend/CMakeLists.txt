cmake_minimum_required(VERSION 3.14)
project(MyDSPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Backend becomes a static library now
add_library(backend STATIC
    src/signalClass.cpp
    src/kiss_fft_Wrapper.cpp
    include/signalClass.h
    include/kiss_fft_wrapper.h
    external/kissfft/kiss_fft.c
    external/kissfft/kiss_fftr.c
)

target_include_directories(backend PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/kissfft
)
