#ifndef IBASEFIGURE_H
#define IBASEFIGURE_H

class  QString;
class  QXmlStreamWriter;
class  QGraphicsItem;

struct IBaseFigure
{
    IBaseFigure() {}
    virtual ~IBaseFigure() {}
    virtual QString saveFigure(QString pathToFolder,QGraphicsItem* object) = 0;
};

#endif // IBASEFIGURE_H

