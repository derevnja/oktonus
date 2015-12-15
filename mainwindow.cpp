#include <QGraphicsScene>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include <QMenuBar>
#include <QDialog>
#include <QStatusBar>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QPainter>
#include <QDir>
#include <QPluginLoader>
#include <set>


#include "mainwindow.h"
#include "about.h"
#include "oktgraphicview.h"
#include "ibasefigure.h"

auto uCircleCount = 20;
using namespace okt;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      CREATE_MODE(NONE),
      currentPlug(NULL)
{    
    createActions();
    createMenus();

    OktGraphicView *view = new OktGraphicView;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,1000);
    view->setScene(scene);
    connect(view,&OktGraphicView::pressEvent,this,&MainWindow::onPressSceneEvent);

    QIcon icon("qrc:///res/FiguresSample0.ico");
    this->setWindowIcon(icon);

    //status bar permanent label
    QLabel *statusLabel = new QLabel(this);
    // set text for the label
    statusLabel->setText("SCRL");
    statusBar()->addPermanentWidget(statusLabel);
    setCentralWidget(view);

    LoadAllPlugs();
}

MainWindow::~MainWindow()
{

}

void MainWindow::LoadAllPlugs()
{
   QDir path(QDir::currentPath() + "/" + "plugins");
   qDebug() << path;

   foreach (QString fileName, path.entryList(QDir::Files))
   {
        LoadPlugin(path.absolutePath() + "/" + fileName);
   }
}

void MainWindow::LoadPlugin(QString filePath)
{
    qDebug() << "Loading " << filePath;
    QPluginLoader loader (filePath);
    QObject *somePlug = loader.instance();
    if(somePlug)
    {
        qDebug() << "Load plug success";
        IBasePlug* some_base_plug = dynamic_cast<IBasePlug*>(somePlug);
        some_base_plug->init(modeMenu);
        connect(some_base_plug, SIGNAL(setCreatorPtr(IBasePlug*)),this,SLOT(onPlugAction(IBasePlug*)));
        plugList.push_back(some_base_plug);
    }
    else
    {
        qDebug() << "Couldn't load plug";
    }
}

void MainWindow::createActions()
{
    ///create some base actions

    //exit action
    pExitAction = new QAction(tr("Exit"), this);
    pExitAction->setShortcut(QKeySequence::Close);
    pExitAction->setStatusTip(tr("Exit"));
    connect(pExitAction, SIGNAL(triggered()),this,SLOT(onExit()));
    //help action
    pHelpAction = new QAction(tr("Help"), this);
    pHelpAction->setShortcut(QKeySequence::HelpContents);
    pHelpAction->setStatusTip(tr("Display programm information, version number and copyright"));
    connect(pHelpAction, SIGNAL(triggered()),this,SLOT(onHelp()));
    //view action
    pViewAction = new QAction(tr("Status Bar"),this);
    pViewAction->setStatusTip(tr("Show or hide status bar"));
    pViewAction->setCheckable(true);
    pViewAction->setChecked(true);
    connect(pViewAction, SIGNAL(triggered()),this,SLOT(onView()));
    //save
    pSaveAction = new QAction(tr("Save"),this);
    pSaveAction->setStatusTip(tr("Save active document"));
    connect(pSaveAction, SIGNAL(triggered()),this,SLOT(onSave()));
    //save as
    pSaveAsAction = new QAction(tr("Save As"),this);
    pSaveAsAction->setStatusTip(tr("Save As..."));
    connect(pSaveAsAction, SIGNAL(triggered()),this,SLOT(onSaveAs()));
    //load
    pLoadAction = new QAction(tr("Load"),this);
    pLoadAction->setStatusTip(tr("Load document"));
    connect(pLoadAction, SIGNAL(triggered()),this,SLOT(onLoad()));

//    //create Squares
//    pCreateSquare = new QAction(tr("Create Square"),this);
//    pCreateSquare->setStatusTip(tr("Create Square"));
//    connect(pCreateSquare, SIGNAL(triggered()),this,SLOT(onCreateSquare()));
//    //create triangle
//    pCreateTriangle = new QAction(tr("Create Triangle"),this);
//    pCreateTriangle->setStatusTip(tr("Create Triangle"));
//    connect(pCreateTriangle, SIGNAL(triggered()),this,SLOT(onCreateTriangle()));
//    //create Circles
//    pCreateCircle = new QAction(tr("Create Circle"),this);
//    pCreateCircle->setStatusTip(tr("Create Circle"));
//    connect(pCreateCircle, SIGNAL(triggered()),this,SLOT(onCreateCircle()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(pSaveAction);
    fileMenu->addAction(pSaveAsAction);
    fileMenu->addAction(pLoadAction);
    fileMenu->addAction(pExitAction);

    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(pViewAction);

    helpMenu = menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(pHelpAction);

    modeMenu = menuBar()->addMenu(tr("Create Mode"));
}

void MainWindow::deleteAllObjects()
{
    vDrawObjects.clear();
}

std::vector< std::unique_ptr<QGraphicsItem> > MainWindow::createObjects(QString fileFromLoad)
{

    std::vector< std::unique_ptr<QGraphicsItem> > some_v;
    return some_v;
}

void MainWindow::onExit()
{    
    exit(0);
}

void MainWindow::onHelp()
{
    About aboutDlg;
    aboutDlg.exec();
}

void MainWindow::onView()
{
    if(pViewAction->isChecked())
        statusBar()->show();
    else
        statusBar()->hide();
}

void MainWindow::onSave()
{

}

void MainWindow::onSaveAs()
{    
    statusBar()->showMessage(tr("*.fig Saved"));
}

void MainWindow::onLoad()
{    
    statusBar()->showMessage(tr("Fig Opened"));
}

void MainWindow::onPressSceneEvent(QPointF point)
{    
    int some_code=0;
    if  (currentPlug)
    {
        QGraphicsItem *some = dynamic_cast<QGraphicsItem*>(currentPlug->createGeomObject(point));
        scene->addItem(some);
    }

}

void MainWindow::onCreateSquare()
{
    CREATE_MODE = OKTSQUARE;
}

void MainWindow::onCreateTriangle()
{
    CREATE_MODE = OKTTRIANGLE;
}

void MainWindow::onCreateCircle()
{
    CREATE_MODE = OKTCIRCLE;
}

void MainWindow::onPlugAction(IBasePlug *_in)
{
    currentPlug = _in;
}
