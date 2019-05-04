#include "searcherworker.h"
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QTableWidgetItem>


SearcherWorker::SearcherWorker(QStringList &list,QMutex* mutex,QTableWidget* table)
{
    m_list= list;
     m_mutex= mutex;
    m_tableResult= table;
    m_maxResult= 23;
    m_keyWord= 0;
    m_abort = false;



}

SearcherWorker::~SearcherWorker()
    {
       m_abort=true;
    }


void SearcherWorker::run()
{
    if(m_keyWord==0)
        return;
    
    while(!m_list.isEmpty())
    {
       m_mutex->lock();
       QString fileName = m_list.takeFirst();
       m_mutex->unlock();

       search(fileName);
       
       if(m_abort)
       return;

    }

}

void SearcherWorker::setKeyWord(char* s)
{
    m_keyWord= s;
}

void SearcherWorker::setList(QStringList &l)
{
    m_list=l;
}

void SearcherWorker::search(QString fileName)
{
    QFile file(fileName);

    if(m_keyWord==0)
        return;

 if(file.open(QFile::ReadOnly | QFile::Truncate))
    {
        QTextStream str(&file);
        str.setCodec("UTF-8");
        QString line;

        do{
            line = str.readLine();
            if(line.indexOf(m_keyWord,Qt::CaseInsensitive)!=-1)
            {
                qDebug()<<line;
                int id= line.indexOf("VALUES",Qt::CaseSensitive);

                if(id==-1)
                    continue;

                QString s = line.left(id-1);
                QString livre= s.split(" ").at(2);


               int idd= line.indexOf("'");
                s= line.left(idd-2);
                id=s.indexOf("(");
                QString h= s.right(s.length()-id-1);

                QString chapitre= h.split(",").first();
                QString verset = h.split(",").last();

                qDebug()<<chapitre.trimmed();
                qDebug()<<verset.trimmed();

                QString text= line.right(line.length()-idd);
                int idEnd= text.indexOf(");");
                text.truncate(idEnd-2);
                qDebug()<<text;

                 m_mutex->lock();

                 int rowNumber = m_tableResult->rowCount();
                 rowNumber++;
                 m_tableResult->setRowCount(rowNumber);

               QTableWidgetItem *newItem = new QTableWidgetItem(livre+" : "+chapitre+"-"+verset);
               QStringList list;
               list<<livre<<chapitre<<verset;
               newItem->setData(1,QVariant(list));
               m_tableResult->setItem(rowNumber, 0, newItem);

               QTableWidgetItem *textFound = new QTableWidgetItem(text);
               m_tableResult->setItem(rowNumber, 1, textFound);

                m_mutex->unlock();

            }

        }while(!line.isNull() && !m_abort);

file.close();

    }else
 {
        m_mutex->unlock();
        qDebug("SearcherWorker::search file not opened");
    }


}
