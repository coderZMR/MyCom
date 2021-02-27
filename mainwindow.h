#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "win_qextserialport.h"
#include "visualdescribe.h"
#include "data.h"
#include <QGraphicsDropShadowEffect>
#include <QPalette>
#include <QTimer>
// 3D
#include <window.h>
#include <Qt3DRenderer/qrenderaspect.h>
#include <Qt3DInput/QInputAspect>
#include <Qt3DQuick/QQmlAspectEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <data.h>
//#include <QTimer> // 使用Polling模式（查询方式）

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Win_QextSerialPort *myCom;
    visualDescribe vDwin;
    QTimer *updateTimer; // 对界面上的数据控件更新值
    QTimer *updateDialTimer; // 对界面上的表盘控件更行值
    QTimer *updateThermoTimer; // 对界面上的表盘控件更行值
    Data *nowData;
    QByteArray temp;
    QByteArray allData;
    //QTimer *readTimer; // 使用Polling模式（查询方式）
private slots:
    void readMyCom();
    void on_openMyComBtn_clicked();
    void on_closeMyComBtn_clicked();
    void on_sendMsgBtn_clicked();
    void on_showVDBtn_clicked();
    void updateData();
    void changeSpeed();
    void changeHigh();
};

#endif // MAINWINDOW_H
