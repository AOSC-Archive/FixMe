# Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = FixMe
TEMPLATE = app

SOURCES  += main.cpp                                    \
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
                                                                                   
    INSTALLS += target autostart                                                   
                                                                                   
    target.path = $$BINDIR                                                         
                                                                                   
    autostart.path = /etc/xdg/autostart                                            
    autostart.files += $${TARGET}.desktop                                          
}
