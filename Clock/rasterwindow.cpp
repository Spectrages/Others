#include "rasterwindow.h"

RasterWindow::RasterWindow(QWindow *parent) : QWindow(parent), m_back_store(new QBackingStore(this))
{
    setGeometry(100, 100, 300, 200);
}

void RasterWindow::exposeEvent(QExposeEvent *)
{
    if(isExposed())
        RenderNow();
}

void RasterWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    m_back_store->resize(resizeEvent->size());
}

void RasterWindow::RenderNow()
{
    if(!isExposed())
        return;
    QRect rect(0, 0, width(), height());
    m_back_store->beginPaint(rect);
    QPaintDevice *device = m_back_store->paintDevice();
    QPainter painter(device);
    painter.fillRect(0, 0, width(), height(), QGradient::CleanMirror);
    render(&painter);
    painter.end();
    m_back_store->endPaint();
    m_back_store->flush(rect);
}

void RasterWindow::render(QPainter *painter)
{
    painter->drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("Window"));
}

void RasterWindow::RenderLater()
{
    requestUpdate();
}

bool RasterWindow::event(QEvent *event)
{
    if(event->type() == QEvent::UpdateRequest)
    {
        RenderNow();
        return true;
    }
    return QWindow::event(event);
}








