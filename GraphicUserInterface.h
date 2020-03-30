#ifndef GRAPHIC_USER_INTERFACE_H
#define GRAPHIC_USER_INTERFACE_H

#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include "MyTimer.h"

#define WELCOME 0
#define MENU    1

void welcomeScreen(LiquidCrystal_I2C lcd);

void menuScreen(LiquidCrystal_I2C lcd, int selection);

void timerListScreen(LiquidCrystal_I2C lcd, TimerManager* timerManager, int selection);

void setTimerScreen(LiquidCrystal_I2C lcd, TimerManager* timerManager, int h, int m, int mode, bool enableTimer, int selection);

void setRtcScreen(LiquidCrystal_I2C lcd, virtuabotixRTC rtc, int h, int m, int dow, int d, int month, int y, int selection);

#endif
