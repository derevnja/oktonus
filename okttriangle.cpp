#include <QPainter>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QDebug>
#include <QGraphicsView>


#include "okttriangle.h"

using namespace okt;

QRectF OktTriangle::boundingRect() const
{
    return Triangle.boundingRect();
}

void OktTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{    
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    QRectF rect = boundingRect();
    painter->drawPolygon(Triangle);
}

void OktTriangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void OktTriangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

QString OktTriangle::saveFigure(QString pathToFolder,QGraphicsItem* object)
{
    OktTriangle *some_object = dynamic_cast<OktTriangle*>(object);

    QString filePath (pathToFolder+"_triangle.txt");

    QFile file(filePath);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    {
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        xmlWriter.writeStartElement("Object");
        for(int i = 0; i < Triangle.size(); i++)
        {
            xmlWriter.writeAttribute(QString("x"),QString::number(Triangle[i].x()));
            xmlWriter.writeAttribute(QString("y"),QString::number(Triangle[i].y()));
        }
        xmlWriter.writeEndElement();
    }
    file.close();
    return (file.fileName());
}


