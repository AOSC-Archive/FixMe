/*
 * Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 */

#include <QApplication>
#include <QDebug>

#include "qtsingleapplication/QtSingleApplication"

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning()) {
        qDebug() << "DEBUG: is running... Bye :)";
        return 0;
    }
    qDebug() << "DEBUG: Ctrl+C to quit";
    return app.exec();
}
