#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>
#include <QMenu>

class QAction;
class QGraphicsScene;
class QStatusBar;
class OktCircle;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:    
    void createMenus();
    void createActions();
    void generateCircles();
    void createCircle(unsigned int x,unsigned int y,unsigned int w,unsigned int h);
    void deleteCircles();
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *viewMenu;
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
    QGraphicsScene *scene;
    QStatusBar     *pStatusBar;
    ///keep all circles
    std::vector< std::unique_ptr<OktCircle> > vCircles;

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
};

#endif // MAINWINDOW_H
