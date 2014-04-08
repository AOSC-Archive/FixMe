/*                                                                              
 * Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>                      
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include <QObject>
#include <QCoreApplication>
#include <QFileSystemWatcher>
#include <QDebug>

class MyWorker : public QObject 
{
    Q_OBJECT

public slots:
    void directoryChanged(const QString & path) 
    {
        qDebug() << "DEBUG: " << __PRETTY_FUNCTION__ << path;
    }

    void fileChanged(const QString & path) 
    {
        qDebug() << "DEBUG: " << __PRETTY_FUNCTION__ << path;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList paths;
    paths.append(argv[1] ? QString(argv[1]) : "/var/log/journal");
    QFileSystemWatcher watcher(paths);
    MyWorker worker;
    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged, 
        &worker, &MyWorker::directoryChanged);
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, 
        &worker, &MyWorker::fileChanged);
    return app.exec();
}

#include "qinotify.moc"
