// Copyright (C) 2014 Leslie Zhai <xiangzhai83@gmail.com>

#include <QApplication>

int main(int argc, char* argv[]) 
{
    char* ptr = NULL;
    QApplication app(argc, argv);
    strcpy(ptr, "segfault");
    return app.exec();
}
