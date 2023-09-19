#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>

#include "resources.h"

// init system tray and its menu
class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    SystemTray(QApplication *parent = nullptr);

public slots:
    void exitSlots();

private:
    QMenu* menu;
    QAction* Quit;
    QApplication* parent;
};

#endif