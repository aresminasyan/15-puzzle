#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QCheckBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "mydialogop.h"
#include "desk.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private:
    void CreateActions();
    void CreateMenu();
private:
    QMenu *FileMenu;
    QMenu *ToolsMenu;
    QMenu *HelpMenu;
    QAction *NewGameAction;
    QAction *ExitAction;
    QAction *OptionsAction;
    QAction *AboutAction;

signals:
    
public slots:
    void NewGame(){}

    void Exit()
    {
        this->close();
    }

    void Options()
    {
       // painter.drawRoundedRect(10,10,100,100,5,5);
        qDebug()<<3;


        dial->show();

    }

    void About(){}

private:
    Desk *w;
    MyDialogOp *dial;
    
};

#endif // MAINWINDOW_H
