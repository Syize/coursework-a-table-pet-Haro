#ifndef TIMER_H
#define TIMER_H

#include <QThread>

// QThread subclass, send signal every 10s to tell system tray change icon
class Timer: public QThread
{
    Q_OBJECT

public:
    void run() override;
    void setSleepTime(int seconds);

signals:
    void atTime();

private:
    int seconds = 0;
};

#endif