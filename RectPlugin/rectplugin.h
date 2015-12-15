#ifndef RECTPLUGIN_H
#define RECTPLUGIN_H

#include <QtPlugin>
#include <QGraphicsRectItem>
#include "ibasefigure.h"

class QAction;

//! [0]
class RectPlugin : public IBasePlug, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Some.Info.IBasePlug" FILE "rectplugin.json")
    Q_INTERFACES(IBasePlug)

public:
    RectPlugin(QObject *parent = 0)
    {}    
    RectPlugin(unsigned int x,unsigned int y,unsigned int w,unsigned int h):
        QGraphicsRectItem(x,y,w,h)
    {
    }

    //QString name(const QString &message) Q_DECL_OVERRIDE;
    //QString saveFigure(QString pathToFolder,QGraphicsItem* object) Q_DECL_OVERRIDE;
    void init(QMenu *modeMenu) Q_DECL_OVERRIDE;
    IBasePlug* createGeomObject(QPointF) Q_DECL_OVERRIDE;
    //void setCreatorPtr(IBasePlug *plug) Q_DECL_OVERRIDE;

private:
    QAction *pCreateAction;
    IBasePlug* generateSquare(QPointF point);
    IBasePlug* createSquare(unsigned int x,unsigned int y,unsigned int w,unsigned int h);

private slots:
    /*!
     * \brief onCreateSquare
     */
    void onCreateSquare();
signals:
    /*!
         * \brief setCreatorPtr
         * \param plug
         *
         * \details Use this function to send to main app
         *          info about what plug will create new object
         */
    virtual void setCreatorPtr(IBasePlug *plug);
};
//! [0]
#endif // RECTPLUGIN_H
