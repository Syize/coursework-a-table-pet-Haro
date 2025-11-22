#include "systemtray.h"
#include "resources.h"

#include <QString>
#include <QApplication>


SystemTray::SystemTray(QApplication *parent)
{
    this->parent = parent;
    // init icon
    this->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Icon))));
    this->setToolTip(tr("Hello, I'm Haro."));

    // init action
    this->Quit = new QAction(tr("Quit"));
    
    // bind slot
    QObject::connect(this->Quit, &QAction::triggered, parent, &QApplication::quit);

    // init menu
    this->menu = new QMenu();
    this->menu->addAction(this->Quit);
    this->setContextMenu(this->menu);

    this->show();

    // test message
    QIcon icon(QString("/tmp/Haro/Haro.png"));
    this->showMessage(QString("Haro"), QString("Hello, Haro!"), icon);
}

void SystemTray::exitSlots()
{
    this->parent->exit();
}