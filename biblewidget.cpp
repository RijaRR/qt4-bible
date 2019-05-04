#include "biblewidget.h"
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QComboBox>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>
#include <QtGui/QPushButton>
#include <QtDebug>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>
#include <QtDebug>
#include <QFile>
#include <QVariant>

#include "loader.h"
#include "loaderworker.h"

BibleWidget::BibleWidget(QWidget *parent,QString l)
{
    Q_UNUSED(parent);

    m_stripNumber= false;
    m_lastReference= new QString[4];
    m_language=l;
    initKeys();
    initComponents();

    m_lastZoomValue=0;

    initLastReference();

    m_worker = new LoaderWorker();


}

BibleWidget::~BibleWidget()
{
    delete m_lastReference;
    delete m_worker;
}

/*
    m_lastReference[0]=tableName;
    m_lastReference[1]=QString::number(chapter);
    m_lastReference[2]= QString::number(verseBegin);
    m_lastReference[3]= QString::number(verseEnd);
  */

void BibleWidget::changeLanguage(QString language)
{
    QString prevLanguage= m_language;
    m_language=language;
    initKeys();
    Loader::initComboBook(m_tableName,m_language,bookCombo);
    if(m_lastReference)
    {

    QString newBookName = Loader::translateTableName(m_lastReference[0],prevLanguage,m_language);

    bookCombo->setCurrentIndex(bookCombo->findData(QVariant(newBookName)));
    Loader l;
    launchButton->setEnabled(false);
    QString reference= l.loadReference(newBookName,m_lastReference[1].toInt()
                                       ,m_lastReference[2].toInt(),m_lastReference[3].toInt()
                                       ,m_language,m_stripNumber);
    textEdit->setText(reference);

    launchButton->setEnabled(true);

    chapterCombo->setCurrentIndex(chapterCombo->findData(QVariant(m_lastReference[1].toInt())));

    versetBeginCombo->setCurrentIndex(m_lastReference[2].toInt()-1);
    versetEndCombo->setCurrentIndex(m_lastReference[3].toInt()-m_lastReference[2].toInt());

    m_lastReference[0]=newBookName;
    emit changeTabTitle(Loader::bookName(newBookName)+" "+m_lastReference[1]+":"+m_lastReference[2]+"-"+m_lastReference[3]);


    }



}

void BibleWidget::initKeys()
{
    QString* s= Loader::keyResolver(m_language);
    m_tableName=s[0];
    m_maxChap=s[1];
    m_posBegin=s[2];
    m_posEnd=s[3];
    m_bloc=s[4];
}



void BibleWidget::initComponents()
{
       QVBoxLayout *mainLayout = new QVBoxLayout;
       QHBoxLayout *h1 = new QHBoxLayout;
       QHBoxLayout *h2 = new QHBoxLayout;
       QHBoxLayout *h3 = new QHBoxLayout;

       h1->setAlignment(Qt::AlignLeft);
       h3->setAlignment(Qt::AlignRight);

     bookL = new QLabel(this);
     bookL->setText("Livre");
     bookCombo = new QComboBox(this);
     Loader::initComboBook(m_tableName,m_language,bookCombo);

     h1->addWidget(bookL);
     h1->addWidget(bookL);
     h1->addWidget(bookCombo);

    chapterL=new QLabel(this);
    chapterL->setText("Chapitre");
    chapterCombo = new QComboBox(this);
    chapterCombo->setMinimumWidth(45);
    h1->addWidget(chapterL);
    h1->addWidget(chapterCombo);
    Loader::setMaxChapitre(0,bookCombo,chapterCombo,m_tableName,m_maxChap);

    versetBL=new QLabel(this);
    versetBL->setText("Verset de ");
    versetBeginCombo = new QComboBox(this);
    h1->addWidget(versetBL);
    h1->addWidget(versetBeginCombo);

    versetEL=new QLabel(this);
    versetEL->setText("à");
    versetEndCombo = new QComboBox(this);
    h1->addWidget(versetEL);
    h1->addWidget(versetEndCombo);
    Loader::setMaxVersetFrom(0,m_maxChap,m_tableName,bookCombo,versetBeginCombo,versetEndCombo,chapterCombo);
    Loader::setMaxVersetTo(0,versetEndCombo,versetBeginCombo);

    launchButton = new QPushButton(this);
    launchButton->setText("ok");
    h1->addWidget(launchButton);

    //2
    textEdit= new QTextEdit(this);
    h2->addWidget(textEdit);
    textEdit->document()->setDefaultFont(QFont("MS Reference Sans Serif"));

    //3
    zoomL =new QLabel(this);
    zoomL->setText("Zoom");
    zoomSlider =  new QSlider(this);
    zoomSlider->setValue(0);
    zoomSlider->setOrientation(Qt::Horizontal);
    zoomSlider->setMaximumWidth(75);
    zoomShowL=new QLabel(this);
    zoomShowL->setText("0%");
    showAllChapterButton = new QPushButton(this);
    showAllChapterButton->setText("Tout ouvrir");


    h3->addWidget(zoomL);
    h3->addWidget(zoomSlider);
    h3->addWidget(zoomShowL);
    h3->addWidget(showAllChapterButton);
    h3->insertStretch(0,300);

    mainLayout->addLayout(h1);
    mainLayout->addLayout(h2);
    mainLayout->addLayout(h3);

    this->setLayout(mainLayout);

    connect(zoomSlider,SIGNAL(valueChanged(int)),this,SLOT(setZoom(int)));

    connect(bookCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(setMaxChapitre(int)));
    connect(chapterCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(setMaxVersetFrom(int)));
    connect(versetBeginCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(setMaxVersetTo(int)));
    connect(launchButton,SIGNAL(clicked()),this,SLOT(fetchReference()));

}


void BibleWidget::initLastReference()
{
    QString tableName = bookCombo->itemData(bookCombo->currentIndex()).toString();
    int chapter = chapterCombo->itemData(chapterCombo->currentIndex()).toInt();
    int verseBegin = versetBeginCombo->itemData(versetBeginCombo->currentIndex()).toString().split(",").at(0).toInt();
    int verseEnd = versetEndCombo->itemData(versetEndCombo->currentIndex()).toInt();

    m_lastReference[0]=tableName;
    m_lastReference[1]=QString::number(chapter);
    m_lastReference[2]= QString::number(verseBegin);
    m_lastReference[3]= QString::number(verseEnd);

}

void BibleWidget::fetchReference()
{
    launchButton->setEnabled(false);
    Loader l;
    QString tableName = bookCombo->itemData(bookCombo->currentIndex()).toString();
    int chapter = chapterCombo->itemData(chapterCombo->currentIndex()).toInt();
    int verseBegin = versetBeginCombo->itemData(versetBeginCombo->currentIndex()).toString().split(",").at(0).toInt();
    int verseEnd = versetEndCombo->itemData(versetEndCombo->currentIndex()).toInt();

    QString reference= l.loadReference(tableName,chapter,verseBegin,verseEnd,m_language,m_stripNumber);

    textEdit->setText(reference);

    launchButton->setEnabled(true);

    m_lastReference[0]=tableName;
    m_lastReference[1]=QString::number(chapter);
    m_lastReference[2]= QString::number(verseBegin);
    m_lastReference[3]= QString::number(verseEnd);
    emit changeTabTitle(Loader::bookName(tableName)+" "+m_lastReference[1]+":"+m_lastReference[2]+"-"+m_lastReference[3]);
    QString sqlDropLater = "DROP TABLE "+tableName+";";
    QString updateFlag ="UPDATE livre SET loaded"+m_language.toLower()+"='n' WHERE "+m_tableName+"='"+tableName+"';";

    m_worker->addSqlOrder(sqlDropLater,16);
    m_worker->addSqlOrder(updateFlag,18);
}




void BibleWidget::setMaxVersetTo(int k)
{
    Loader::setMaxVersetTo(k,versetEndCombo,versetBeginCombo);
}

void BibleWidget::setStripNumber(bool b)
{
    if(b!=m_stripNumber)
    {
      m_stripNumber=b;
      fetchReference();
    }

}







void BibleWidget::setMaxVersetFrom(int k)
{
    Loader::setMaxVersetFrom(k,m_maxChap,m_tableName,bookCombo,versetBeginCombo,versetEndCombo,chapterCombo);
}


void BibleWidget::setMaxChapitre(int indexCombo)
{
Loader::setMaxChapitre(indexCombo,bookCombo,chapterCombo,m_tableName,m_maxChap);
}





void BibleWidget::setTextFamily(const QString &f)
{
    textEdit->document()->setDefaultFont(QFont(f));
}

void BibleWidget::setZoom(int z)
{
    z=z;
  if(z>m_lastZoomValue)
    {
      textEdit->zoomIn(z-m_lastZoomValue);
    }else
  {
       textEdit->zoomOut(m_lastZoomValue-z);
    }
    m_lastZoomValue= z;
    zoomShowL->setText(QString::number(z*5)+QString(" %"));
}
