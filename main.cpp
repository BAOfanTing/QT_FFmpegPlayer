#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    qDebug()<<QString("Hello World! ffmpeg verson %1\n").arg(av_version_info());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
