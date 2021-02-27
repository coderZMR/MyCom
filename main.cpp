#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
#include <QPropertyAnimation>

// 3D
#include <window.h>
#include <Qt3DRenderer/qrenderaspect.h>
#include <Qt3DInput/QInputAspect>
#include <Qt3DQuick/QQmlAspectEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <data.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //使程序可处理中文
//  QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
//  QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf_8"));
    // 数据流加载
    Data *startData = Data::getInstance();

    // 3D加载
    Window view;
    Qt3D::Quick::QQmlAspectEngine engine;

    view.resize(700, 500);
    engine.aspectEngine()->registerAspect(new Qt3D::QRenderAspect());
    engine.aspectEngine()->registerAspect(new Qt3D::QInputAspect());
    engine.aspectEngine()->initialize();
    QVariantMap data;
    data.insert(QStringLiteral("surface"), QVariant::fromValue(static_cast<QSurface *>(&view)));
    data.insert(QStringLiteral("eventSource"), QVariant::fromValue(&view));
    engine.aspectEngine()->setData(data);
    engine.qmlEngine()->rootContext()->setContextProperty("_window", &view);
    engine.qmlEngine()->rootContext()->setContextProperty("_data", startData);
    engine.setSource(QUrl("qrc:/main.qml"));

    // 界面加载
    MainWindow w;

    QPixmap pixmap(":/new/prefix1/uwrPic");
    QSplashScreen splash(pixmap);

    // 显示所有窗口
    splash.show();

    QTimer::singleShot(1500, &splash, SLOT(hide()));
    QTimer::singleShot(2000, &w, SLOT(show()));
    QTimer::singleShot(2500, &view, SLOT(show()));
    w.move((QApplication::desktop()->width() - w.width()) / 2,
           (QApplication::desktop()->height() - w.height()) / 2);


    return a.exec();
}

// 要先打开串口再对它进行设置，不然设置就不会起作用
// 正确的顺序：先定义Win_QextSerialPort类对象，然后打开串口，再用那几个设置函数对串口进行设置
// 事件驱动EventDriven下设置串口的延迟不会起作用，一旦有数据来到即会触发readyRead()信号
// 查询模式Polling下设置串口的延迟会决定读取串口数据的时间间隔
// timeout 底层读串口数据将读到的数据写入串口缓冲区（myCom->setTimeout(间隔时间ms)）；间隔时间应该较小
// readTime->start(间隔时间ms)设置的是读串口缓冲区中的数据，间隔时间应该比timeout大
