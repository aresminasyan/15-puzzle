#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <ctime>
#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>


class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0):QWidget(parent)
    {
        start=false;
        this->setFixedSize(301,301);
        rects = new QRect* [4];
        for(int i=0; i<4; i++)
            rects[i]= new QRect [4];

        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                rects[i][j]= QRect(j*75,i*75,75,75);

        places = new int* [4];
        for(int i=0; i<4; i++)
            places[i]= new int [4];
        this->grabKeyboard();
        int k=1;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                places[i][j]=k++;
        places[3][3]=0;
        score=0;
        free_x=3;
        free_y=3;
        QObject::connect(this, SIGNAL(Finish()), this, SLOT(Message()));

        Rand();
        start=true;
        imagepath = QString(":/pictures/15.png");
        image = QImage(imagepath);
        //image = QImage("D:\Dragon.jpeg");
        image=image.scaled(300,300);

    }

    void Res()
    {
         start=false;
         this->grabKeyboard();
         score=0;
         Rand();
         start=true;
         image = QImage(imagepath);
         image=image.scaled(300,300);

         this->repaint();
    }

    void paintEvent(QPaintEvent *event)
    {
        event->accept();
        painter = new QPainter(this);

        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                if(places[i][j]==0){
                   painter->setBrush(Qt::black);
                   painter->setPen(Qt::black);
                    painter->drawRect(rects[i][j]);
                }
                if(places[i][j]==1)
                    painter->drawImage(rects[i][j],image,rects[0][0]);
                if(places[i][j]==2)
                    painter->drawImage(rects[i][j],image,rects[0][1]);
                if(places[i][j]==3)
                    painter->drawImage(rects[i][j],image,rects[0][2]);
                if(places[i][j]==4)
                    painter->drawImage(rects[i][j],image,rects[0][3]);
                if(places[i][j]==5)
                    painter->drawImage(rects[i][j],image,rects[1][0]);
                if(places[i][j]==6)
                    painter->drawImage(rects[i][j],image,rects[1][1]);
                if(places[i][j]==7)
                    painter->drawImage(rects[i][j],image,rects[1][2]);
                if(places[i][j]==8)
                    painter->drawImage(rects[i][j],image,rects[1][3]);
                if(places[i][j]==9)
                    painter->drawImage(rects[i][j],image,rects[2][0]);
                if(places[i][j]==10)
                    painter->drawImage(rects[i][j],image,rects[2][1]);
                if(places[i][j]==11)
                    painter->drawImage(rects[i][j],image,rects[2][2]);
                if(places[i][j]==12)
                    painter->drawImage(rects[i][j],image,rects[2][3]);
                if(places[i][j]==13)
                    painter->drawImage(rects[i][j],image,rects[3][0]);
                if(places[i][j]==14)
                    painter->drawImage(rects[i][j],image,rects[3][1]);
                if(places[i][j]==15)
                    painter->drawImage(rects[i][j],image,rects[3][2]);
            }
        painter->end();
    }

    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key()==Qt::Key_Right)
           if(free_y > 0)
               Move(free_x, free_y-1);

        if(event->key()==Qt::Key_Left)
           if(free_y < 3)
               Move(free_x, free_y+1);

        if(event->key()==Qt::Key_Down)
           if(free_x > 0 )
              Move(free_x-1, free_y);

        if(event->key()==Qt::Key_Up)
           if(free_x < 3 )
               Move(free_x+1, free_y);


        if(Check())
            emit Finish();
        this->repaint();

    }

    void mousePressEvent(QMouseEvent *event)
    {

        int x, y;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if(event->button()==Qt::LeftButton &&
                        rects[i][j].contains(event->x(), event->y(), true))
                {
                    x=i; y=j;
                    break;
                }
        Move(x,y);
        this->repaint();
        if(Check())
            emit Finish();

    }


signals:
    void Finish();
    void ScoreChanged(QString str);
    void CloseApp();
    void ResGame();

public slots:
    void ImgChangemw(int num, QString path)
    {
        if(num == 1)
            imagepath = QString(":/pictures/15.png");
        if(num == 2)
            imagepath = QString(":/pictures/Tulips.jpg");
        if(num==3)
           { imagepath = QString(path);
            qDebug()<<path;
        }
        Res();
    }

    void Message()
    {
        this->releaseKeyboard();
        QFont myfont("Arial", 15);
        messageBox.setFont(myfont);
        messageBox.setText("     You Won!  \nYour Score is "+QString::number(score)+"  ");
        messageBox.setStandardButtons(QMessageBox::Close | QMessageBox::Reset);

       int ret= messageBox.exec();
       if(ret == QMessageBox::Close)
           emit CloseApp();
       if(ret == QMessageBox::Reset)
           emit ResGame();

    }

private:
    QRect **rects;
    QPainter *painter;
    int **places;
    QImage image;
    int free_x;
    int free_y;
    int score;
    bool start;
    QMessageBox messageBox;
    QString imagepath;


    void Move(int x, int y)
    {
        int y1=free_y, x1=free_x;
        if(x==free_x || y== free_y){
        if(x==free_x)
        {
            if(y<free_y)
                while(y1!=y){
                   places[x1][y1]=places[x1][y1-1];
                   y1--;
                }
            if(y>free_y)
                while(y1!=y){
                    places[x1][y1]=places[x1][y1+1];
                     y1++;
                }

        }

        if(y==free_y)
        {
            if(x<free_x)
                while(x1!=x){
                    places[x1][y1]=places[x1-1][y1];
                     x1--;
                }
            if(x>free_x)
                while(x1!=x){
                    places[x1][y1]=places[x1+1][y1];
                     x1++;
                }
        }
        places[x][y]=0;

        if(start && !(free_x == x && free_y == y)){
            score++;
            QString sc="Steps ";
            sc+=QString::number(score);
            emit ScoreChanged(sc);
        }

        free_x = x;
        free_y = y;


        }
    }

    void Rand()
    {
        int x2, y2;
        srand(time(NULL));
        int rand1=rand();
        srand(rand1);
        int rand2=rand();
        for(int i=0; i<10000; i++)
        {
            srand(rand1);
            rand1=rand();
            x2=rand1%4;
            srand(rand2);
            rand2=rand();
            y2=rand2%4;
            Move(x2,y2);
        }
        Move(free_x, 3);
        Move(3,3);
    }

    bool Check()
    {
        int k=1;
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                if((i+j)!=6 && places[i][j]!=k++)
                    return false;
        if(places[3][3]!=0)
            return false;
        return true;


    }


};

#endif // MYWIDGET_H
