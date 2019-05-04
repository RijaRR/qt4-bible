

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <QFile>
#include <QVariant>
#include <QSqlRecord>
#include <QTextStream>
#include <QStringList>
#include <QDir>
#include <QMessageBox>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
qDebug("appel create connection");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        qDebug("createConnection: unable to open database");
          QMessageBox::critical(0,"Erreur interne de l'application",
            "QSQLITE non pris en charge ", QMessageBox::Ok);
        return false;
    }
    QSqlQuery query;

    if(!query.exec("create table livre (idTable int primary key,nomTableMg varchar(20),"
                                     "nomTableFr varchar(20),nomLivreFr varchar(20),nomTableEn varchar(20),"
                                     "maxChapMg int,maxChapFr int,maxChapEn int,"
                                     "posBeginMg int,posBeginFr int,posBeginEn,"
                                     "posEndMg int,posEndFr int,posEndEn,"
                                     "type varchar(1) not null,loadedmg varchar(1),loadedfr varchar(1),"
                                     "loadeden varchar(1),"
                                     "blocMg int,blocFr int,blocEn int)"))
    {
         qDebug("createConnection: erreur creation table livre");
         qDebug()<<query.lastError().text();
         return false;
    }

    if(!query.exec("CREATE TABLE maxAndininy("
"idTable int NOT NULL ,"
"toko int NOT NULL ,"
"maxAndMg int NOT NULL ,"
"maxAndFr int NOT NULL ,"
"maxAndEn int NOT NULL );"))
    {
        qDebug("createConnection: erreur creation table maxAndininy");
         qDebug()<<query.lastError().text();
        return false;
    }

    QString mn= QDir::currentPath();

     QString max=mn+"/text/max.txt";
    QString livre=mn+"/text/livre.txt";

   QFile btt(livre);
   QFile mtt(max);
   if(btt.open(QFile::ReadOnly | QIODevice::Text) && mtt.open(QFile::ReadOnly | QIODevice::Text))
       {

     QTextStream livre(&btt);
     QTextStream max(&mtt);
     QString record;
     QString sql;
     QString n= "','";


     do{

         record= livre.readLine();
         QStringList l= record.split(",");

         if(l.size()==18)
         {
         sql= "INSERT INTO livre VALUES('"+l.at(0)+n+l.at(1)+n+l.at(2)+n+l.at(3)+n+l.at(4)+
              n+l.at(5)+n+l.at(6)+n+l.at(7)+n+l.at(9)
              +n+l.at(10)+n+l.at(11)+n+l.at(12)+n+l.at(13)+n+l.at(14)+n+l.at(8)+
              n+"n"+n+"n"+n+"n"+n+l.at(15)+n+l.at(16)+n+l.at(17)+"');";

        QSqlQuery insertLivre;
        if(!insertLivre.exec(sql))
        {
            qDebug()<<"erreur pour"<<sql;
            qDebug()<<insertLivre.lastError().text();
            return false;
        }
        }else
         {
            if(record.size()!=0)
            {
            qDebug()<<"erreur de formatage du fichier livre.txt";
             qDebug()<<record.length();
            return false;
            }
        }
     }while(!record.isNull());

     record.clear();
     sql.clear();
     do{
        record = max.readLine();
        QStringList l= record.split(",");
        if(l.size()==5)
        {
        sql= "INSERT INTO maxAndininy VALUES('"+l.at(0)+n+l.at(1)+n+l.at(2)+n+
             l.at(3)+n+l.at(4)+"');";

        QSqlQuery insertMax;
        if(!insertMax.exec(sql))
        {
            qDebug()<<"erreur pour"<<sql;
            qDebug()<<insertMax.lastError().text();
            return false;
        }
        }

     }while(!record.isNull());

    }else
    {
      qDebug("createFirstTables:: erreur lors d'ouverture des fichiers TT");
      QMessageBox::critical(0,"Fichier introuvable",
            "Les fichiers max.txt et livre.txt sont introuvables ", QMessageBox::Ok);
      qDebug()<<livre<<max;
       return false;
    }

return true;

}


#endif
