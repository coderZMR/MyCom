#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T21:38:18
#
#-------------------------------------------------

QT       += core gui

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mycom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    visualdescribe.cpp \
    data.cpp

HEADERS  += mainwindow.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    visualdescribe.h \
    visualdescribe.h \
    data.h

FORMS    += \
    visualdescribe.ui \
    mainwindow.ui

DEFINES += QT_DLL QWT_DLL
LIBS += -L"D:\Qt5.5\5.5\mingw492_32\lib" -lqwt #Release
INCLUDEPATH += D:\Qt5.5\5.5\mingw492_32\include\QWT

RESOURCES += \
    res.qrc
