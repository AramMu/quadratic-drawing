TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14

SOURCES += main.cpp \
    quadratic.cpp \
    alg.cpp \
    circle.cpp

include(deployment.pri)
qtcAddDeployment()

    LIBS += D:\\Dependencies\\opencv_3_1_0\\x86\\mingw\\lib\\libopencv_world310.dll.a
    INCLUDEPATH +=D:\\Dependencies\\opencv_3_1_0\\include

HEADERS += \
    quadratic.h \
    alg.h \
    circle.h
