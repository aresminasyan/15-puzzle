#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->setFixedSize(400,470);
    w = new Desk(this);
    dial = new MyDialogOp(this);
    w->setGeometry(0,20,400,450);
    QObject::connect(w, SIGNAL(ToClose()), this, SLOT(close()));
    CreateActions();
    CreateMenu();
    QObject::connect(dial, SIGNAL(imageChange(int, QString)), w, SLOT(ImageChangeW(int, QString)));
}

void MainWindow::CreateActions()
{
    NewGameAction = new QAction(tr("&New Game"),this);
    QObject::connect(NewGameAction,SIGNAL(triggered()),w,SLOT(resetgame()));
    ExitAction = new QAction(tr("&Exit"),this);
    QObject::connect(ExitAction, SIGNAL(triggered()),this, SLOT(Exit()));
    OptionsAction = new QAction(tr("&Options"),this);
    QObject::connect(OptionsAction, SIGNAL(triggered()),this,SLOT(Options()));
    AboutAction = new QAction(tr("&About"),this);
}
void MainWindow::CreateMenu()
{
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addAction(NewGameAction);
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAction);
    ToolsMenu = menuBar()->addMenu(tr("&Tools"));
    ToolsMenu->addAction(OptionsAction);
    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu ->addAction(AboutAction);
}


