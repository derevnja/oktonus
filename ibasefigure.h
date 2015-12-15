#ifndef IBASEPLUG_H
#define IBASEPLUG_H

#include <QString>
#include <QObject>

class  QMenu;
class  QAction;
class  IBasePlug;

//class IBaseSignaler : public QObject
//{
//    Q_OBJECT

//signals:
//    /*!
//     * \brief setCreatorPtr
//     * \param plug
//     *
//     * \details Use this function to send to main app
//     *          info about what plug will create new object
//     */
//    virtual void setCreatorPtr(IBasePlug *plug);
//};

class IBasePlug : public QObject
{

public:        
    /*!
     * \brief init
     * \param modeMenu
     * \param createAction
     */
    virtual void init(QMenu *modeMenu) = 0;
    /*!
     * \brief createGeomObject
     * \return IBasePlug* - pointer to created object
     */
    virtual IBasePlug* createGeomObject(QPointF) = 0;
signals:
    /*!
         * \brief setCreatorPtr
         * \param plug
         *
         * \details Use this function to send to main app
         *          info about what plug will create new object
         */
    void setCreatorPtr(/*IBasePlug *plug*/);
};

QT_BEGIN_NAMESPACE

#define IBasePlug_iid "Some.Info.IBaseFigure"

Q_DECLARE_INTERFACE(IBasePlug, IBasePlug_iid)
QT_END_NAMESPACE

#endif // IBASEFIGURE_H

