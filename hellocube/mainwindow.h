#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "glwidget.h"
#include <QMainWindow>
#include <QtWidgets>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createMenuBar();
    void createShadingMenu();
    void createAboutMessBox();
    void add_ToolBar();

public slots:
    void showAboutBox();

private:
    // file menu
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;

    // shading menu
    QMenu *Shading_Menu;
    QActionGroup *shadingGroup;
    QAction *None;
    QAction *Flat;
    QAction *Gouraud;
    QAction *Phong;

    // about message box
    QAction *AboutMB;

    // toolbar
    QToolBar *Tool_Bar;

    //
    GLWidget *glwidget;
};

#endif // MAINWINDOW_H
