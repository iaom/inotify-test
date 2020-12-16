#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inotify-manager.h"
#include "index-generator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    InotifyManager *m_inotify_manager;
    IndexGenerator *m_index_generator;


};
#endif // MAINWINDOW_H
