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
DEFINES += FFMPEG_VERSION_4

INCLUDEPATH +=$$PWD/libFFmpeg-4.2.4/include

SOURCES += libvideo_saver_ff.cpp \
    H264ToMp4.cpp \
    tool_function.cpp

HEADERS += libvideo_saver_ff.h\
        libvideo_saver_ff_global.h \
    H264ToMp4.h \
    Tool_function.h

#resource file
win32:RC_FILE += \
    rc.rc

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32{
    LIBS+= -L$$PWD/libFFmpeg-4.2.4/lib -lavcodec -lavformat -lavutil
}

!unix {
#导出符号表，以便转成MSVC的lib
QMAKE_LFLAGS_RELEASE += -Wl,--export-all-symbols,--output-def,libvideo_saver_ff.def
QMAKE_LFLAGS_DEBUG += -Wl,--export-all-symbols,--output-def,libvideo_saver_ff.def
#QMAKE_CXXFLAGS_RELEASE += -finput-charset=GB2312 -fexec-charset=GB2312
}
