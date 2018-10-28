#include "mainwindow.h"
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createShadingMenu();
    createAboutMessBox();
    createMenuBar();
    add_ToolBar();

    /****************************set opengl widget****************************/
    glwidget = new GLWidget();
    if (!centralWidget())
        setCentralWidget(glwidget);
    else
        QMessageBox::information(0, tr("Cannot set central widget."), tr("Try again."));
    /****************************set opengl widget****************************/

    this->statusBar()->showMessage("Set label text.");
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuBar()
{
    menuBar = new QMenuBar();
    fileMenu = new QMenu("&File");

    exitAction = new QAction("E&xit" , fileMenu);
    exitAction->setShortcut(Qt::CTRL | Qt::Key_Q);
    connect(exitAction , SIGNAL(triggered()) , this , SLOT(close()));

    /********************file menu********************/
    fileMenu->addAction(exitAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(Shading_Menu);
    menuBar->addAction(AboutMB);
    /********************file menu********************/

    setMenuBar(menuBar);
}

void MainWindow::createShadingMenu()
{
    Shading_Menu = new QMenu("&Shading");
    // none wireframe
    None = new QAction("&None(Wireframe)", Shading_Menu);
    None->setShortcut(QKeySequence("Ctrl+1"));
    None->setIcon(QIcon(":/img/wireframe.png"));
    None->setCheckable(true);
    //connect(None, SIGNAL(triggered()), glwidget, SLOT(setWireframeShading()));
    Shading_Menu->addAction(None);

    // flat
    Flat = new QAction("&Flat", Shading_Menu);
    Flat->setShortcut(QKeySequence("Ctrl+2"));
    Flat->setIcon(QIcon(":/img/flat.png"));
    Flat->setCheckable(true);
    Flat->setChecked(true);
    //connect(Flat, SIGNAL(triggered()), glwidget, SLOT(setFlatShading()));
    Shading_Menu->addAction(Flat);

    // gouraud
    Gouraud = new QAction("&Gouraud", Shading_Menu);
    Gouraud->setShortcut(QKeySequence("Ctrl+3"));
    Gouraud->setIcon(QIcon(":/img/gouraud.png"));
    Gouraud->setCheckable(true);
    //connect(Gouraud, SIGNAL(triggered()), glwidget, SLOT(setGouraudShading()));
    Shading_Menu->addAction(Gouraud);

    // phong
    Phong = new QAction("&Phong", Shading_Menu);
    Phong->setShortcut(QKeySequence("Ctrl+4"));
    Phong->setIcon(QIcon(":/img/phong.png"));
    Phong->setCheckable(true);
    //connect(Phong, SIGNAL(triggered()), glwidget, SLOT(setPhongShading()));
    Shading_Menu->addAction(Phong);
}

void MainWindow::createAboutMessBox()
{
    AboutMB = new QAction("About");
    connect(AboutMB, SIGNAL(triggered()), this, SLOT(showAboutBox()));
}

void MainWindow::showAboutBox()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About Hello Cube!");
    msgBox.setText("Written by Fangyu!");
    msgBox.exec();
}

void MainWindow::add_ToolBar()
{
    Tool_Bar = addToolBar("main toolbar");
    Tool_Bar->addAction(None);
    Tool_Bar->addAction(Flat);
    Tool_Bar->addAction(Gouraud);
    Tool_Bar->addAction(Phong);

}
