cmake_minimum_required(VERSION 3.16)
project(DSP_Project LANGUAGES CXX)

# Ensure Qt automoc features are globally enabled
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add subdirectories
add_subdirectory(backend)
add_subdirectory(gui)
