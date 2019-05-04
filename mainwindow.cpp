#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createAction();
    createToolbars();
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    m_tabWidget = new TabWidget(this);
    layout->addWidget(m_tabWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(openBibleAction,SIGNAL(triggered()),m_tabWidget,SLOT(newTab()));
    connect(searchAction,SIGNAL(triggered()),m_tabWidget,SLOT(newTab()));

    //LANGUAGE
    connect(ui->actionMalgache,SIGNAL(triggered()),this,SLOT(setLanguage()));
    connect(ui->actionFrancais,SIGNAL(triggered()),this,SLOT(setLanguage()));
    connect(ui->actionAnglais,SIGNAL(triggered()),this,SLOT(setLanguage()));
    connect(this,SIGNAL(languageChanged(QString)),m_tabWidget,SLOT(setLanguage(QString)));




  //text edit

    connect(fontCombo, SIGNAL(activated(const QString &)),
            m_tabWidget, SLOT(setTextFamily(const QString &)));
    connect(ui->stripNumberAction,SIGNAL(toggled(bool)),m_tabWidget,SLOT(changeStripNumber(bool)));
}


void MainWindow::setLanguage(){
    QAction* current = qobject_cast<QAction *>(sender());
    QAction* j[3]= {ui->actionAnglais,ui->actionFrancais,ui->actionMalgache};
    QString language[3]= {"en","fr","mg"};
    for(int i=0;i<3;i++)
    {
        if(j[i]!=current)
        {
                j[i]->setChecked(false);
        }else{
            j[i]->setChecked(true);
             emit languageChanged(language[i]);
        }
    }


}




MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createAction()
{

    openBibleAction = new QAction(QIcon(":/images/newBible.png"),
                                tr("Nouveau Page"), this);
    openBibleAction->setShortcut(tr("Ctrl+N"));
    openBibleAction->setStatusTip(tr("Pour ouvrir un nouveau onglet bible"));
    openBibleAction->setData(QString("bible"));

    quantiqueAction = new QAction(QIcon(":/images/quantique.png"),
                                tr("Ouvrir Quantique"), this);
    quantiqueAction->setShortcut(tr("Ctrl+E"));
    quantiqueAction->setStatusTip(tr("Quantique"));

    searchAction = new QAction(QIcon(":/images/search.png"),
                                tr("Chercher"), this);
    searchAction->setShortcut(tr("Ctrl+F"));
    searchAction->setStatusTip(tr("Outil de recherche"));
    searchAction->setData(QString("chercher"));

    translateAction = new QAction(QIcon(":/images/translate.png"),
                                tr("Traduire"), this);
    translateAction->setShortcut(tr("Ctrl+T"));
    translateAction->setStatusTip(tr("Traduire"));


}

void MainWindow::createToolbars()
{
    navigationToolBar = addToolBar(tr("Navigation"));
    navigationToolBar->addAction(openBibleAction);
    navigationToolBar->addAction(quantiqueAction);
    navigationToolBar->addAction(searchAction);
    navigationToolBar->addAction(translateAction);

    textToolBar = addToolBar(tr("Style"));
    fontCombo = new QFontComboBox();
    fontCombo->setEditable(false);

    textToolBar->addWidget(fontCombo);
}
