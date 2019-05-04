#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QMutex>
#include "searcherworker.h"
QT_BEGIN_NAMESPACE
class QCompleter;
class QLineEdit;
class QMenu;
class QStackedWidget;
class QLabel;
class QComboBox;
class QSlider;
class QTextEdit;
class QPushButton;
class QRadioButton;
class QFormLayout;
class QTableWidget;
QT_END_NAMESPACE

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    SearchWidget(QWidget *parent,QString l="mg");
    void setLanguage(QString s);

private slots:
    void toogleMoreOptionSearch(bool b);
    void search();


private:
    QFormLayout *formLayout;
    QLineEdit* keyWordLineEdit;
    QLineEdit* searchInLineEdit;
    QComboBox* searchInChapterCombo;
    QComboBox* searchFromCombo;
    QComboBox* searchToCombo;
    QRadioButton *moreSearchButton;
    QPushButton *searchButton;
    QLabel* resultNumberL;
    QTableWidget* tableResult;

    QString m_language;
    QList<SearcherWorker* > m_worker;
    QMutex* m_mutex;
    QStringList m_list;


    void initComponents();
    void initWorkers();
};

#endif // SEARCHWIDGET_H
