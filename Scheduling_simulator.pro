#-------------------------------------------------
#
# CS301 CPU scheduling project
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scheduling_simulator
TEMPLATE = app

SOURCES += \
    file_dialog.cpp \
        main.cpp \
        mainwindow.cpp \
    sub_window.cpp

HEADERS += \
    file_dialog.h \
        mainwindow.h \
    sub_window.h

FORMS += \
    file_dialog.ui \
        mainwindow.ui \
    sub_window.ui
