TEMPLATE = app
TARGET = GUI_APP

QT = core gui charts printsupport widgets

INCLUDEPATH += /Users/ian/Code/C++/DSP_Project/gui/external/qcustomplot

greaterThan(QT_MAJOR_VERSION, ) QT += widgets

SOURCES += \
    external/qcustomplot/qcustomplot.cpp\
    main.cpp \
    widgets/constellation_plot.cpp \
    widgets/power_spectrum.cpp \
    widgets/time_domain.cpp \
    window.cpp

HEADERS += \
    external/qcustomplot/qcustomplot.h\
    widgets/constellation_plot.h \
    widgets/power_spectrum.h \
    widgets/time_domain.h \
    window.h
