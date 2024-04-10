#include "mainwindow.h"

#include <QApplication>
#include "thread.h"
using namespace std;

int main(int argc, char *argv[])
{
    qDebug()<<QString("Hello World! ffmpeg verson %1\n").arg(av_version_info());
    Thread *z_thread;
    z_thread->test_main();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
