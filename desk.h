#ifndef DESK_H
#define DESK_H

#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include "mywidget.h"

class Desk : public QWidget
{
    Q_OBJECT
public:
    explicit Desk(QWidget *parent = 0):QWidget(parent)
    {
        this->setFixedSize(400,450);
        mw= new MyWidget(this);
        mw->setGeometry(50,80,300,300);
        lb = new QLabel("Steps 0",this);
        lb->setGeometry(100,20,250,40);
        QFont Scorefont("Arial", 25);
        lb->setFont(Scorefont);
        lb->setAlignment(Qt::AlignRight);
        QObject::connect(mw,SIGNAL(ScoreChanged(QString)),lb, SLOT(setText(QString)));
        QObject::connect(mw, SIGNAL(CloseApp()), this, SLOT(Close()));
        QObject::connect(mw, SIGNAL(ResGame()), this, SLOT(resetgame()));
        QObject::connect(this, SIGNAL(ImChangeW(int,QString)), mw, SLOT(ImgChangemw(int,QString)));

    }


signals:
    void ToClose();
    void ImChangeW(int,QString);

public slots:
    void resetgame()
    {
       mw->Res();
       lb->setText("Steps 0");
    }

    void Close()
    {
        emit ToClose();
    }

    void ImageChangeW(int a, QString str)
    {
        emit ImChangeW(a,str);
    }


private:
    MyWidget *mw;
    QLabel *lb;
};

#endif // DESK_H
