#ifndef OKTGRAPHICVIEW_H
#define OKTGRAPHICVIEW_H

#include <QObject>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace okt {
class OktGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit OktGraphicView();
    ~OktGraphicView()
    {

    }

private:
    void emitPressEvent(QPointF point);
    void resizeEvent(QResizeEvent *event);

    ///own signals
signals:
    void  pressEvent(QPointF);

public slots:
    void mousePressEvent(QMouseEvent * e);
};
}
#endif // OKTGRAPHICVIEW_H
