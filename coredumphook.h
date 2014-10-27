// Copyright (C) 2014 AnthonOS Open Source Community

#ifndef COREDUMP_HOOK_H
#define COREDUMP_HOOK_H

#include <QThread>
#include <QDebug>
#include <poll.h>
#include <errno.h>
#include <string.h>
#include <systemd/sd-journal.h>

typedef void (*CoredumpHookCallback)();

class CoredumpHook : public QThread 
{
    Q_OBJECT

public:
    CoredumpHook(CoredumpHookCallback fptr) : 
        m_fptr(fptr), 
        m_isRunning(true), 
        m_j(NULL) 
    {
        qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << __LINE__;
    }
    ~CoredumpHook() 
    {
        qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << __LINE__;

        if (m_j) sd_journal_close(m_j); m_j = NULL;
    }

protected:
    void run() 
    {
        nfds_t nfds = 1;
        struct pollfd fds[1];
        int r = -1, poll_num = -1;
        
        while (m_isRunning) {
            r = sd_journal_open(&m_j, SD_JOURNAL_LOCAL_ONLY);
            if (r < 0 || m_j == NULL) {
                qDebug() << "ERROR:" << __PRETTY_FUNCTION__ << __LINE__ << 
                    "fail to open systemd journal file descriptor";
                return;
            }

            memset(fds, 0, 1);
            fds[0].fd = sd_journal_get_fd(m_j);
            fds[0].events = sd_journal_get_events(m_j);

            poll_num = poll(fds, nfds, -1);
            if (poll_num == -1) {
                if (errno != EINTR) {
                    qDebug() << "ERROR:" << __PRETTY_FUNCTION__ << __LINE__ << 
                        "fail to poll" << strerror(errno);
                    return;
                }
            }
            if (poll_num > 0) {
                if (fds[0].revents & POLLIN) {
                    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << __LINE__ << 
                        "__COREDUMP__ please call Mr. Doctor ;)";
                    if (m_fptr) m_fptr();
                }
            }

            sd_journal_close(m_j);
            m_j = NULL;
        }
    }

private:
    CoredumpHookCallback m_fptr;
    bool m_isRunning;
    sd_journal* m_j;
};

#endif // COREDUMP_HOOK_H
