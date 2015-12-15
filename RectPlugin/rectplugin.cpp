#include <QMenuBar>
#include <QAction>



#include "rectplugin.h"

//! [0]
void RectPlugin::init(QMenu *modeMenu)
{
    if(modeMenu != NULL)
    {
        //create Squares
        pCreateAction = new QAction(tr("Create Square"),this);
        pCreateAction->setStatusTip(tr("Create Square"));
        connect(pCreateAction, SIGNAL(triggered()),this,SLOT(onCreateSquare()));

        modeMenu->addAction(pCreateAction);
    }
    else
    {
       //todo some releas fuck up log
    }
}

IBasePlug*  RectPlugin::createGeomObject(QPointF point)
{
    return generateSquare(point);
}

//void RectPlugin::setCreatorPtr(IBasePlug *plug)
//{

//}

void RectPlugin::onCreateSquare()
{
    //emit (signaler->setCreatorPtr(this));
    //emit (&IBaseSignaler::setCreatorPtr,this);
    emit (setCreatorPtr(this));
}

IBasePlug* RectPlugin::generateSquare(QPointF point)
{
   auto x = point.rx();
   auto y = point.ry();
   auto w = qrand() % 90+10;
   auto h = w;
   return createSquare(x-w/2,y-w/2,w,h);
}

IBasePlug* RectPlugin::createSquare(unsigned int x,unsigned int y,unsigned int w,unsigned int h)
{
    //std::unique_ptr<QGraphicsItem> ptr(new RectPlugin(x,y,w,h));
    return new RectPlugin(x,y,w,h);
    //vDrawObjects.push_back(std::move(ptr));
    //scene->addItem(vDrawObjects.back().get());
}
//! [0]
