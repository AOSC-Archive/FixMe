// Copyright (C) 2014 AnthonOS Open Source Community

#include <QApplication>
#include <QDebug>

#include "qtsingleapplication/QtSingleApplication"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QtSingleApplication app(argc, argv);
    if (app.isRunning()) {
        qDebug() << "DEBUG: is running... Bye :)";
        return 0;
    }

    MainWindow objMainWnd;
    objMainWnd.show();

    return app.exec();
}
