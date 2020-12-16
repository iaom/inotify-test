#ifndef INOTIFYMANAGER_H
#define INOTIFYMANAGER_H

#include <QObject>
#define EVENT_NUM 12

class InotifyManager : public QObject
{
    Q_OBJECT
public:
    explicit InotifyManager(QObject *parent = nullptr,QString *path = nullptr);
private:
    QString *m_watch_path;


};

#endif // INOTIFYMANAGER_H
