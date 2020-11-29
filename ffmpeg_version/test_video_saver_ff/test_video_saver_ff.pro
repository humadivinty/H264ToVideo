TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS +=-L$$PWD/libvideo_saver -llibvideo_saver_ff
