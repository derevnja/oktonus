#include <QFile>
#include <QXmlStreamWriter>

#include "circle.h"

using namespace okt;

QString OktCircle::saveFigure(QString pathToFolder,QGraphicsItem* object)
{
    QGraphicsEllipseItem *some_object = dynamic_cast<QGraphicsEllipseItem*>(object);
    QRectF rect = some_object->rect();

    QString filePath (pathToFolder+"_circle.txt");

    QFile file(filePath);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    {
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        xmlWriter.writeStartElement("Object");
        xmlWriter.writeAttribute(QString("radius"),QString::number(rect.width()));
        xmlWriter.writeAttribute(QString("x"),QString::number(rect.x()));
        xmlWriter.writeAttribute(QString("y"),QString::number(rect.y()));
        xmlWriter.writeEndElement();
    }
    file.close();
    return (file.fileName());
}
