#include <QResizeEvent>
#include <QListView>
#include <QStandardItemModel>
#include <QDebug>
#include <algorithm>
#include <format>
#include <qboxlayout.h>
#include <qchar.h>
#include <qdebug.h>
#include <qglobal.h>
#include <qobject.h>
#include <qtabwidget.h>
#include <qwidget.h>

#include "welcomescreen.h"
#include "projectpreview.h"
#include "./ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QStandardItemModel* recentProjects, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeScreen) {
    ui->setupUi(this);
    
    l_title = new QLabel("LabPlot", ui->top);
    // l_title->setStyleSheet("background-color: yellow");
    QFont titleFont(l_title->font());
    titleFont.setPointSize(24);
    l_title->setFont(titleFont);

    l_subTitle = new QLabel("Data Visualization and Analysis", ui->top);
    // l_subTitle->setStyleSheet("background-color: blue");
    QFont subTitleFont(l_subTitle->font());
    subTitleFont.setPointSize(16);
    l_subTitle->setFont(subTitleFont);

    l_start = new QLabel("Start", ui->middle);
    // l_start->setStyleSheet("background-color: red");
    QFont startFont(l_start->font());
    startFont.setPointSize(14);
    startFont.setBold(true);
    l_start->setFont(startFont);

    l_recentProjects = new QLabel("Recent Projects", ui->middle);
    // l_recentProjects->setStyleSheet("background-color: yellow");
    QFont recentProjectsFont(l_recentProjects->font());
    recentProjectsFont.setPointSize(14);
    recentProjectsFont.setBold(true);
    l_recentProjects->setFont(recentProjectsFont);

    l_exampleProjects = new QLabel("Example Projects", ui->bottom);
    // l_exampleProjects->setStyleSheet("background-color: red");
    QFont exampleProjectsFont(l_exampleProjects->font());
    exampleProjectsFont.setPointSize(14);
    exampleProjectsFont.setBold(true);
    l_exampleProjects->setFont(exampleProjectsFont);

    l_newProject = new QLabel("New Project...", ui->middle);
    // l_newProject->setStyleSheet("background-color: yellow");
    QFont newProjectFont(l_newProject->font());
    newProjectFont.setPointSize(12);
    l_newProject->setFont(newProjectFont);

    l_openProject = new QLabel("Open Project...", ui->middle);
    // l_openProject->setStyleSheet("background-color: yellow");
    QFont openProjectFont(l_openProject->font());
    openProjectFont.setPointSize(12);
    l_openProject->setFont(openProjectFont);

    tw_exampleProjects = new QTabWidget(ui->bottom);
    // tw_exampleProjects->setDocumentMode(true);
    // tw_exampleProjects->tabBar()->setDocumentMode(true);
    // tw_exampleProjects->tabBar()->setDrawBase(false);
    // tw_exampleProjects->setStyleSheet("QTabWidget::pane {margin: 0px;}");
    // tw_exampleProjects->setStyleSheet("background-color: blue");

    w_recentProjects = new QWidget(ui->middle);
    // w_recentProjects->setStyleSheet("background-color: yellow");

    for (int i = 0; i < 5; i++) {
        auto* item = new QWidget(w_recentProjects);
        item->setStyleSheet("background-color: black");
    }

    for (int i = 0; i < 5; i++) {
        auto* tab = new QWidget(tw_exampleProjects);
        // tab->setStyleSheet("background-color: red");
        for (int i = 0; i < 5; i++) {
            auto* item = new QWidget(tab);
            item->setStyleSheet("background-color: black");
        }

        tw_exampleProjects->addTab(tab, QString::number(i));
    }

    connect(tw_exampleProjects, &QTabWidget::currentChanged, this, &WelcomeScreen::resizeTabPageChildren);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::resizeEvent(QResizeEvent* event) {
    resizeChildren();
}

void WelcomeScreen::resizeChildren() {
    resizeTopWidget();
    resizeMiddleWidget();
    resizeBottomWidget();
}

void WelcomeScreen::resizeTopWidget() {
    l_title->move(0, ui->top->height() / 6);
    l_subTitle->move(0, l_title->pos().y() + l_title->fontMetrics().height() + ui->top->height() / 20);
}

void WelcomeScreen::resizeMiddleWidget() {
    l_start->move(0, ui->middle->height() / 20);
    l_newProject->move(0, l_start->pos().y() + l_start->fontMetrics().height() + ui->middle->height() / 5);
    l_openProject->move(0, l_newProject->pos().y() + l_newProject->fontMetrics().height() + ui->middle->height() / 12);
    
    int indent = l_openProject->fontMetrics().horizontalAdvance(l_openProject->text()) + ui->middle->width() / 4;
    l_recentProjects->move(indent, ui->middle->height() / 20);
    w_recentProjects->move(indent, l_recentProjects->pos().y() + l_recentProjects->fontMetrics().height() + ui->middle->height() / 15);
    w_recentProjects->setFixedHeight(ui->middle->height() * 3 / 5);
    w_recentProjects->setFixedWidth(std::max(ui->middle->width() - indent, 0));

    int i = 0;
    int previewWidth = std::max(static_cast<int>(w_recentProjects->height() * 1.5), static_cast<int>(ui->middle->width() / 4));
    int previewSpacing = ui->middle->width() / 20;
    for (auto& child : w_recentProjects->children()) {
        auto* w_Child = static_cast<QWidget*>(child);
        w_Child->setFixedHeight(w_recentProjects->height());
        w_Child->setFixedWidth(previewWidth);
        w_Child->move((previewWidth + previewSpacing) * i, 0);
        i++;
    }
}

void WelcomeScreen::resizeBottomWidget() {
    l_exampleProjects->move(0, ui->bottom->height() / 25);
    tw_exampleProjects->move(0, l_exampleProjects->pos().y() + l_exampleProjects->fontMetrics().height() + ui->bottom->height() / 15);
    tw_exampleProjects->setFixedHeight(ui->bottom->height() * 3 / 5 + tw_exampleProjects->tabBar()->height() + tw_exampleProjects->style()->pixelMetric(QStyle::QStyle::PM_TabBarBaseHeight));
    tw_exampleProjects->setFixedWidth(ui->bottom->width());

    resizeTabPageChildren(tw_exampleProjects->currentIndex());
}

void WelcomeScreen::resizeTabPageChildren(int k) {
    if (k == -1)
        return;

    int pageAreaHeight = ui->bottom->height() * 3 / 5 + tw_exampleProjects->style()->pixelMetric(QStyle::QStyle::PM_TabBarBaseHeight);
    int previewWidth = std::max(static_cast<int>(pageAreaHeight * 1.5), static_cast<int>(ui->bottom->width() / 4));
    int previewSpacing = ui->bottom->width() / 20;

    int i = 0;
    for (auto& child : tw_exampleProjects->widget(k)->children()) {
        auto* w_Child = static_cast<QWidget*>(child);
        w_Child->setFixedHeight(pageAreaHeight);
        w_Child->setFixedWidth(previewWidth);
        w_Child->move((previewWidth + previewSpacing) * i, 0);
        i++;
    }
}
