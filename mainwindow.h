#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include "tabwidget.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void setLanguage();

signals:
    void languageChanged(QString);

private:
    Ui::MainWindow *ui;

    QToolBar *navigationToolBar;
    QAction *openBibleAction;
    QAction *quantiqueAction;
    QAction *searchAction;
    QAction *translateAction;

    QToolBar *textToolBar;
    QFontComboBox *fontCombo;

    TabWidget *m_tabWidget;

    void createAction();
    void createToolbars();






};

#endif // MAINWINDOW_H
