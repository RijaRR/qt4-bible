/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Mon 19. Mar 10:43:14 2018
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCopier;
    QAction *actionColler;
    QAction *actionS_lectionner_tout;
    QAction *actionCouper;
    QAction *actionQuitter;
    QAction *actionMalgache;
    QAction *actionFrancais;
    QAction *actionAnglais;
    QAction *stripNumberAction;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuEdition;
    QMenu *menuPr_f_rences;
    QMenu *menuLangue_par_d_faut;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        actionCopier = new QAction(MainWindow);
        actionCopier->setObjectName(QString::fromUtf8("actionCopier"));
        actionColler = new QAction(MainWindow);
        actionColler->setObjectName(QString::fromUtf8("actionColler"));
        actionS_lectionner_tout = new QAction(MainWindow);
        actionS_lectionner_tout->setObjectName(QString::fromUtf8("actionS_lectionner_tout"));
        actionCouper = new QAction(MainWindow);
        actionCouper->setObjectName(QString::fromUtf8("actionCouper"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionMalgache = new QAction(MainWindow);
        actionMalgache->setObjectName(QString::fromUtf8("actionMalgache"));
        actionMalgache->setCheckable(true);
        actionMalgache->setChecked(true);
        actionFrancais = new QAction(MainWindow);
        actionFrancais->setObjectName(QString::fromUtf8("actionFrancais"));
        actionFrancais->setCheckable(true);
        actionAnglais = new QAction(MainWindow);
        actionAnglais->setObjectName(QString::fromUtf8("actionAnglais"));
        actionAnglais->setCheckable(true);
        stripNumberAction = new QAction(MainWindow);
        stripNumberAction->setObjectName(QString::fromUtf8("stripNumberAction"));
        stripNumberAction->setCheckable(true);
        stripNumberAction->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuPr_f_rences = new QMenu(menuBar);
        menuPr_f_rences->setObjectName(QString::fromUtf8("menuPr_f_rences"));
        menuLangue_par_d_faut = new QMenu(menuPr_f_rences);
        menuLangue_par_d_faut->setObjectName(QString::fromUtf8("menuLangue_par_d_faut"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuPr_f_rences->menuAction());
        menuEdition->addAction(actionCouper);
        menuEdition->addAction(actionQuitter);
        menuPr_f_rences->addAction(menuLangue_par_d_faut->menuAction());
        menuPr_f_rences->addAction(stripNumberAction);
        menuLangue_par_d_faut->addAction(actionMalgache);
        menuLangue_par_d_faut->addAction(actionFrancais);
        menuLangue_par_d_faut->addAction(actionAnglais);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Baiboly 1.0", 0, QApplication::UnicodeUTF8));
        actionCopier->setText(QApplication::translate("MainWindow", "Copier", 0, QApplication::UnicodeUTF8));
        actionColler->setText(QApplication::translate("MainWindow", "Coller", 0, QApplication::UnicodeUTF8));
        actionS_lectionner_tout->setText(QApplication::translate("MainWindow", "S\303\251lectionner tout", 0, QApplication::UnicodeUTF8));
        actionCouper->setText(QApplication::translate("MainWindow", "Imprimer", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionMalgache->setText(QApplication::translate("MainWindow", "Malgache", 0, QApplication::UnicodeUTF8));
        actionFrancais->setText(QApplication::translate("MainWindow", "Fran\303\247ais", 0, QApplication::UnicodeUTF8));
        actionAnglais->setText(QApplication::translate("MainWindow", "Anglais", 0, QApplication::UnicodeUTF8));
        stripNumberAction->setText(QApplication::translate("MainWindow", "Afficher les num\303\251rotations", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edition", 0, QApplication::UnicodeUTF8));
        menuPr_f_rences->setTitle(QApplication::translate("MainWindow", "Pr\303\251f\303\251rences", 0, QApplication::UnicodeUTF8));
        menuLangue_par_d_faut->setTitle(QApplication::translate("MainWindow", "Langue par d\303\251faut", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
