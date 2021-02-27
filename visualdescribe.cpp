#include "visualdescribe.h"

//背景色填充
class Background: public QwtPlotItem
{
public:
    Background()
    {
        setZ( 0.0 );
    }

    virtual int rtti() const
    {
        return QwtPlotItem::Rtti_PlotUserItem;
    }

    virtual void draw( QPainter *painter,
        const QwtScaleMap &, const QwtScaleMap &yMap,
        const QRectF &canvasRect ) const
    {
        QColor c( Qt::white );
        QRectF r = canvasRect;
        for ( int i = 50; i >= -50; i -= 10 )
        {
            r.setBottom( yMap.transform( i - 10 ) );//将相对于Y坐标轴值 转换成相对于窗口绘图设备的相对值
            r.setTop( yMap.transform( i ) );
            painter->fillRect( r, c );//填充矩形背景
            c = c.dark( 110 );//递增变黑，但该方法已经过时了，Qt5.3应该是 c.darker()
        }
    }
};

//曲线
class temperatureCurve: public QwtPlotCurve
{
public:
    temperatureCurve( const QString &title ):
        QwtPlotCurve( title )
    {
        setRenderHint( QwtPlotItem::RenderAntialiased );//设置渲染效果，抗锯齿
    }

    void setColor( const QColor &color )
    {
        QColor c = color;
        c.setAlpha( 150 );//设置Alpha通道颜色

        setPen( c );//设置画笔
        setBrush( c );//设置笔刷
    }
};

class TimeScaleDraw: public QwtScaleDraw
{
public:
    TimeScaleDraw(const QTime &base):
    baseTime(base)
    {
    }

    virtual QwtText label(double v) const
    {
        QTime upTime = baseTime.addSecs((int)v);
        return upTime.toString();
    }
private:
    QTime baseTime;
};


visualDescribe::visualDescribe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualDescribe)
{
    dataCount = 0;
    QPalette bgpal = palette();
    bgpal.setColor (QPalette::Background, QColor (192,192,192));
    setPalette (bgpal);

    ui->setupUi(this);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(Qt::gray);
    shadow_effect->setBlurRadius(8);
    ui->qwtPlot->setGraphicsEffect(shadow_effect);
    this->setWindowTitle("形象描述");
    ui->qwtPlot->setAutoReplot(false);
    ui->qwtPlot->setTitle("温度变化");
    QwtPlotCanvas *canvas = new QwtPlotCanvas();//画布
    canvas->setBorderRadius( 10 );//画布四周边框角半径
    ui->qwtPlot->setCanvas( canvas );//设置绘图的画布
    ui->qwtPlot->setAxisTitle( QwtPlot::xBottom, " 时间 [h:m:s]" );
    QTime curTime;
    curTime = curTime.currentTime();
    curTime = curTime.addSecs(-60);
    ui->qwtPlot->setAxisScaleDraw( QwtPlot::xBottom,
                                   new TimeScaleDraw(curTime));
    ui->qwtPlot->setAxisLabelRotation( QwtPlot::xBottom, -50.0 );//标签旋转50度
    ui->qwtPlot->setAxisLabelAlignment( QwtPlot::xBottom, Qt::AlignLeft | Qt::AlignBottom );

    for ( int i = 0; i < HISTORY; i++ )
        timeData[HISTORY - 1 - i] = i;
    startTimer(1000);

    ui->qwtPlot->setAxisTitle( QwtPlot::yLeft, "温度 [°]" );
    ui->qwtPlot->setAxisScale( QwtPlot::yLeft, -50, 50 );

    Background *bg = new Background();//给绘图填充背景
    bg->attach(ui->qwtPlot);//插入plot

    curve = new temperatureCurve("Temperature");
    curve->setColor( Qt::red );//设置曲线颜色
    curve->attach( ui->qwtPlot );//插入plot
    curve->setVisible(true);
    ui->qwtPlot->replot();
}


void visualDescribe::timerEvent(QTimerEvent *)
{
    for ( int i = dataCount; i > 0; i-- )
    {
        if ( i < HISTORY )
            temperatureData[i] = temperatureData[i-1];
    }

    temperatureData[0] = Data::getInstance()->gettemperatureValue();

    if ( dataCount < HISTORY )
        dataCount++;

    for ( int j = 0; j < HISTORY; j++ )
        timeData[j]++;

    ui->qwtPlot->setAxisScale(QwtPlot::xBottom,
                              timeData[HISTORY - 1], timeData[0]);

    curve->setRawSamples(
                timeData, temperatureData, dataCount );

    ui->qwtPlot->replot();
}

visualDescribe::~visualDescribe()
{
    delete ui;
}
