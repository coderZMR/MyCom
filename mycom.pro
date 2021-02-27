#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T21:38:18
#
#-------------------------------------------------

QT       += core gui
QT       += 3dcore 3drenderer 3dinput 3dquick qml quick

OTHER_FILES += *.qml

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
    data.cpp \
    window.cpp

HEADERS  += mainwindow.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    visualdescribe.h \
    visualdescribe.h \
    window.h \
    data.h

FORMS    += mainwindow.ui \
    visualdescribe.ui

DEFINES += QT_DLL QWT_DLL
#LIBS += -L"D:\Qt5.5\5.5\mingw492_32\lib" -lqwtd #Debug
LIBS += -L"D:\Qt5.5\5.5\mingw492_32\lib" -lqwt #Release
INCLUDEPATH += D:\Qt5.5\5.5\mingw492_32\include\QWT
#LIBS += -L"D:\UI_Design\5.1.1\mingw48_32\lib" -lqwtd
#LIBS += -L"D:\UI_Design\5.1.1\mingw48_32\lib" -lqwt
#INCLUDEPATH += D:\UI_Design\5.1.1\mingw48_32\include\Qwt

RESOURCES += \
    res.qrc

DISTFILES += \
    main.qml
