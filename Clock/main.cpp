#include <QGuiApplication>
#include "rasterwindow.h"

class AnalogClockWindow:public RasterWindow
{
public:
    AnalogClockWindow();
protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
private:
    int m_timerID;
};

AnalogClockWindow::AnalogClockWindow()
{
    setTitle("Clock");
    resize(600, 600);

    m_timerID = startTimer(1000);
}

void AnalogClockWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_timerID)
        RenderLater();
}

void AnalogClockWindow::render(QPainter *p)
{
    QTextStream text;

    static const QPoint hourHand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -40)};
    static const QPoint minuteHand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -70)};
    static const QPoint secondHand[3] = {QPoint(7, 8), QPoint(-7, 8), QPoint(0, -100)};

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondColor(60, 60, 60);
    QTime time = QTime::currentTime();

    p->setRenderHint(QPainter::Antialiasing);
    p->translate(width()/2, height()/2);

    int side = qMin(width(), height());
    p->scale(side/200, side/200);

    p->setPen(Qt::NoPen);
    //////////////////////////////////////////////////////////////////////////////
    p->setBrush(hourColor);
    p->save();
    p->rotate(30 * ((time.hour() + time.minute() / 60)));
    p->drawConvexPolygon(hourHand, 3);
    p->restore();
    p->setPen(hourColor);
    for(int i = 0; i < 12; ++i)
    {
        p->drawLine(88, 0, 96, 0);
        p->rotate(30);
    }
    p->setPen(Qt::NoPen);
    /////////////////////////////////////////////////////////////////////////////////
    p->setBrush(minuteColor);
    p->save();
    p->rotate(6 * ((time.minute() + time.second() / 60)));
    p->drawConvexPolygon(minuteHand, 3);
    p->restore();
    p->setPen(minuteColor);
    for(int j = 0; j < 60; ++j)
    {
        if((j % 5) != 0)
            p->drawLine(92, 0, 96, 0);
        p->rotate(6);
    }
    p->setPen(Qt::NoPen);
    /////////////////////////////////////////////////////////////////////////////////
    p->setBrush(secondColor);
    p->save();
    p->rotate(6 * ((time.second())));
    p->drawConvexPolygon(secondHand, 3);
    p->restore();
    p->setPen(secondColor);
    for(int j = 0; j < 60; ++j)
    {
        p->rotate(1);
    }
}

int main(int argc, char **argv)
{
    QGuiApplication a(argc, argv);
    AnalogClockWindow window;
    window.show();
    return a.exec();
}
