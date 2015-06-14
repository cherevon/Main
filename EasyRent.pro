#-------------------------------------------------
#
# Project created by QtCreator 2014-02-24T01:51:24
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyRent
TEMPLATE = app


SOURCES += main.cpp\
    PropertyStorage.cpp \
    PriorityQuery.cpp \
    AbstractQuery.cpp \
    ResponseQuery.cpp \
    MainWindow.cpp \
    FormPriorityShow.cpp \
    AppInfo.cpp \
    FormPriorityCreate.cpp \
    AuthWidget.cpp \
    AuthUnit.cpp

HEADERS  += \
    Queries.h \
    PropertyStorage.h \
    PriorityQuery.h \
    AbstractQuery.h \
    ResponseQuery.h \
    MainWindow.h \
    FormPriorityShow.h \
    Interfaces.h \
    AppInfo.h \
    FormPriorityCreate.h \
    AuthWidget.h \
    AuthUnit.h

FORMS    += \
    FormPriorityShow.ui \
    MainWindow.ui \
    FormPriorityCreate.ui \
    AuthWidget.ui

RESOURCES += \
    resources.qrc
