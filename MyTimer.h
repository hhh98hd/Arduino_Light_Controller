#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <stddef.h>

#define OFF 0
#define ON  1

#define MAX 6

class MyTimer
{
private:
    int hour;
    int minute;
    int mode;
public:
	/* constructor */
	MyTimer(int _hour, int _minute, int _mode);

    int getHour();

    int getMinute();

    int getMode();

    void setHour(int h);

    void setMinute(int m);

    void setMode(int mode);
};

class TimerManager
{
private:
    MyTimer* manager[MAX];
public:
    /* constructor */
    TimerManager();
    /* return pointer to a MyTimer object */
    MyTimer* getTimer(int index);
    /* add a timer to the timer mannager */
    void addTimer(int index, int hour, int minute, int mode);
    /* change data of a already exist timer */
    void changeTimer(int index, int hour, int minute, int mode);
    /* delete a timer from the list */
    void deleteTimer(int index);
};

#endif

