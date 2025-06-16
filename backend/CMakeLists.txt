cmake_minimum_required(VERSION 3.14)
project(MyDSPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Source files
set(SOURCES
    src/main.cpp
    src/signalClass.cpp
    src/kiss_fft_Wrapper.cpp
    external/kissfft/kiss_fft.c
)

add_executable(MyDSPApp ${SOURCES})

# Include paths
target_include_directories(MyDSPApp PRIVATE
    include
    external/kissfft
)

#target_link_libraries(MyDSPApp Qt6::Widgets)
