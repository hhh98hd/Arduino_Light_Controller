#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include "MyTimer.h"
#include "GraphicUserInterface.h"
#include "BigNumbers.h"

#define NORMAL         0
#define SET_RTC        1
#define TIMER_LIST     2
#define MENU           3
#define SET_TIMER      4

#define OK_BUTTON      4
#define MENU_BUTTON    3
#define UP_BUTTON      6
#define DOWN_BUTTON    5

#define LIGHT_SWITCH   2
#define LIGHT          10
#define RELAY          0

virtuabotixRTC myRTC(9, 7, 8);
LiquidCrystal_I2C lcd(0x27, 20, 4);
TimerManager* manager = new TimerManager();
BigNumbers bigNum(&lcd);

int currentMode;
int selectMode;
int setHour = -1, setMin = -1, setMode, setDow, setDay, setMonth, setYear;
int timerIndex;
bool lightStatus = false;
bool enableTimer = true;
long long lastCheck = 0;
long long lastOkBtn = 0, lastMenuBtn = 0, lastUpBtn = 0, lastDownBtn = 0;

void lightSwitchPresed();

void checkTimers();

void displayTime();

void setup() 
{
        pinMode(OK_BUTTON, INPUT_PULLUP);
        pinMode(MENU_BUTTON, INPUT_PULLUP);
        pinMode(UP_BUTTON, INPUT_PULLUP);
        pinMode(DOWN_BUTTON, INPUT_PULLUP);
        
        pinMode(LIGHT, OUTPUT);
        pinMode(LIGHT_SWITCH, INPUT);
        pinMode(RELAY, OUTPUT);
        
        attachInterrupt(digitalPinToInterrupt(LIGHT_SWITCH), lightSwitchPresed, RISING);
        
        currentMode = NORMAL;
        selectMode = 1;
//        myRTC.setDS1302Time(10, 18, 13, 1, 6, 10, 2019);
           /*
            * Son = 1
            * Mon = 2
            * Tue = 3
            * Wed = 4
            * Thu = 5
            * Fri = 6
            * Sat = 7
            */
        lcd.backlight();
        lcd.begin();
        welcomeScreen(lcd);
        delay(1500);
        lcd.clear();
        bigNum.begin();
}

void loop() 
{  
     myRTC.updateTime();
      
    if(millis() - lastCheck >= 600)
    {
        checkTimers();
        lastCheck = millis();
    }
    
    if(currentMode == MENU)
    {
        if(digitalRead(UP_BUTTON) == LOW && millis() - lastUpBtn >= 200)
        {
            lastUpBtn = millis();
            selectMode -= 1;
            if(selectMode < 1)
            {
                selectMode = SET_RTC;
            }
        }
        else if(digitalRead(DOWN_BUTTON) == LOW && millis() - lastDownBtn >= 200)
        {
            lastDownBtn = millis();
            selectMode += 1;
            if(selectMode > 2)
            {   
                selectMode = SET_RTC;
            }
        }
        else if(digitalRead(MENU_BUTTON) == LOW  && millis() - lastMenuBtn >= 600)
        {
            lastMenuBtn = millis();
            bigNum.begin();
            lcd.clear();
            currentMode = NORMAL;
        }
        else if(digitalRead(OK_BUTTON) == LOW && millis() - lastOkBtn >= 600)
        {
            lastOkBtn = millis();
            lcd.clear();
            currentMode = selectMode;
            if(currentMode == SET_RTC)
            {
                setHour = myRTC.hours;
                setMin = myRTC.minutes;
                setDow = myRTC.dayofweek;
                setDay = myRTC.dayofmonth;
                setMonth = myRTC.month;
                setYear = myRTC.year;
            }
            selectMode = 1;
        }
    }
    else if(currentMode == NORMAL)
    {
        if(digitalRead(MENU_BUTTON) == LOW && millis() - lastMenuBtn >= 600)
        {
            lastMenuBtn = millis();
            lcd.clear();
            bigNum.begin();
            currentMode = MENU;
        }
    }
    else if(currentMode == TIMER_LIST)
    {
        if(digitalRead(UP_BUTTON) == LOW && millis() - lastUpBtn >= 200)
        {
            lastUpBtn = millis();
            selectMode -= 1;
            lcd.clear();
            if(selectMode < 1)
            {
                selectMode = 1;
            }
        }
        else if(digitalRead(DOWN_BUTTON) == LOW && millis() - lastDownBtn >= 200)
        {
            lastDownBtn = millis();
            selectMode += 1;
            lcd.clear();
            if(selectMode > 6)
            {   
                selectMode = 1;
            }
        }
        else if(digitalRead(OK_BUTTON) == LOW && millis() - lastOkBtn >= 600)
        {
            lastOkBtn = millis();
            lcd.clear();
            timerIndex = selectMode - 1;
            if(manager->getTimer(selectMode - 1) != NULL)
            {
                setHour = manager->getTimer(timerIndex)->getHour();
                setMin = manager->getTimer(timerIndex)->getMinute();
                setMode = manager->getTimer(timerIndex)->getMode();
            }
            else
            {
                setHour = 0;
                setMin = 0;
                setMode = 0;
                manager->addTimer(timerIndex, 0, 0, OFF);
            }
            selectMode = 1;
            currentMode = SET_TIMER;
        }
        else if(digitalRead(MENU_BUTTON) == LOW && millis() - lastMenuBtn >= 600)
        {
            lastMenuBtn = millis();
            selectMode = 1;
            currentMode = MENU;
            lcd.clear();
        }
    }
    else if(currentMode == SET_TIMER)
    {
        if(digitalRead(DOWN_BUTTON) == LOW && millis() - lastDownBtn >= 200)
        {
            lastDownBtn = millis();
            if(selectMode == 1)
            {
                setHour -= 1;
                if(setHour < 0)
                {
                    setHour = 23;
                }
            }
            else if(selectMode == 2)
            {
                setMin -= 1;
                if(setMin < 0)
                {
                    setMin = 59;
                }
            }
            else if(selectMode == 3)
            {
                setMode -= 1;
                if(setMode < 0)
                {
                    setMode = 1;
                }
            }
            else if(selectMode == 4)
            {
                if(enableTimer == true)
                {
                    enableTimer = false;
                }
                else
                {
                    enableTimer = true;
                }
            }
        }
        else if(digitalRead(UP_BUTTON) == LOW && millis() - lastUpBtn >= 200)
        {
            lastUpBtn = millis();
            if(selectMode == 1)
            {
                setHour += 1;
                if(setHour > 23)
                {
                    setHour = 0;
                }
            }
            else if(selectMode == 2)
            {
                setMin += 1;
                if(setMin > 59)
                {
                    setMin = 0;
                }
            }
            else if(selectMode == 3)
            {
                setMode += 1;
                if(setMode > 1)
                {
                    setMode = 0;
                }
            }
            else if(setMode == 4)
            {
                if(enableTimer == true)
                {
                    enableTimer = false;
                }
                else
                {
                    enableTimer = true;
                }
            }
        }
        else if(digitalRead(OK_BUTTON) == LOW && millis() - lastOkBtn >= 600)
        {
            lastOkBtn = millis();
            lcd.clear();
            if(selectMode > 3)
            {
                if(enableTimer == true)
                {
                    manager->changeTimer(timerIndex, setHour, setMin, setMode);
                }
                else
                {
                    manager->deleteTimer(timerIndex);
                }
                currentMode = TIMER_LIST;
                setHour = -1;
                setMin = -1;
            }
            else
            {
                selectMode += 1;
            }
        }
        else if(digitalRead(MENU_BUTTON) == LOW && millis() - lastMenuBtn >= 600)
        {
            lastMenuBtn = millis();
            currentMode = TIMER_LIST;
            selectMode = 1;
        }
    }
    else if(currentMode == SET_RTC)
    {   
        if(digitalRead(DOWN_BUTTON) == LOW && millis() - lastDownBtn >= 200)
        {
            lastDownBtn = millis();
            if(selectMode == 1)
            {
                setHour -= 1;
                if(setHour < 0)
                {
                    setHour = 23;
                }
            }
            else if(selectMode == 2)
            {
                setMin -= 1;
                if(setMin < 0)
                {
                    setMin = 59;
                }
            }
            else if(selectMode == 3)
            {
                setDow -= 1;
                if(setDow < 0)
                {
                    setDow = 7;
                }
            }
            else if(selectMode == 4)
            {
                setDay -= 1;
                if(setDay < 0)
                {
                    setDay = 30;
                }
            } 
            else if(selectMode == 5)
            {
                setMonth -= 1;
                if(setMonth < 0)
                {
                    setMonth = 12;
                }
            }
            else if(selectMode == 6)
            {
                setYear -= 1;
                if(setYear < 0)
                {
                    setYear = 2100;
                }
            }              
        }
        else if(digitalRead(UP_BUTTON) == LOW && millis() - lastUpBtn >= 200)
        {
            lastUpBtn = millis();
            if(selectMode == 1)
            {
                setHour += 1;
                if(setHour > 23)
                {
                    setHour = 0;
                }
            }
            else if(selectMode == 2)
            {
                setMin += 1;
                if(setMin > 59)
                {
                    setMin = 0;
                }
            }
            else if(selectMode == 3)
            {
                setDow += 1;
                if(setDow > 7)
                {
                    setDow = 0;
                }
            }
            else if(selectMode == 4)
            {
                setDay  += 1;
                if(setDay > 31)
                {
                    setDay = 1;
                }
            } 
            else if(selectMode == 5)
            {
                setMonth  += 1;
                if(setMonth > 12)
                {
                    setMonth = 1;
                }
            }
            else if(selectMode == 6)
            {
                setYear += 1;
                if(setYear > 2100)
                {
                    setYear = 2000;
                }
            }          
        }
        else if(digitalRead(OK_BUTTON) == LOW && millis() - lastOkBtn >= 600)
        {
            lastOkBtn = millis();
            lcd.clear();
            if(selectMode > 5)
            {
                myRTC.setDS1302Time(0, setMin, setHour, setDow, setDay, setMonth, setYear);
                currentMode = MENU;
                selectMode = 1;
            }
            else
            {
                selectMode += 1;
            }
        }
        else if(digitalRead(MENU_BUTTON) == LOW && millis() - lastDownBtn >= 600)
        {
            lastMenuBtn = millis();
            lcd.clear();
            currentMode = MENU;
            selectMode = 1;
        }
    }


    if(currentMode == NORMAL)
    {
        displayDateTime();
    }
    else if(currentMode == MENU)
    {
        menuScreen(lcd, selectMode);
    }
    else if(currentMode == SET_RTC)
    {
        setRtcScreen(lcd, myRTC, setHour, setMin, setDow, setDay, setMonth, setYear, selectMode);
    }
    else if(currentMode == TIMER_LIST)
    {
        timerListScreen(lcd, manager, selectMode);
    }
    else if(currentMode == SET_TIMER)
    {
        setTimerScreen(lcd, manager, setHour, setMin, setMode, enableTimer, selectMode);
    }
}

void checkTimers()
{
    for(int i = 0; i < MAX; i++)
    {
        if(myRTC.hours == manager->getTimer(i)->getHour() &&
           myRTC.minutes == manager->getTimer(i)->getMinute() &&
           myRTC.seconds == 0)
        {
            /* T2 -> T7 */
//            if(myRTC.dayofweek != 0)
//            {
//                lightStatus = manager->getTimer(i)->getMode();
//                digitalWrite(LIGHT, lightStatus);
//            }
              lightStatus = manager->getTimer(i)->getMode();
              digitalWrite(LIGHT, lightStatus);
              digitalWrite(RELAY, !lightStatus);
        }
    }
}

void displayDateTime()
{
    /* display time */
    bigNum.displayLargeInt(myRTC.hours, 3, 2, true);
    lcd.setCursor(10, 1);
    lcd.print("O");
    lcd.setCursor(10, 2);
    lcd.print("O");
    bigNum.displayLargeInt(myRTC.minutes, 11, 2, true);
    /* display date */
    lcd.setCursor(3, 0);
    if(myRTC.dayofweek > 1)
    {
        lcd.print("T");
        lcd.print(myRTC.dayofweek);
    }
    else
    {
        lcd.print("CN");
    }
    lcd.print("/");
    if(myRTC.dayofmonth < 10)
    {
        lcd.print("0");
    }
    lcd.print(myRTC.dayofmonth);
    lcd.print("/");
    if(myRTC.month < 10)
    {
        lcd.print("0");
    }
    lcd.print(myRTC.month);
    lcd.print("/");
    lcd.print(myRTC.year);
}

void lightSwitchPresed()
{
    lightStatus = !lightStatus;
    digitalWrite(LIGHT, lightStatus);
    digitalWrite(RELAY, !lightStatus);
}







