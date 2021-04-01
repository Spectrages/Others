#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H


#include <QtGui>


class RasterWindow:public QWindow
{
    Q_OBJECT
public:
    explicit RasterWindow(QWindow *parent = 0);
    virtual void render(QPainter *painter);
public slots:
    void RenderLater();
    void RenderNow();
protected:
    bool event(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void exposeEvent(QExposeEvent *event) override;
private:
    QBackingStore *m_back_store;

};

#endif // RASTERWINDOW_H
