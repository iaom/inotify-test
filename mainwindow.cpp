#include "mainwindow.h"
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto path = new QString("/home/zpf");
//    m_inotify_manager = new InotifyManager(this,path);
    m_index_generator = new IndexGenerator(this);
}

MainWindow::~MainWindow()
{
}

