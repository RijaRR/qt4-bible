#include "loaderworker.h"
#include <QtDebug>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QTime>
#include <QList>
#include <QPair>


LoaderWorker::LoaderWorker()
{

   _abort=false;

}

LoaderWorker::~LoaderWorker()
{

   mutex.lock();
   _abort=true;
   condition.wakeOne();
   mutex.unlock();

   wait();
}




int LoaderWorker::getMinIndex()
{

    if(_stack.isEmpty())
        return -1;

     int minI = 0;
     QTime min= _stack.at(0).second;

    for(int i=1; i<_stack.size();i++)
    {
        QPair <QString,QTime> pair = _stack.at(i);
        if(pair.second<min)
        {
            qDebug()<<pair.first;
           min=pair.second;
           minI=i;
        }
    }

    return minI;

}


void LoaderWorker::addSqlOrder(QString sql, int timeout)//en seconde
{


       mutex.lock();


if(timeout<0)
    return;

      QTime executionTime = QTime::currentTime().addSecs(timeout);
       QPair <QString,QTime> pair;
       pair.first=sql;
       pair.second= executionTime;
       int e=-1;
        for(int i=1; i<_stack.size();i++)
    {
        QPair <QString,QTime> pair = _stack.at(i);
        if(pair.first==sql)
        {
            e=i;
        }
    }
       if(e!=-1)
        {
           _stack.replace(e,pair);
       }else
       {
            _stack.append(pair);
       }

      mutex.unlock();

        if (!isRunning()) {
            qDebug("start ");
        start(LowPriority);
         } else {

        condition.wakeOne();

         }



}



void LoaderWorker::run()
{
    int k=9999;
    forever{
      mutex.lock();


      if(_stack.isEmpty())
      {
            condition.wait(&mutex);
      }

      int indexMin= getMinIndex();

      if(indexMin==-1)
      {
          qDebug()<<_stack.size()<<"-ERREUR GRAVE-"<<indexMin;
          return;
      }

      QPair <QString,QTime> pair = _stack.at(indexMin);
      int timeFromExecution = QTime::currentTime().msecsTo(pair.second);
      if(timeFromExecution < 59)
      {
          QSqlQuery q(pair.first);
          if(q.lastError().isValid())
          {
            qDebug()<<"LoaderWorker error sql"+ q.lastError().text();
          }

          if(!_stack.removeOne(pair))
          {
              qDebug("run erreur suppression");
             mutex.unlock();
          }
      }else
      {
              condition.wait(&mutex,timeFromExecution);
      }

      if(_abort)
      {

          for(int i=0;i<_stack.size();i++)
          {
              QPair <QString,QTime> pair = _stack.at(i);
              QSqlQuery q(pair.first);

          if(q.lastError().isValid())
          {
            qDebug()<<"LoaderWorker error sql abort"+ q.lastError().text();
          }
          }
         return;
      }

      mutex.unlock();


       k++;
       if(k>90000)
       {
           qDebug("boucle worker");
          return;
       }

    }


}
