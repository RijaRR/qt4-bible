#include "tabwidget.h"
#include "searchwidget.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QComboBox>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>
#include <QtDebug>
#include <QtGui>




TabWidget::TabWidget(QWidget *parent,QString type)
    : QTabWidget(parent)
{

     m_tabBar = new TabBar(this);
     m_language=type;
     setTabBar(m_tabBar);

    BibleWidget* b = new BibleWidget(this,m_language);
             connect(b,SIGNAL(changeTabTitle(QString)),this,SLOT(changeTabTitle(QString)));
          int a=  this->addTab(b,QIcon(":/images/newBible.png"),"Bible");
           setCurrentIndex(a);

    connect(m_tabBar, SIGNAL(closeTab(int)), this, SLOT(closeTab(int)));
    connect(m_tabBar,SIGNAL(closeOtherTabs(int)),this,SLOT(closeOtherTabs(int)));
    connect(this,SIGNAL(setStripNumber(bool)),b,SLOT(setStripNumber(bool)));


}
 void TabWidget::closeTab(int index)
 {
     QWidget *w=this->widget(index);
     removeTab(index);
     delete w;
 }

 void TabWidget::setLanguage(QString l)
 {
    if(m_language!=l)
     {
      BibleWidget* b= qobject_cast<BibleWidget *>(this->currentWidget());
      m_language=l;
      if(b)
      {
          b->changeLanguage(l);
      }
    }
 }

 void TabWidget::changeTabTitle(QString t)
 {
    int ind = this->indexOf(qobject_cast<BibleWidget *>(sender()));
    m_tabBar->setTabText(ind,t);
 }

 void TabWidget::changeStripNumber(bool b)

 {
     qDebug()<<"change strip number " << !b;
     emit setStripNumber(!b);
 }

 void TabWidget::newTab()
 {

     if(QAction *source = qobject_cast<QAction*>(sender()))
     {
         if(source->data().toString()=="bible")
         {
             BibleWidget* b = new BibleWidget(this,m_language);
             connect(b,SIGNAL(changeTabTitle(QString)),this,SLOT(changeTabTitle(QString)));
              connect(this,SIGNAL(setStripNumber(bool)),b,SLOT(setStripNumber(bool)));
          int a=  this->addTab(b,QIcon(":/images/newBible.png"),"Bible");
           setCurrentIndex(a);
         }

         if(source->data().toString()=="chercher")
         {
             int a=this->addTab(new SearchWidget(this),QIcon(":/images/newBible.png"),"Chercher");
             setCurrentIndex(a);
         }

     }
 }

 void TabWidget::closeOtherTabs(int index)
{
    if (-1 == index)
        return;
    for (int i = count() - 1; i > index; --i)
                closeTab(i);
    for (int i = index - 1; i >= 0; --i)
                closeTab(i);

}

 void TabWidget::setTextFamily(const QString &f)
 {
     BibleWidget* b= qobject_cast<BibleWidget*>(this->currentWidget());
     if(b)
     {
         b->setTextFamily(f);
     }

 }
