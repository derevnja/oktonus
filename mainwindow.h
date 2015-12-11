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

namespace okt {


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:    
    void createMenus();
    void createActions();
    void generateCircle(QPointF point);
    void createCircle(unsigned int x,unsigned int y,unsigned int w,unsigned int h);
    void generateSquare(QPointF point);
    void createSquare(unsigned int x,unsigned int y,unsigned int w,unsigned int h);
    void generateTringle(QPointF point);
    void createTringle(unsigned int x,unsigned int y,unsigned int length);
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
    QAction *pCreateCircle;
    QAction *pCreateTriangle;
    QAction *pCreateSquare;
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
};

}
#endif // MAINWINDOW_H
