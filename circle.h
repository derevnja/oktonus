#ifndef CIRCLE
#define CIRCLE

#include <QGraphicsEllipseItem>
/*!
 * \brief The OktCircle class
 */
class OktCircle : public QGraphicsEllipseItem
{
public:
    OktCircle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0):
        QGraphicsEllipseItem(x,y,width,height,parent)
    {
         //this->setBrush(QBrush(Qt::green));
    }
};

#endif // CIRCLE

