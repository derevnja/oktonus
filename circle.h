#ifndef CIRCLE
#define CIRCLE
#include "ibasefigure.h"

#include <QGraphicsEllipseItem>
/*!
 * \brief The OktCircle class
 */
namespace okt {
class OktCircle : public QGraphicsEllipseItem, public IBaseFigure
{
public:
    OktCircle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0):
        QGraphicsEllipseItem(x,y,width,height,parent)
    {
        //this->setBrush(QBrush(Qt::green));
    }
    ~OktCircle()
    {
    }
    virtual QString saveFigure(QString pathToFolder,QGraphicsItem* object);
};
}
#endif // CIRCLE

