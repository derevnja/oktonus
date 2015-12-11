#ifndef OKTTRIANGLE_H
#define OKTTRIANGLE_H

//#include <QAbstractGraphicsShapeItem>
#include <QAbstractGraphicsShapeItem>
#include <QResizeEvent>
#include "ibasefigure.h"

/* !
 *
 * \brief the OktTriangle class
 *
 */

namespace okt {

    class OktTriangle : public QAbstractGraphicsShapeItem, public IBaseFigure
    {
    public:
        OktTriangle(unsigned int x,unsigned int y,unsigned int length,QGraphicsItem * parent = 0):
            QAbstractGraphicsShapeItem(parent)
        {
            Triangle << QPointF(x - length/2,y - length/2) <<
                        QPointF(x,y+length/2) <<
                        QPointF(x+length/2.,y-length/2)<<
                        QPointF(x - length/2,y- length/2);
        }
        ~OktTriangle()
        {}
        virtual QRectF boundingRect() const;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        virtual QString saveFigure(QString pathToFolder,QGraphicsItem* object);
    private:
        QPolygonF Triangle;
    };

}


#endif // OKTTRIANGLE_H
