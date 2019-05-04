#include "searchwidget.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QStringList>
#include <QTableWidgetItem>
#include <QThread>
#include "loader.h"


SearchWidget::SearchWidget(QWidget *parent,QString l)
{
     m_language=l;
    initComponents();
    m_mutex= new QMutex();
    initWorkers();

}

void SearchWidget::search()
{
   QString key= keyWordLineEdit->text();
   key.data();

   if(key.length()==0 || key.length()>90)
       return;

   int l= key.length();
   char* c = 0;
   c= new char[l];
   for(int i=0; i<l;i++)
   {
       c[i]=key.at(i).toLatin1();
   }
   for(int i=0; i<m_worker.size();i++)
   {
       SearcherWorker* w= m_worker.at(i);
       w->setKeyWord(c);

   }




}


void SearchWidget::initWorkers()
{
    int ideal = QThread::idealThreadCount();

    if(ideal==-1)
        ideal=2;

    Loader l;
    QList< QPair<int, QString> > list= l.getBloc(m_language);
    for(int i=0; i<list.size();i++)
    {
        m_list.append(list.at(i).second);
    }

    for(int i=0; i<ideal;i++)
    {
       SearcherWorker* w = new SearcherWorker(m_list,m_mutex,tableResult);
       m_worker.append(w);
    }   

}

void SearchWidget::setLanguage(QString s)
{
    if(m_language!=s)
    {
      m_language= s;

      m_mutex->lock();
       Loader l;
       m_list.clear();

    QList< QPair<int, QString> > list= l.getBloc(m_language);
    for(int i=0; i<list.size();i++)
    {
        m_list.append(list.at(i).second);
    }

    for(int i=0; i<m_worker.size();i++)
    {
        m_worker.at(i)->setList(m_list);
    }
    m_mutex->unlock();

    }
}

void SearchWidget::initComponents()
{
      QVBoxLayout *mainLayout = new QVBoxLayout;
      formLayout = new QFormLayout;
      //QHBoxLayout *h1 = new QHBoxLayout;
    
      keyWordLineEdit= new QLineEdit(this);
      formLayout->addRow("Mot(s)", keyWordLineEdit);

      moreSearchButton = new QRadioButton("Affiner la recherche",this);
      formLayout->addWidget(moreSearchButton);

      searchInLineEdit= new QLineEdit(this);
      searchInLineEdit->setMaximumWidth(150);
      formLayout->addRow("Chercher dans:",searchInLineEdit);

      searchInChapterCombo= new QComboBox(this);
      searchInChapterCombo->setMaximumWidth(150);
      formLayout->addRow("Chapitre ",searchInChapterCombo);

      searchFromCombo= new QComboBox(this);
      searchFromCombo->setMaximumWidth(150);
      formLayout->addRow("Verset",searchFromCombo);

      searchToCombo= new QComboBox(this);
      searchToCombo->setMaximumWidth(150);
      formLayout->addRow("à",searchToCombo);


       searchButton = new QPushButton("rechercher",this);
       searchButton->setMaximumWidth(80);
       //h1->addWidget(searchButton, Qt::AlignLeft);




       resultNumberL = new QLabel(this);
       resultNumberL->setText("Nombre d'occurence trouvé ");

       tableResult = new QTableWidget(this);
       tableResult->setColumnCount(2);
       tableResult->setRowCount(0);


      // QTableWidgetItem *textFound = new QTableWidgetItem("test sur ligne 0 colonne 0"); OK
      // tableResult->setItem(0,0,textFound);


       QStringList list;
       list<<"Référence"<<"Texte";
       tableResult->setHorizontalHeaderLabels(list);

       mainLayout->addLayout(formLayout);
       mainLayout->addWidget(searchButton);
       mainLayout->addWidget(resultNumberL);
       mainLayout->addWidget(tableResult);
       mainLayout->addSpacing(45);
       mainLayout->insertStretch(-1,300);

       searchFromCombo->hide();

       formLayout->labelForField(searchFromCombo)->hide();

       this->setLayout(mainLayout);
       toogleMoreOptionSearch(false);
       connect(moreSearchButton, SIGNAL(toggled(bool)), this, SLOT(toogleMoreOptionSearch(bool)));

}

void SearchWidget::toogleMoreOptionSearch(bool b)
{
    searchFromCombo->setVisible(b);
    formLayout->labelForField(searchFromCombo)->setVisible(b);
    searchInChapterCombo->setVisible(b);
    formLayout->labelForField(searchInChapterCombo)->setVisible(b);
    searchToCombo->setVisible(b);
    formLayout->labelForField(searchToCombo)->setVisible(b);
    searchInLineEdit->setVisible(b);
     formLayout->labelForField(searchInLineEdit)->setVisible(b);

}


