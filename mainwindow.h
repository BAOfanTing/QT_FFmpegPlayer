#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifdef __cplusplus ///
extern "C"
{
#include "libavutil/avutil.h"
}
#endif
#include <QMainWindow>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
