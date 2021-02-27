#ifndef VISUALDESCRIBE_H
#define VISUALDESCRIBE_H

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include "ui_visualdescribe.h"
#include <qwt_plot_canvas.h>
#include <qlayout.h>
#include <QTime>
#include "data.h"
#include <QGraphicsDropShadowEffect>

#define HISTORY 60

class temperatureCurve;

namespace Ui {
class visualDescribe;
}

class visualDescribe : public QWidget
{
    Q_OBJECT

public:
    explicit visualDescribe(QWidget *parent = 0);
    ~visualDescribe();

private:
    Ui::visualDescribe *ui;
    temperatureCurve *curve;//曲线
    double timeData[HISTORY];
    double temperatureData[HISTORY];
    int dataCount;
protected:
    void timerEvent( QTimerEvent * );
};

#endif // VISUALDESCRIBE_H
