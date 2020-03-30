#include "MyTimer.h"
#include <Arduino.h>

/* constructor */
MyTimer::MyTimer(int _hour, int _minute, int _mode)
{
    this->hour = _hour;
    this->minute = _minute;
    this->mode = _mode;
}
/* getters */
int MyTimer::getHour()
{
    return this->hour;
}

int MyTimer::getMinute()
{
    return this->minute;
}

int MyTimer::getMode()
{
    return this->mode;
}
/* setters */
void MyTimer::setHour(int h)
{
    this->hour = h;
}

void MyTimer::setMinute(int m)
{
    this->minute = m;
}

void MyTimer::setMode(int mode)
{
    this->mode = mode;
}
/* constructor */
TimerManager::TimerManager()
{
    for(int i = 0; i < MAX; i++)
    {
        this->manager[i] = NULL;
    }
}
/* return pointer to a timer at particular index */
MyTimer* TimerManager::getTimer(int index)
{
    return this->manager[index];
}
/* add a timer to the manager array */
void TimerManager::addTimer(int index, int hour, int minute, int mode)
{
    MyTimer* newTimer = new MyTimer(hour, minute, mode);
    this->manager[index] = newTimer;
}
/* set hour, minute and mode for a timer at particular index */
void TimerManager::changeTimer(int index, int hour, int minute, int mode)
{
    this->manager[index]->setHour(hour);
    this->manager[index]->setMinute (minute);
    this->manager[index]->setMode(mode);
}
/* delete a timer at particular index */
void TimerManager::deleteTimer(int index)
{
    if(this->manager[index] != NULL)
    {
        this->manager[index] = NULL; 
    }
}
