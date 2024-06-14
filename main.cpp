#include "welcomescreen.h"

#include <QApplication>
#include <QStandardItemModel>
#include <qstandarditemmodel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto* items = new QStandardItemModel();
    
    QStringList b{"i", "j", "k", "l", "m"};
    
    for (auto& i : {"i", "j", "k", "l", "m"}) {
        items->appendRow(new QStandardItem(i));        
    }

    WelcomeScreen w(items);
    w.show();
    return a.exec();
}
