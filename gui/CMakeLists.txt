cmake_minimum_required(VERSION 3.16)
project(GUI_APP LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the required Qt modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Charts PrintSupport Widgets)

# Add your executable
add_executable(GUI_APP
    main.cpp
    window.cpp
    widgets/constellation_plot.cpp
    widgets/power_spectrum.cpp
    widgets/time_domain.cpp
    external/qcustomplot/qcustomplot.cpp

    window.h
    widgets/constellation_plot.h
    widgets/power_spectrum.h
    widgets/time_domain.h
    external/qcustomplot/qcustomplot.h
)

# Set include directories
target_include_directories(GUI_APP PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/external/qcustomplot
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
)

# Link against Qt libraries
target_link_libraries(GUI_APP PRIVATE
    backend
    Qt6::Core
    Qt6::Gui
    Qt6::Charts
    Qt6::PrintSupport
    Qt6::Widgets
)

find_package(Qt<QTVERSION> COMPONENTS Widgets)
