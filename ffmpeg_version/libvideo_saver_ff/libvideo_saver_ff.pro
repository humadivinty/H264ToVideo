#-------------------------------------------------
#
# Project created by QtCreator 2020-11-23T11:23:53
#
#-------------------------------------------------

QT       -= core gui

TARGET = libvideo_saver_ff
TEMPLATE = lib

DEFINES += LIBVIDEO_SAVER_FF_LIBRARY
DEFINES += LIBVIDEO_SAVER_FFSHARED_EXPORT

INCLUDEPATH +=$$PWD/libFFmpeg/include

SOURCES += libvideo_saver_ff.cpp \
    H264ToMp4.cpp \
    tool_function.cpp

HEADERS += libvideo_saver_ff.h\
        libvideo_saver_ff_global.h \
    H264ToMp4.h \
    Tool_function.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32{
    LIBS+= -L$$PWD/libFFmpeg/lib -lavcodec -lavformat -lavutil
}
