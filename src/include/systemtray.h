#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>

#include "resources.h"

// init system tray and its menu
class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    SystemTray(QObject *parent = nullptr);

private:
    QMenu* menu;
    QAction* Quit;
};

#endif