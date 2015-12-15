#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QMenu>

class QAction;
class QGraphicsScene;
class QStatusBar;
class OktCircle;
class QGraphicsItem;
class IBasePlug;

namespace okt {


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:    
    void LoadAllPlugs();
    void LoadPlugin(QString filePath);
    void createMenus();
    void createActions();
    void generateSquare(QPointF point);
    void createSquare(unsigned int x,unsigned int y,unsigned int w,unsigned int h);    
    void deleteAllObjects();
    std::vector< std::unique_ptr<QGraphicsItem> > createObjects(QString fileFromLoad);
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
    QMenu *modeMenu;
    ///open new smthng
    QAction *pOpenAction;
    QAction *pSaveAction;
    QAction *pLoadAction;
    QAction *pSaveAsAction;
    QAction *pPrintAction;
    ///show/hide statusbar;
    QAction *pViewAction;
    QAction *pExitAction;
    QAction *pHelpAction;

    QList<IBasePlug*> plugList;
    ///save current plug which draw figure
    IBasePlug *currentPlug;

    QGraphicsScene *scene;
    QStatusBar     *pStatusBar;
    ///keep all circles
    std::vector< std::unique_ptr<QGraphicsItem> > vDrawObjects;
    enum{
        NONE = 1,
        OKTCIRCLE,
        OKTSQUARE,
        OKTTRIANGLE
    }CREATE_MODE;

private slots:
    /// just close app
    void onExit();
    /// show messagebox "about"
    void onHelp();
    /// show/hide status bar
    void onView();
    /// save button pressed
    void onSave();
    /// save as button pressed
    void onSaveAs();
    /// save button pressed
    void onLoad();
    /// on click event to Scene
    void onPressSceneEvent(QPointF point);
    ///create actions
    /// on click create square
    void onCreateSquare();
    /// on click create triangle
    void onCreateTriangle();
    /// on click create circle
    void onCreateCircle();
    void onPlugAction(IBasePlug *);
};

}
#endif // MAINWINDOW_H
