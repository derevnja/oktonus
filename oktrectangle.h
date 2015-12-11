#ifndef OKTRECTANGLE_H
#define OKTRECTANGLE_H
#include <QGraphicsRectItem>
#include "ibasefigure.h"

class OktRectangle : public QGraphicsRectItem, public IBaseFigure
{
public:    
    OktRectangle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0):
        QGraphicsRectItem(x,y,width,height,parent)
    {
        //this->setBrush(QBrush(Qt::green));
    }
    ~OktRectangle()
    {
    }
    virtual QString saveFigure(QString pathToFolder,QGraphicsItem* object);
};

#endif // OKTRECTANGLE_H
