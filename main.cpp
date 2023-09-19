#include "haro.h"
#include "systemtray.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create system tray
    SystemTray systemTray = SystemTray(&a);

    Haro w;

    // show Haro after clicking system tray icon
    QObject::connect(&systemTray, &QSystemTrayIcon::activated, &w, &Haro::onSystemTrayIconActivate);
    QObject::connect(&w, &Haro::exitSignal, &systemTray, &SystemTray::exitSlots);

    w.show();

    return a.exec();
}
