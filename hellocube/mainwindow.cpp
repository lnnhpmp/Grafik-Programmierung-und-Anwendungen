#include "mainwindow.h"
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenuBar();
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
    exitAction->setShortcut(QKeySequence::Quit);
    fileMenu->addAction(exitAction);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);
}
