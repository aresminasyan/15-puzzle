#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pix(":/pictures/icon.png");
    QIcon icon(pix);
    a.setWindowIcon(icon);
    MainWindow *wind = new MainWindow();
    wind->show();




    return a.exec();
}
