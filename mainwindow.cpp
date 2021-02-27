#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MyCom Window");
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (192,192,192));
    this->setPalette (bgpal);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    ui->centralWidget->setGraphicsEffect(shadow_effect);
    ui->baudRateComboBox->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->dataBitsComboBox->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->parityComboBox->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->portNameComboBox->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->stopBitsComboBox->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    ui->closeMyComBtn->setEnabled(false); //开始“关闭串口”按钮不可用
    ui->sendMsgBtn->setEnabled(false); //开始“发送数据”按钮不可用
    ui->showVDBtn->setEnabled(false);//开始“形象描述”按钮不可用

    // 对表盘进行设置
    QwtRoundScaleDraw *scaleDraw = new QwtRoundScaleDraw();
    scaleDraw->setSpacing( 8 );
    scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, false );
    scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
    scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 4 );
    scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 8 );
    ui->Dial_io->setScaleDraw(scaleDraw);
    ui->Dial_io->setWrapping( false );
    ui->Dial_io->setReadOnly( true );
    ui->Dial_io->setOrigin( 135.0 );
    ui->Dial_io->setScaleArc( 0.0, 270.0 );
    ui->Dial_io->setScaleStepSize( 20.0 );
    ui->Dial_io->setScale( 0.0, 240.0 );
    ui->Dial_io->scaleDraw()->setPenWidth( 2 );
    // 给表盘设置指针
    QwtDialSimpleNeedle *needle = new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true, Qt::red,
        QColor( Qt::gray ).light( 130 ) );
    ui->Dial_io->setNeedle( needle );



    // 创建用于更新数据控件值的计时器
    updateTimer = new QTimer(this);
    updateTimer->setInterval(1000);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateData()));

    // 创建用于更新表盘控件值的计时器
    updateDialTimer = new QTimer(ui->Dial_io);
    updateDialTimer->setInterval(50);
    connect( updateDialTimer, SIGNAL( timeout() ), this, SLOT( changeSpeed() ) );

    // 创建用于更新温度计值的计时器
    updateThermoTimer = new QTimer(ui->Thermo_temperature);
    updateThermoTimer->setInterval(50);
    connect( updateThermoTimer, SIGNAL( timeout() ), this, SLOT( changeHigh() ) );


    temp.clear();
    allData.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData() {
    nowData = Data::getInstance();
    // 测试
    //nowData->test();
    // 更新各个控件的值
    if (nowData->getltf() == 1) ui->frame_left->setStyleSheet("image: url(:/new/prefix1/lightOn)");
    if (nowData->getltf() == 0) ui->frame_left->setStyleSheet("image: url(:/new/prefix1/lightOff)");
    if (nowData->getlts() == 1) ui->frame_right->setStyleSheet("image: url(:/new/prefix1/lightOn)");
    if (nowData->getlts() == 0) ui->frame_right->setStyleSheet("image: url(:/new/prefix1/lightOff)");

    ui->lcd_acx->display(Data::getInstance()->getacX());
    ui->lcd_acy->display(Data::getInstance()->getacY());
    ui->lcd_acz->display(Data::getInstance()->getacZ());

    ui->lcd_avx->display(Data::getInstance()->getavX());
    ui->lcd_avy->display(Data::getInstance()->getavY());
    ui->lcd_avz->display(Data::getInstance()->getavZ());

    ui->lcd_anx->display(Data::getInstance()->getanX());
    ui->lcd_any->display(Data::getInstance()->getanY());
    ui->lcd_anz->display(Data::getInstance()->getanZ());
}

void MainWindow::changeSpeed() {
    ui->Dial_io->setValue(Data::getInstance()->getgunValue());
    // Data
    //ui->textBrowser->insertPlainText(QString("acx0") + QString("acy0") + QString("acz0") + QString("avx0") + QString("avy0") + QString("avz0") + QString("agx0") + QString("agy0") + QString("agz0") + QString("tem15") + QString("oi") + QString::number(Data::getInstance()->getgunValue()) + QString("ltf0") + QString("lts0") + QString("d") + QString("\n"));
}

void MainWindow::changeHigh() {
    ui->Thermo_temperature->setValue(Data::getInstance()->gettemperatureValue());
}

void MainWindow::readMyCom() //读串口函数
{
    temp = myCom->readAll();    // 读取串口缓冲区的所有数据给临时变量
    if (!temp.isEmpty())    // 判断是否已从串口读取到数据
    {
        allData.append(temp);   // 将接收到的数据进行拼接
        if (allData.contains("d"))  // 判断是否已经接收到一个完整的数据流
        {
            QByteArray getPage = allData.split('d').at(0) + 'd';    // 根据“数据截止协议标记格式”截断数据并进行简单数据处理
            nowData->analyze(getPage);  // 使用“数据分类抽取解析算法”分类提取采集相应的传感器数据
            ui->textBrowser->insertPlainText(allData.split('d').at(0) + 'd' + '\n' + '\n'); // 将接收到的完整数据流规则显示在窗口的文本浏览器中
            allData = allData.right(allData.length() - allData.indexOf('d') - 1);   // 对非完整数据流数据进行存储，在下次运行“数据完整性拼接算法”中使用
        }
    }
}

void MainWindow::on_openMyComBtn_clicked()
{
    QString portName = ui->portNameComboBox->currentText(); //获取串口名
    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven); //定义串口对象，并传递参数，在构造函数里对其进行初始化
    //myCom = new Win_QextSerialPort("COM1", QextSerialBase::Polling); // 使用Polling模式（查询方式）
    //readTimer = new QTimer(this);// 使用Polling模式（查询方式）
    //readTimer->start(100);  // 设置延时为100ms// 使用Polling模式（查询方式）
    myCom ->open(QIODevice::ReadWrite); //打开串口
    //设置波特率(根据组合框内容对串口进行设置)
    if(ui->baudRateComboBox->currentText()==tr("9600"))
    myCom->setBaudRate(BAUD9600);
    else if(ui->baudRateComboBox->currentText()==tr("115200"))
    myCom->setBaudRate(BAUD115200);
    //设置数据位
    if(ui->dataBitsComboBox->currentText()==tr("8"))
    myCom->setDataBits(DATA_8);
    else if(ui->dataBitsComboBox->currentText()==tr("7"))
    myCom->setDataBits(DATA_7);
    //设置奇偶校验
    if(ui->parityComboBox->currentText()==tr("null"))
    myCom->setParity(PAR_NONE);
    else if(ui->parityComboBox->currentText()==tr("odd"))
    myCom->setParity(PAR_ODD);
    else if(ui->parityComboBox->currentText()==tr("even"))
    myCom->setParity(PAR_EVEN);
    //设置停止位
    if(ui->stopBitsComboBox->currentText()==tr("1"))
    myCom->setStopBits(STOP_1);
    else if(ui->stopBitsComboBox->currentText()==tr("2"))
    myCom->setStopBits(STOP_2);
    //设置数据流控制，我们使用无数据流控制的默认设置
    myCom->setFlowControl(FLOW_OFF);
    //设置延时
    myCom->setTimeout(500);
    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //connect(readTimer, SIGNAL(timeout()), this, SLOT(readMyCom())); // 使用Polling模式（查询方式）
    ui->openMyComBtn->setEnabled(false); //打开串口后“打开串口”按钮不可用
    ui->closeMyComBtn->setEnabled(true); //打开串口后“关闭串口”按钮可用
    ui->sendMsgBtn->setEnabled(true); //打开串口后“发送数据”按钮可用
    ui->showVDBtn->setEnabled(true);//打开串口后“形象描述”按钮可用
    //设置各个组合框不可用
    ui->baudRateComboBox->setEnabled(false);
    ui->dataBitsComboBox->setEnabled(false);
    ui->parityComboBox->setEnabled(false);
    ui->stopBitsComboBox->setEnabled(false);
    ui->portNameComboBox->setEnabled(false);
    // 数据采集类创建对象并初始化
    nowData = Data::getInstance();
    nowData->init();
    // 开始更新控件数据
    updateTimer->start();
    updateDialTimer->start();
    updateThermoTimer->start();
//    //定义一个结构体，用来存放串口各个参数
//    struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
//    //定义串口对象，并传递参数，在构造函数里对其进行初始化
//    // 完成了串口的选择和串口的初始化
//    myCom = new Win_QextSerialPort("com1",myComSetting,QextSerialBase::EventDriven);
//    //以可读写方式打开串口
//    myCom ->open(QIODevice::ReadWrite);
//    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
//    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
//    ui->openMyComBtn->setEnabled(false); //打开串口后“打开串口”按钮不可用
//    ui->closeMyComBtn->setEnabled(true); //打开串口后“关闭串口”按钮可用
//    ui->sendMsgBtn->setEnabled(true); //打开串口后“发送数据”按钮可用
}

void MainWindow::on_closeMyComBtn_clicked()
{
    myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义
    ui->openMyComBtn->setEnabled(true); //关闭串口后“打开串口”按钮可用
    ui->closeMyComBtn->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
    ui->sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用
    ui->showVDBtn->setEnabled(false);//关闭串口后“形象描述”按钮不可用
    if(!vDwin.isHidden()) vDwin.hide();
    //设置各个组合框可用
    ui->baudRateComboBox->setEnabled(true);
    ui->dataBitsComboBox->setEnabled(true);
    ui->parityComboBox->setEnabled(true);
    ui->stopBitsComboBox->setEnabled(true);
    ui->portNameComboBox->setEnabled(true);
    // 停止更新控件数据
    updateTimer->stop();
    updateDialTimer->stop();
    updateThermoTimer->stop();
    nowData->init(); // 数据采集类初始化
    // 各控件值初始化
    ui->frame_left->setStyleSheet("image: url(:/new/prefix1/lightOff)");
    ui->frame_right->setStyleSheet("image: url(:/new/prefix1/lightOff)");

    ui->Dial_io->setValue(0);

    ui->Thermo_temperature->setValue(0);

    ui->lcd_acx->display(0);
    ui->lcd_acy->display(0);
    ui->lcd_acz->display(0);

    ui->lcd_avx->display(0);
    ui->lcd_avy->display(0);
    ui->lcd_avz->display(0);

    ui->lcd_anx->display(0);
    ui->lcd_any->display(0);
    ui->lcd_anz->display(0);

//    myCom->close(); //关闭串口，该函数在win_qextserialport.cpp文件中定义
//    ui->openMyComBtn->setEnabled(true); //关闭串口后“打开串口”按钮可用
//    ui->closeMyComBtn->setEnabled(false); //关闭串口后“关闭串口”按钮不可用
//    ui->sendMsgBtn->setEnabled(false); //关闭串口后“发送数据”按钮不可用
}

void MainWindow::on_sendMsgBtn_clicked()
{
//    //以ASCII码形式将行编辑框中的数据写入串口
//    myCom->write(ui->sendMsgLineEdit->text().toLatin1());
    ui->textBrowser->clear();
}

void MainWindow::on_showVDBtn_clicked()
{
    vDwin.show();
    vDwin.move((QApplication::desktop()->width() - vDwin.width()) / 2,
           (QApplication::desktop()->height() - vDwin.height()) / 2);
}
