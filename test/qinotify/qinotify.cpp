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
#include <systemd/sd-journal.h>

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

class MyJournal : public QObject 
{
    Q_OBJECT

public:
    MyJournal() : m_j(NULL) 
    {
        if (sd_journal_open(&m_j, SD_JOURNAL_LOCAL_ONLY) < 0) {
            qDebug() << "DEBUG: " << __PRETTY_FUNCTION__ << "failed to sd_journal_open";
        }
    }
    ~MyJournal() 
    {
        if (m_j) sd_journal_close(m_j); m_j = NULL;
    }

    void dump_list() 
    {
        int count = 0;
        if (m_j == NULL) return;

        sd_journal_set_data_threshold(m_j, 4096);

        SD_JOURNAL_FOREACH(m_j) {
            //qDebug() << "DEBUG: " << __PRETTY_FUNCTION__;
            const void *d;
            size_t l;
            SD_JOURNAL_FOREACH_DATA(m_j, d, l) {
                qDebug() << "DEBUG: " << d << l;
            }
            count++;
        }

        qDebug() << "DEBUG: " << __PRETTY_FUNCTION__ << count;
    }

private:
    sd_journal *m_j;
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    MyJournal jour;
    jour.dump_list();
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
