#include "timer.h"
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void Timer::run()
{
    if (this->seconds == 0)
        this->exit();
    else
    {
        while (1)
        {
            sleep(this->seconds);
            emit atTime();
        }
    }
}

void Timer::setSleepTime(int second)
{
    this->seconds = second;
}