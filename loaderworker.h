#ifndef LOADERWORKER_H
#define LOADERWORKER_H
 #include <QThread>
#include <QList>
#include <QPair>
#include <QTime>
#include <QMutex>
#include <QWaitCondition>

#include "loader.h"

class LoaderWorker : public QThread
{

public:
     LoaderWorker();
     ~LoaderWorker();

     void run();
     void addSqlOrder(QString sql, int timeout=10);

private:
     QList<QPair <QString,QTime> > _stack;
     bool _abort;
     QMutex mutex;
     QWaitCondition condition;
     int getMinIndex();




};

#endif // LOADERWORKER_H
