# Copyright (C) 2014 AnthonOS Open Source Community

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = FixMeForm
TEMPLATE = app

SOURCES  += fixmeform.cpp                               \
            qtsingleapplication/qtsingleapplication.cpp \
            qtsingleapplication/qtlocalpeer.cpp         \
            mainwindow.cpp

HEADERS  += qtsingleapplication/qtsingleapplication.h   \
            qtsingleapplication/qtlocalpeer.h           \
            mainwindow.h

FORMS    += mainwindow.ui

unix {                                                                             
    #VARIABLES                                                                     
    isEmpty(PREFIX) {                                                              
        PREFIX = /usr                                                              
    }                                                                              
    BINDIR = $$PREFIX/bin 
                                                                                   
    INSTALLS += target 
                                                                                   
    target.path = $$BINDIR                                                         
}
