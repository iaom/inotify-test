#include "inotify-manager.h"
#include <sys/unistd.h>
#include <sys/inotify.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <QDebug>

char *event_type[EVENT_NUM] =
{
    "IN_ACCESS",
    "IN_MODIFY",
    "IN_ATTRIB",
    "IN_CLOSE_WRITE",
    "IN_CLOSE_NOWRITE",
    "IN_OPEN",
    "IN_MOVED_FROM",
    "IN_MOVED_TO",
    "IN_CREATE",
    "IN_DELETE",
    "IN_DELETE_SELF",
    "IN_MOVE_SELF"
};
InotifyManager::InotifyManager(QObject *parent, QString *path) : QObject(parent)
{
    int fd;
    int wd;
    int len;
    int nread;
    char buf[BUFSIZ];
    struct inotify_event *event;
    int i;
    m_watch_path = path;


    fd = inotify_init();
    if( fd < 0 )
    {
        qDebug()<<"inotify_init failed!";
        return;
    }

    wd = inotify_add_watch(fd, m_watch_path->toLatin1().data(), IN_ALL_EVENTS);
    if(wd < 0)
    {
        qDebug()<<"inotify_add_watch "<<m_watch_path<<"failed!";
        return;
    }

    memset(buf,0x00,sizeof(buf));
    while( (len = read(fd, buf, sizeof(buf) - 1)) > 0 )
    {
        nread = 0;
        while( len > 0 )
        {
            qDebug()<<"nread!!"<<nread;
            event = (struct inotify_event *)&buf[nread];
            for(i=0; i<EVENT_NUM; i++)
            {
                if((event->mask >> i) & 1)
                {
                    if(event->len > 0)
                        qDebug()<<QString(event->name)<<QString(event_type[i]);
                    else
                        qDebug()<< " "<<QString(event_type[i]);
                }
            }
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }

    return;

}
