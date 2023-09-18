#include "systemtray.h"
#include "resources.h"

#include <QString>


SystemTray::SystemTray(QObject *parent)
{
    // init icon
    this->setIcon(QIcon(QString(HaroIcon::getIcon(HaroIcon::Icon))));
    this->setToolTip("Hello, I'm Haro.");
    this->show();
}