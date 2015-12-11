#include "oktgraphicview.h"
#include <QDebug>
using namespace okt;

OktGraphicView::OktGraphicView()
{
}

void OktGraphicView::mousePressEvent(QMouseEvent *e)
{
  QPointF pt = mapToScene(e->pos());
  emitPressEvent(pt);
}

void OktGraphicView::emitPressEvent(QPointF point)
{
    emit pressEvent(point);
}

void OktGraphicView::resizeEvent(QResizeEvent *event)
{
    QRectF bounds(0,0,event->size().width(),event->size().height());

//    bounds.setWidth(bounds.width()*0.9);         // to tighten-up margins
//    bounds.setHeight(bounds.height()*0.9);       // same as above
//    this->fitInView(bounds, Qt::KeepAspectRatio);
//    this->fitInView(0,0,bounds.width(),bounds.height(), Qt::KeepAspectRatio);
    this->scene()->setSceneRect(0,0,bounds.width(),bounds.height());
}
