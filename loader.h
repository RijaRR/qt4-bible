#ifndef LOADER_H
#define LOADER_H
#include <QtGui/QApplication>
#include <QStringList>
#include <QObject>
#include <QPair>
#include <QList>
#include <QComboBox>

class Loader
{
public:
    Loader();
    bool loadTable(QString tableName,QString type);
    QString loadReference(QString tableName,int chapter,int verseBegin,int verseEnd,QString type,bool stripNumber=false);
    static QString* keyResolver(QString language);
    static QString bookName(QString tableName);
    static QString translateTableName(QString src,QString languageSrc, QString languageDst);

    static void initComboBook(QString m_tableName,QString m_language,QComboBox* bookCombo);
    static void setMaxChapitre(int indexCombo,QComboBox* bookCombo,QComboBox* chapterCombo,QString m_tableName,
                            QString m_maxChap);
    static void setMaxVersetFrom(int k,QString m_maxChap,QString m_tableName,QComboBox* bookCombo,
                              QComboBox* versetBeginCombo,QComboBox* versetEndCombo,QComboBox* chapterCombo);
    static void setMaxVersetTo(int k,QComboBox* versetEndCombo,QComboBox* versetBeginCombo);
    QList< QPair<int, QString> > getBloc(QString language);

private:
    QList< QPair<int, QString> > _myBlocsMg;
    QList< QPair<int, QString> > _myBlocsFr;
    QList< QPair<int, QString> > _myBlocsEn;

    void initBlocDico();

};

#endif // LOADER_H
