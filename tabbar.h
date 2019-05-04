#ifndef TABBAR_H
#define TABBAR_H
#include <QtGui/QTabBar>

#include <QtGui/QShortcut>
/*
    Tab bar with a few more features such as a context menu and shortcuts
 */
class TabBar : public QTabBar
{
    Q_OBJECT

signals:
    void closeOtherTabs(int index);
    void closeTab(int index);
   // void tabMoveRequested(int fromIndex, int toIndex);

private slots:
    void contextMenuRequested(const QPoint &);
    void closeTab();
    void closeOtherTabs();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

public:
    TabBar(QWidget *parent = 0);
    QPoint m_dragStartPos;

};


#endif // TABBAR_H
