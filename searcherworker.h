#ifndef SEARCHERWORKER_H
#define SEARCHERWORKER_H
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTableWidget>
#include "searcherworker.h"

class SearcherWorker : public QThread
{
public:
    SearcherWorker(QStringList &list,QMutex* mutex,QTableWidget* table);
    ~SearcherWorker();
    void run();
    void setKeyWord(char* s);
    void setList(QStringList &l);


private:
    QStringList m_list;
    QMutex* m_mutex;
    QTableWidget* m_tableResult;
    int m_maxResult;
    char* m_keyWord;
    void search(QString fileName);
    bool m_abort;




};

#endif // SEARCHERWORKER_H
