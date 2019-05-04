#include <QtGui/QApplication>
#include "mainwindow.h"
#include "connection.h"
#include <QThread>


void ch(QString &s)
{
    s.truncate(3);   
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug()<<QThread::idealThreadCount();
    QString e="mljmlk";
    ch(e);
    qDebug()<<e;



    MainWindow* w=0;
    if(createConnection())
    {
        w= new MainWindow();
        w->show();
    }else
    {
        return 0;
    }



    return a.exec();
}
