#ifndef TABWIDGET_H
#define TABWIDGET_H
#include "tabbar.h"
#include "biblewidget.h"

#include <QtGui/QTabWidget>
QT_BEGIN_NAMESPACE
class QCompleter;
class QLineEdit;
class QMenu;
class QStackedWidget;
class QLabel;
class QComboBox;
class QSlider;
class QTextEdit;
QT_END_NAMESPACE

class TabWidget :public QTabWidget
{
     Q_OBJECT

public slots:
    void closeTab(int);
    void newTab();
    void closeOtherTabs(int index);
    void setTextFamily(const QString &);
    void setLanguage(QString);
    void changeTabTitle(QString);
    void changeStripNumber(bool);

private:
    TabBar *m_tabBar;
    QLabel *descriptionLabel;
    QString m_language;

signals:
    void setStripNumber(bool);


public:
    TabWidget(QWidget *parent = 0, QString type=QString("mg"));




};

#endif // TABWIDGET_H
