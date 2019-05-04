#ifndef BIBLEWIDGET_H
#define BIBLEWIDGET_H

#include <QWidget>
#include <QtGui/QTabWidget>
#include "loaderworker.h"

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
QT_END_NAMESPACE


        //VERSION 3
class BibleWidget : public QWidget
{
     Q_OBJECT

public:
    BibleWidget(QWidget *parent,QString l);
    BibleWidget::~BibleWidget();

    void setTextFamily(const QString &f);
    void changeLanguage(QString language);


public slots:
    void setZoom(int);

signals:
    void changeTabTitle(QString);

private slots:
    void setMaxChapitre(int);
    void setMaxVersetFrom(int);
    void setMaxVersetTo(int);
    void fetchReference();
    void setStripNumber(bool);

private:
    QString m_language;
    QString m_tableName;
    QString m_maxChap;
    QString m_posBegin;
    QString m_posEnd;
    QString m_bloc;
    QString* m_lastReference;




    //UI
    QLabel* bookL;
    QComboBox* bookCombo;
    QLabel* chapterL;
    QComboBox* chapterCombo;
    QLabel* versetBL;
    QComboBox* versetBeginCombo;
    QLabel* versetEL;
    QComboBox* versetEndCombo;
    QPushButton* launchButton;


    //2
    QTextEdit* textEdit;
    //3
    QLabel* zoomL;
    QSlider* zoomSlider;
    QLabel* zoomShowL;
    QPushButton* showAllChapterButton;

    //thread
    LoaderWorker *m_worker;

    int m_lastZoomValue;
    bool m_stripNumber;

    void initComponents();
    void initKeys();
    void initLastReference();
};

#endif // BIBLEWIDGET_H
