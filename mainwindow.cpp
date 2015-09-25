#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>
#include <QLabel>
#include <QtGui>
#include <QMenuBar>
#include <QDialog>
#include <QStatusBar>
#include <QFileDialog>


#include "mainwindow.h"
#include "circle.h"
#include "about.h"

auto uCircleCount = 20;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    
    createActions();
    createMenus();

    QGraphicsView *view = new QGraphicsView;
    scene = new QGraphicsScene(this);
    view->setScene(scene);

    QIcon icon("qrc:///res/FiguresSample0.ico");
    this->setWindowIcon(icon);

    //status bar permanent label
    QLabel *statusLabel = new QLabel(this);
    // set text for the label
    statusLabel->setText("SCRL");
    statusBar()->addPermanentWidget(statusLabel);

    createCircles();
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
}

void MainWindow::createCircles()
{

    for (int i = 0; i < uCircleCount; i++)
    {
        auto x = qrand() % 500;
        auto y = qrand() % 500;
        auto w = qrand() % 90+10;
        auto h = w;
        //OktCircle *c = new OktCircle(x,y,w,h);
        std::unique_ptr<OktCircle> ptr(new OktCircle(x,y,w,h));
        vCircles.push_back(std::move(ptr));
        scene->addItem(vCircles.back().get());
    }
}

void MainWindow::onExit()
{
    qDebug()<<"exit pressed";
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
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Objects");
    for(int i = 0;i < vCircles.size(); i++)
    {
        QRectF rec = vCircles[i].get()->rect();
        xmlWriter.writeStartElement("Object");
        xmlWriter.writeAttribute(QString("name"),QString::number(i));
        xmlWriter.writeAttribute(QString("x"),QString::number(rec.x()));
        xmlWriter.writeAttribute(QString("y"),QString::number(rec.y()));
        xmlWriter.writeAttribute(QString("width"),QString::number(rec.width()));
        xmlWriter.writeAttribute(QString("height"),QString::number(rec.height()));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

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
        // std::cerr << "Error: Cannot read file " << qPrintable(filename)
        //  << ": " << qPrintable(file.errorString())
        //  << std::endl;
    }
    QXmlStreamReader Rxml;
    Rxml.setDevice(&file);
    //Rxml.readNext();

    while(!Rxml.atEnd())
    {
        Rxml.readNext();
        qDebug()<<Rxml.name();
        if(Rxml.isStartElement())
        {
            if(Rxml.name() == "Object")
            {

                int x = Rxml.attributes().value("x").toString().toInt();
                int y = Rxml.attributes().value("y").toString().toInt();
                int width = Rxml.attributes().value("width").toString().toInt();
                int height = Rxml.attributes().value("height").toString().toInt();
                qDebug()<< x << y << width << height;
            }
            qDebug()<<Rxml.name();
        }
    }
    file.close();
    statusBar()->showMessage(tr("Fig Opened"));
}

