#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QListView>
#include <QStandardItemModel>
#include <qwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class WelcomeScreen;
}
QT_END_NAMESPACE

class WelcomeScreen : public QWidget
{
    Q_OBJECT

public:
    WelcomeScreen(QStandardItemModel* recentProjects, QWidget* parent = nullptr);
    ~WelcomeScreen();

private:
    Ui::WelcomeScreen* ui;
    QLabel* l_title;
    QLabel* l_subTitle;
    QLabel* l_start;
    QLabel* l_newProject;
    QLabel* l_openProject;
    QLabel* l_recentProjects;
    QLabel* l_exampleProjects;
    QTabWidget* tw_exampleProjects;
    QWidget* w_recentProjects;

    void resizeChildren();
    void resizeTopWidget();
    void resizeMiddleWidget();
    void resizeBottomWidget();
    void resizeTabPageChildren(int k);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
#endif // WELCOMESCREEN_H
