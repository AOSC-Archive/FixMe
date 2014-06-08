/* Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn> */

#include <stdio.h>
#include <poll.h>
#include <errno.h>
#include <systemd/sd-journal.h>

static sd_journal *m_j = NULL;

int main(int argc, char *argv[]) 
{
    nfds_t nfds = 1;
    struct pollfd fds[1];
    int r = -1, poll_num = -1;

    r = sd_journal_open(&m_j, SD_JOURNAL_LOCAL_ONLY);
    if (r < 0 || m_j == NULL) { 
        printf("ERROR: fail to sd_journal_open\n"); 
        return -1;
    }

    fds[0].fd = sd_journal_get_fd(m_j);
    fds[0].events = sd_journal_get_events(m_j);

    printf("DEBUG: listening for systemd-journal fd events...\n");
    while (1) {
        poll_num = poll(fds, nfds, -1);
        if (poll_num == -1) {
            if (errno == EINTR) {
                continue;
            }
            printf("ERROR: fail to poll\n"); 
            break;
        }

        if (poll_num > 0) {
            if (fds[0].revents & POLLIN) {
                for (;;)  {
                    const void *data = NULL;
                    size_t l = -1;
                    r = sd_journal_next(m_j);
                    if (r < 0) {
                        printf("failed to iterate to next entry: %s\n", strerror(-r));
                        break;
                    }
                    if (r == 0) {
                        r = sd_journal_wait(m_j, (uint64_t) -1);
                        if (r < 0) {
                            printf("failed to wait for changes: %s\n", strerror(-r));
                            break;
                        }
                        continue;
                    }
                    r = sd_journal_get_data(m_j, "COREDUMP", &data, &l);
                    if (r < 0) {
                        printf("failed to read message field: %s\n", strerror(-r));
                        continue;
                    }
                    printf("%.*s\n", (int) l, (const char*) data);
                }
            }
        }
    }
    
    sd_journal_close(m_j);
    m_j = NULL;
    
    return 0;
}
