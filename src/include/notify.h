#ifndef NOTIFY_H
#define NOTIFY_H

#include <QProcess>
#include <QFile>
#include <QString>

class Notify : public QObject
{
    Q_OBJECT

private:
    // icon file pointer
    QFile* icon;
    // use QProcess to send ntification with "notify-send" on linux
    QProcess* notifyProcess;
    // extract icon to /tmp/Haro on linux
    void extractIcon();

public:
    // constuctor
    Notify();

public slots:
    void sendNotificationSlot(QString);
};

#endif