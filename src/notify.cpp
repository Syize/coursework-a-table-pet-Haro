#include "notify.h"
#include "resources.h"

#include <QStringList>

Notify::Notify()
{
    this->icon = new QFile("/tmp/Haro/Haro.png");
    this->notifyProcess = new QProcess;
    this->notifyProcess->closeReadChannel(QProcess::StandardOutput);
    this->notifyProcess->closeReadChannel(QProcess::StandardError);
    this->extractIcon();
}

void Notify::extractIcon()
{
    #ifdef __linux__
        if (!this->icon->exists())
        {
            QFile QrcHaroIcon(HaroIcon::getIcon(HaroIcon::IconPNG));
            QrcHaroIcon.copy(QString("/tmp/Haro/Haro.png"));
        }
    #endif
}

void Notify::sendNotificationSlot(QString text)
{
    // stop running process
    if (this->notifyProcess->state() == 2)
    {
        this->notifyProcess->kill();
    }
    
    this->notifyProcess->setProgram(QString("notify-send"));
    // arguments
    QStringList arguments = {"-u", "normal", "-a", "Haro", "-i", "/tmp/Haro/Haro.png"};
    arguments << text;
    this->notifyProcess->setArguments(arguments);
    this->notifyProcess->start();
}