#include <QFile>
#include <QXmlStreamWriter>
#include <QFileInfo>
#include <QDebug>
#include <QFileInfo>

#include "oktrectangle.h"

QString OktRectangle::saveFigure(QString pathToFolder,QGraphicsItem* object)
{
    QRectF rec = dynamic_cast<QGraphicsRectItem*>(object)->rect();

    QString filePath (pathToFolder+"_rect.txt");

    QFile file(filePath);


    QXmlStreamWriter xmlWriter(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    xmlWriter.setAutoFormatting(true);

    {        
        xmlWriter.writeStartElement("Object");
        xmlWriter.writeAttribute(QString("x"),QString::number(rec.x()));
        xmlWriter.writeAttribute(QString("y"),QString::number(rec.y()));
        xmlWriter.writeAttribute(QString("width"),QString::number(rec.width()));
        xmlWriter.writeAttribute(QString("height"),QString::number(rec.height()));
        xmlWriter.writeEndElement();
    }

    file.close();
    return (file.fileName());
}
