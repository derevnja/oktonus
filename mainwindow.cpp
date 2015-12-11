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
#include <set>


#include "mainwindow.h"
#include "circle.h"
#include "oktrectangle.h"
#include "okttriangle.h"
#include "about.h"
#include "oktgraphicview.h"

auto uCircleCount = 20;
using namespace okt;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      CREATE_MODE(NONE)
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
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
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

    //create Squares
    pCreateSquare = new QAction(tr("Create Square"),this);
    pCreateSquare->setStatusTip(tr("Create Square"));
    connect(pCreateSquare, SIGNAL(triggered()),this,SLOT(onCreateSquare()));
    //create triangle
    pCreateTriangle = new QAction(tr("Create Triangle"),this);
    pCreateTriangle->setStatusTip(tr("Create Triangle"));
    connect(pCreateTriangle, SIGNAL(triggered()),this,SLOT(onCreateTriangle()));
    //create Circles
    pCreateCircle = new QAction(tr("Create Circle"),this);
    pCreateCircle->setStatusTip(tr("Create Circle"));
    connect(pCreateCircle, SIGNAL(triggered()),this,SLOT(onCreateCircle()));
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
    modeMenu->addAction(pCreateSquare);
    modeMenu->addAction(pCreateTriangle);
    modeMenu->addAction(pCreateCircle);
}

void MainWindow::generateCircle(QPointF point)
{    
   auto x = point.x();
   auto y = point.y();
   auto w = qrand() % 90+10;
   auto h = w;
   createCircle(x - w/2,y - w/2,w,h);
}

void MainWindow::createCircle(unsigned int x,unsigned int y,unsigned int w,unsigned int h)
{
    std::unique_ptr<QGraphicsItem> ptr(new OktCircle(x,y,w,h));
    vDrawObjects.push_back(std::move(ptr));
    scene->addItem(vDrawObjects.back().get());
}

void MainWindow::generateSquare(QPointF point)
{
   auto x = point.rx();
   auto y = point.ry();
   auto w = qrand() % 90+10;
   auto h = w;
   createSquare(x-w/2,y-w/2,w,h);
}

void MainWindow::createSquare(unsigned int x,unsigned int y,unsigned int w,unsigned int h)
{
    std::unique_ptr<QGraphicsItem> ptr(new OktRectangle(x,y,w,h));
    vDrawObjects.push_back(std::move(ptr));
    scene->addItem(vDrawObjects.back().get());
}

void MainWindow::generateTringle(QPointF point)
{
   auto x = point.rx();
   auto y = point.ry();
   auto length = qrand() % 90+10;
   createTringle(x,y,length);
}

void MainWindow::createTringle(unsigned int x,unsigned int y,unsigned int length)
{ 
    std::unique_ptr<QGraphicsItem> ptr(new OktTriangle(x,y,length));
    vDrawObjects.push_back(std::move(ptr));
    scene->addItem(vDrawObjects.back().get());
    scene->update();
}

void MainWindow::deleteAllObjects()
{
    vDrawObjects.clear();
}

std::vector< std::unique_ptr<QGraphicsItem> > MainWindow::createObjects(QString fileFromLoad)
{
    if (fileFromLoad == "_rect.txt")
    {
        QFile file(fileFromLoad);
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            Q_ASSERT("error read file");
        }
        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        QXmlStreamReader Rxml;
        Rxml.setDevice(&file);
        std::vector< std::unique_ptr<QGraphicsItem> > local_object_vector;

        while(!Rxml.atEnd())
        {
//            if (token == QXmlStreamReader::StartDocument)
//                continue;
            if(Rxml.name() == "Object")
            {
                unsigned int _x,_y,_w,_h;
                foreach(const QXmlStreamAttribute &attr, Rxml.attributes())
                                {
                                    if (attr.name().toString() == QLatin1String("x"))
                                    {
                                        _x = attr.value().toUInt();
//                                        QString attribute_value = attr.value().toString();
//                                        qDebug() << attr.name().toString()<< " " <<attribute_value;
                                    }
                                    if (attr.name().toString() == QLatin1String("y"))
                                    {
                                        _y = attr.value().toUInt();

                                    }
                                    if (attr.name().toString() == QLatin1String("width"))
                                    {
                                        _w = attr.value().toUInt();

                                    }
                                    if (attr.name().toString() == QLatin1String("height"))
                                    {
                                        _h = attr.value().toUInt();

                                    }
                                }

                std::unique_ptr<QGraphicsItem> ptr(new OktRectangle(_x,_y,_w,_h));
                vDrawObjects.push_back(std::move(ptr));
                scene->addItem(vDrawObjects.back().get());
            }
            Rxml.readNext();
        }
        file.close();
    }
    else if (fileFromLoad == "_triangle.txt")
    {

    }
    else if (fileFromLoad == "_circle.txt")
    {

    }
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
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save fig"), ".",
                                                    tr("Fig files (*.fig)"));

    QFile file(filename);
    file.remove();
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartElement("Files");
    std::set<QString> filesSet;
    for(int i = 0;i < vDrawObjects.size(); i++)
    {
       QString file_name = dynamic_cast<IBaseFigure*>(vDrawObjects[i].get())->saveFigure("",vDrawObjects[i].get());
       //save returned files in general file with all figures
       {
           auto res = filesSet.insert(file_name);
           if (res.second == true)
           {
             xmlWriter.writeStartElement("File");
             xmlWriter.writeAttribute(QString("file"),file_name);
             xmlWriter.writeEndElement();
           }
       }
    }
    xmlWriter.writeEndElement();
    file.close();
    statusBar()->showMessage(tr("*.fig Saved"));
}

void MainWindow::onLoad()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Fig"), ".",
                                                    tr("Fig files (*.fig)"));

    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        Q_ASSERT("error read file");
    }
    deleteAllObjects();
    QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);

    while(!Rxml.atEnd())
    {        
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if(Rxml.name() == "File")
        {
            QString str = Rxml.attributes().value("file").toString();
            createObjects(str);
        }
        Rxml.readNext();
    }
    file.close();
    statusBar()->showMessage(tr("Fig Opened"));
}

void MainWindow::onPressSceneEvent(QPointF point)
{
    if (CREATE_MODE == OKTCIRCLE)
    {
        generateCircle(point);
    }
    if (CREATE_MODE == OKTSQUARE)
    {
        generateSquare(point);
    }
    if (CREATE_MODE == OKTTRIANGLE)
    {
        generateTringle(point);
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
