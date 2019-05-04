#include "loader.h"

#include <QMessageBox>
#include <QtDebug>
#include <QTextStream>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QPair>
#include <QDir>
#include <QCompleter>



//bversion 3
Loader::Loader()
{
    initBlocDico();
}

 QList< QPair<int, QString> > Loader::getBloc(QString lang)
{
    if(lang=="mg")
        return  _myBlocsMg;
    if(lang=="fr")
        return _myBlocsFr;
    if(lang=="en")
        return _myBlocsEn;
}


void Loader::setMaxVersetTo(int k,QComboBox* versetEndCombo,QComboBox* versetBeginCombo)
{

       versetEndCombo->clear();

    if(versetBeginCombo->count()!=0)
    {

        QString data= versetBeginCombo->itemData(k).toString();
        int beginVerse=data.split(",").at(0).toInt();
        int maxVerse= data.split(",").at(1).toInt();
        int endVerse = versetEndCombo->itemData(versetEndCombo->currentIndex()).toInt();
        qDebug()<<"end verse"<<endVerse;
        versetEndCombo->clear();

            for(int i=beginVerse;i<(maxVerse+1);i++)
            {
                versetEndCombo->insertItem(i,QString::number(i),QVariant(i));
            }


     versetEndCombo->setCurrentIndex(versetEndCombo->count()-1);
    }



}



void Loader::setMaxVersetFrom(int k,QString m_maxChap,QString m_tableName,QComboBox* bookCombo,
                              QComboBox* versetBeginCombo,QComboBox* versetEndCombo,QComboBox* chapterCombo)
{
    int numChap = chapterCombo->itemData(k).toInt();
    if(numChap!=0)
    {
    QString tableName = bookCombo->itemData(bookCombo->currentIndex()).toString();
    QString maxAnd=m_maxChap;
    QString a= "SELECT m."+maxAnd.replace(QString("Chap"),QString("And"))+" FROM livre l,maxAndininy m WHERE ";
    QString b = "l."+m_tableName+"='"+tableName+"' AND m.idTable=l.idTable AND m.toko='"+QString::number(numChap)+"';";
    QString sql=a+b;
    QSqlQuery query(sql);
    if(!query.lastError().isValid())
    {
        int maxVerset;
         while(query.next())
        {
         maxVerset = query.value(0).toInt();
         }
         versetBeginCombo->clear();
         versetEndCombo->clear();
         int l=0;

         for(int i=1;i<(maxVerset+1);i++)
         {
             if(200<l)
             {//dans le cas où la requête n'a pas eu de résultat on a une grande valeur de maxVerset retourné par sqllite

                 qDebug()<<"!!!!!!!ERreur max verset = "<<maxVerset;
                  break;
             }

            versetBeginCombo->insertItem(i,QString::number(i),QVariant(QString::number(i)+","+QString::number(maxVerset)));
           // versetEndCombo->insertItem(i,QString::number(i),QVariant(i));
            l++;
         }
         versetEndCombo->setCurrentIndex(versetEndCombo->count()-1);

    }
    else{
      qDebug()<<"erreur BibleWidget::setMaxVersetFrom "+ query.lastError().text()+sql;
    }
}

}



void Loader::setMaxChapitre(int indexCombo,QComboBox* bookCombo,QComboBox* chapterCombo,QString m_tableName,
                            QString m_maxChap)
{

    if(bookCombo->count()!=0)
    {
    QString tableName = bookCombo->itemData(indexCombo).toString();


    QString sql="SELECT "+m_maxChap+" FROM livre WHERE "+m_tableName+"='"+tableName+"'";
    QSqlQuery query(sql);


    if(!query.lastError().isValid())
    {
        chapterCombo->clear();
        int maxChap=-1;
        while(query.next())
        {
            maxChap=query.value(0).toInt();
        }
        if(maxChap==-1 || maxChap>1100000)
        {
            qDebug("erreur BibleWidget::setMaxChapitre");
            qDebug()<<" SELECT "+m_maxChap+" FROM livre WHERE "+m_tableName+"='"+tableName+"'";
            return;
        }

        for(int i=1;i<(maxChap+1);i++)
        {
             chapterCombo->insertItem(i,QString::number(i),QVariant(i));
        }

    }else
    {
       qDebug()<<"erreur BibleWidget::setMaxChapitre: SELECT "+m_maxChap+" FROM livre WHERE "+m_tableName+"='"+tableName+"'";
    }
}

}





 QString Loader::loadReference(QString tableName,int chapter,int verseBegin,int verseEnd,QString type ,bool stripNumber)
 {
     if(!loadTable(tableName,type))
         return QString();
     if(verseBegin>verseEnd)
     {
         qDebug("début supérieur à fin");
         return QString();
     }

     QString sql;
     QString result;
if(verseBegin==verseEnd)
     {
    sql= "SELECT andininy, lahatsoratra FROM "+tableName+" WHERE toko='"+
         QString::number(chapter)+"' AND andininy='"+QString::number(verseBegin)+"';";
}else{
    sql= "SELECT andininy, lahatsoratra FROM "+tableName+" WHERE toko='"+
         QString::number(chapter)+"' AND andininy BETWEEN '"+QString::number(verseBegin)+"' AND '"+
         QString::number(verseEnd)+"';";
}
QSqlQuery query(sql);
if(query.lastError().isValid())
{
    qDebug()<<query.lastError().text()+"Loader::loadReference"<<sql;
    return QString();
}else
{

    while(query.next())
    {
        if(!stripNumber)
        {
         result= result+" "+query.value(0).toString()+" "+query.value(1).toString();
        }else{
        result= result+" "+query.value(1).toString();
         }
    }
}

return result.trimmed();

 }


void Loader::initComboBook(QString m_tableName,QString m_language,QComboBox* bookCombo)
{
    QSqlQuery query;
    QStringList list;
    if(m_language!="fr")
    {
    QString sql= "SELECT "+m_tableName+" FROM livre";
    if(!query.exec(sql))
    {
        qDebug()<<"BibleWidget::initComboBook() "+query.lastError().text();
        return;
    }
    int k=0;
    while(query.next())
    {
        QString tableName= query.value(0).toString();
        QString bookName =Loader::bookName(tableName);
        bookCombo->insertItem(k,bookName,QVariant(tableName));
        list.append(bookName);
        k++;
    }
   }else if(m_language=="fr")
    {
       QString sql= "SELECT "+m_tableName+",nomLivreFr FROM livre";
    if(!query.exec(sql))
    {
        qDebug()<<"BibleWidget::initComboBook() 2 "+query.lastError().text();
        return;
    }
    int k=0;
    while(query.next())
    {
        QString tableName= query.value(0).toString();
        QString bookName =query.value(1).toString();
        bookCombo->insertItem(k,bookName,QVariant(tableName));
        list.append(bookName);
        k++;
    }

   }

    QCompleter* comp= new QCompleter(list,bookCombo);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    bookCombo->setCompleter(comp);


    }



QString Loader::bookName(QString k)
{
    if(k.indexOf("tonon")!=-1)
       return QString("Tonon-kira");
    if(k.indexOf("song_of")!=-1)
        return QString("Song of Solomon");

   QChar l= k.at(0);
   k.replace(0,1,l.toUpper());
   if(k.indexOf("_")!=-1)
   {
   k.replace(QString("_"),QString(" "));
   QString r= k.right(k.length()-k.indexOf(" "));
   k.truncate(k.indexOf(" "));
   return k+r.toUpper();
   }

   return k;
}



QString* Loader::keyResolver(QString type)
{
    QString *t=new QString[5];
     t[0]="nomTable";
     t[1]="maxChap";
    t[4]="bloc";
    t[2]="posBegin";
    t[3]= "posEnd";
 for(int i=0;i<5;i++)
    {
      if(type=="mg")
{
    t[i]=t[i]+"Mg";
}else if(type=="fr")
{
    t[i]=t[i]+"Fr";
}else if(type=="en")
{
    t[i]=t[i]+"En";  ;
}else{
    qDebug()<<"Loader::keyResolver langue invalide";
    break;
}
}

return t;
}

/*
    QString m_language;
    QString m_tableName;0
    QString m_maxChap;1
    QString m_posBegin;2
    QString m_posEnd;3
    QString m_bloc;4
  */

QString Loader::translateTableName(QString src,QString languageSrc, QString languageDst)
{
   QString* s = keyResolver(languageSrc);
   QString* d= keyResolver(languageDst);
   QString sql="SELECT "+d[0]+" FROM livre WHERE "+s[0]+"='"+src+"';";
   QSqlQuery query(sql);
   if(query.lastError().isValid())
   {
       qDebug()<<"Loader::translateTableName"+query.lastError().text();
       return QString();
   }
   QString res;
   while(query.next())
   {
       res= query.value(0).toString();
   }
   return res;
}





bool Loader::loadTable(QString tableName,QString type)//type= language
{
QString table;
QString bloc;
QString posB;
QString posE;


if(type=="mg")
{
    table="nomTableMg";
    bloc="blocMg";
    posB="posBeginMg";
    posE= "posEndMg";
}else if(type=="fr")
{
     table="nomTableFr";
    bloc="blocFr";
    posB="posBeginFr";
    posE= "posEndFr";
}else if(type=="en")
{
    table="nomTableEn";
    bloc="blocEn";
    posB="posBeginEn";
    posE= "posEndEn";
}else{
    qDebug()<<"langue invalide";
    return false;
}


QSqlQuery query;
QString s=",";
QString sql = "SELECT "+bloc+s+posB+s+posE+s+"loaded"+type+" FROM livre WHERE "+table+"='"+tableName+"';";
bool found=false;
QString loaded;
int blocNum=-1;
int posStart=-1;
int posEnd=-1;
int k=0;


if(!query.exec(sql))
{
   qDebug()<<"Erreur sql pour "+sql;
    qDebug()<<query.lastError().text();
}

while(query.next())
{
    k++;
  found=true;
blocNum= query.value(0).toInt();
posStart= query.value(1).toInt();
posEnd= query.value(2).toInt();
loaded= query.value(3).toString();
}

if(1<k)
{
     qDebug()<<"Erreur sql pour, il y a deux resultats"+sql;
    return false;
}else if(loaded=="y")
{
    qDebug()<<"livre déjà chargé dans la base";
    return true;
}else if(!found)
{
    qDebug()<<"livre introuvable ";
    return false;
}

if((posEnd==-1 && posStart==-1) || blocNum==-1)
{
    qDebug("quelque chose ne marche pas");
    qDebug()<<"blocNum="<<blocNum<<posStart<<posEnd<<loaded;
    return false;
}


QString fileBlock;
if(type=="mg")
{
    fileBlock=_myBlocsMg.at(blocNum-1).second;
}else if(type=="fr")
{

    fileBlock=_myBlocsFr.at(blocNum-1).second;
     qDebug()<<blocNum<<fileBlock;
}else if(type=="en")
{
    fileBlock=_myBlocsEn.at(blocNum-1).second;
}

QFile file(QDir::currentPath()+fileBlock);

 if(file.open(QFile::ReadOnly | QFile::Truncate))
    {
        QTextStream str(&file);
        str.setCodec("UTF-8");
        QString line;
        QString sql;
        k=1;
        bool concat=false;
        if(posEnd==-1)
        {
            posEnd=7000;
        }

        do{
            line= str.readLine();

            if(k>=posStart)
            {
                 if((line.startsWith("CREATE TABLE") || line.startsWith("INSERT")))
                 {
                     concat=true;
                 }
                 if(concat)
                 {
                     sql=sql+line;
                     if(sql.endsWith(";"))
                     {
                     QSqlQuery query;

                     if(!query.exec(sql))
                     {
                        qDebug()<<sql+query.lastError().text();
                        return false;
                     }
                     sql.clear();
                     concat=false;
                    }
                 }
            }

            k++;
        }while(!line.isNull() && k<posEnd);

     file.close();

    }else
 {
        qDebug()<<"LoadTable Couldn't open "+fileBlock;
        QString msg= "Le fichier "+QDir::currentPath()+fileBlock+"est introuvable";

        QMessageBox::critical(0,"Fichier introuvable",
            msg, QMessageBox::Ok);

       return false;
    }


QSqlQuery q("UPDATE livre SET loaded"+type+"='y' WHERE "+table+"='"+tableName+"';");


if(q.lastError().isValid())
{
    qDebug()<<"UPDATE livre SET loaded"+type+"='y' WHERE "+table+"='"+tableName+"';"+q.lastError().text();
    return false;
}


return true;

}


void Loader::initBlocDico()
{
    QString pm="/text/MG/mg";
    QString end=".txt";
    QString pf="/text/FR/fr";
    QString pe="/text/EN/en";
    for(int i=1;i<9;i++)
    {
        _myBlocsMg.append(QPair<int, QString>(i,pm+QString::number(i)+end));
        _myBlocsFr.append(QPair<int, QString>(i,pf+QString::number(i)+end));
        _myBlocsEn.append(QPair<int, QString>(i,pe+QString::number(i)+end));
    }
}


