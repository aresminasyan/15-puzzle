#ifndef MYDIALOGOP_H
#define MYDIALOGOP_H

#include <QDialog>
#include <QFileDialog>
#include <QFont>
#include <QPainter>
#include <QRadioButton>
#include <QPushButton>
#include <QDebug>

class MyDialogOp : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialogOp(QWidget *parent = 0)
    {

        qDebug()<<4;

        qDebug()<<5;
        this->setWindowTitle("Options");
        this->setFixedSize(380,250);
        font=QFont("Calibri",10);

        image = new QWidget(this);
        image->setGeometry(10,10,100,100);


        a = new QRadioButton(image);
        a->setText("Numbers");
        a->setFont(font);
        a->setGeometry(10,0,100,40);
        a->setChecked(true);
        b =  new QRadioButton(image);
        b->setText("Letters");
        b->setFont(font);
        b->setGeometry(10,20,100,40);
        c =  new QRadioButton(image);
        c->setText("Image");
        c->setFont(font);
        c->setGeometry(10,48,100,40);

        QObject::connect(c, SIGNAL(toggled(bool)), this, SLOT(C_radiobutton_set(bool)));


        ok_button = new QPushButton(this);
        ok_button->setText("OK");
        ok_button->setFont(font);
        ok_button->setGeometry(270,170,80,40);

        QObject::connect(ok_button, SIGNAL(clicked()), this , SLOT(option_ok()));


        browse_button = new QPushButton(this);
        browse_button->setText("Browse...");
        browse_button->setFont(font);
        browse_button->setGeometry(10,100,80,30);
        browse_button->setEnabled(false);

        QObject::connect(browse_button, SIGNAL(clicked()), this , SLOT(browseslot()));


        this->repaint();

    }

    void paintEvent(QPaintEvent *)
    {
        painter = new QPainter(this);
        painter->setPen(Qt::lightGray);
        painter->drawLine(10,65,110,65);
        painter->end();
    }

private:
    QFont font;
    QPainter *painter;
    QWidget *image;
    QRadioButton *a;
    QRadioButton *b;
    QRadioButton *c;
    QPushButton *browse_button;
    QPushButton *ok_button;
    QString fileName;
    
signals:
    void imageChange(int,QString);
    
public slots:
    void option_ok()
    {
        if(a->isChecked())
            emit imageChange(1,"");
        if(b->isChecked())
            emit imageChange(2,"");
        if(c->isChecked()){
            emit imageChange(3,fileName);
            qDebug() << fileName;
        }

        this->close();
    }

    void C_radiobutton_set(bool flag)
    {

        browse_button->setEnabled(flag);

    }

    void browseslot()
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                         "/home",
                                                         tr("Images (*.png *.xpm *.jpg)"));

    }

    
};

#endif // MYDIALOGOP_H
