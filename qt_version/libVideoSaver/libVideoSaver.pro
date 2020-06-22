#-------------------------------------------------
#
# Project created by QtCreator 2019-11-22T10:23:45
#
#-------------------------------------------------

QT       -= core gui

TARGET = libVideoSaver
TEMPLATE = lib
CONFIG += share

DEFINES += LIBVIDEOSAVER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#生成Map文件
QMAKE_LFLAGS_RELEASE += -Wl,-Map,videoSaver.map

unix {
    target.path = /usr/lib
    INSTALLS += target
}

!unix {
#导出符号表，以便转成MSVC的lib
QMAKE_LFLAGS_RELEASE += -Wl,--export-all-symbols,--output-def,libvideoSaver.def
QMAKE_LFLAGS_DEBUG += -Wl,--export-all-symbols,--output-def,libvideoSaver.def
#QMAKE_CXXFLAGS_RELEASE += -finput-charset=GB2312 -fexec-charset=GB2312
}

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        libvideosaver.cpp \
    libAVI/cAviLib.cpp \
    libAVI/avilib.c \
    libMp4/cMp4Encode.cpp \
    videosaver.cpp \
    utilityTool/ToolFunction.cpp \
    utilityTool/utf8.c

HEADERS += \
        libvideosaver.h \
        libvideosaver_global.h \ 
    libAVI/avilib.h \
    libAVI/cAviLib.h \
    libMp4/cMp4Encode.h \
    videosaver.h \
    libvideo_typedef.h \
    utilityTool/ToolFunction.h \
    utilityTool/utf8.h




#INCLUDEPATH += $$PWD/libMp4/include
#win32:LIBS += $$PWD/lib/libmp4v2.lib

OTHER_FILES += \
    rc.rc

#resource file
win32:RC_FILE += \
    rc.rc

win32: LIBS += -L$$PWD/lib/ -lmp4v2

INCLUDEPATH += $$PWD/libMp4/include
DEPENDPATH += $$PWD/libMp4/include

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/libmp4v2.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libmp4v2.a

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/libmp4v2.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libmp4v2.lib

