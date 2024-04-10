QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    demuxthread.cpp \
    main.cpp \
    mainwindow.cpp \
    thread.cpp

HEADERS += \
    demuxthread.h \
    mainwindow.h \
    thread.h

FORMS += \
    mainwindow.ui

win32{
INCLUDEPATH += E:\Environment\ffmpeg-6.0\include\

LIBS += E:\Environment\ffmpeg-6.0\lib\avformat.lib \
        E:\Environment\ffmpeg-6.0\lib\avcodec.lib \
        E:\Environment\ffmpeg-6.0\lib\avdevice.lib \
        E:\Environment\ffmpeg-6.0\lib\avfilter.lib \
        E:\Environment\ffmpeg-6.0\lib\avutil.lib \
        E:\Environment\ffmpeg-6.0\lib\postproc.lib \
        E:\Environment\ffmpeg-6.0\lib\swresample.lib \
        E:\Environment\ffmpeg-6.0\lib\swscale.lib
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
