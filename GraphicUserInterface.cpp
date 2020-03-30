#include "GraphicUserInterface.h"
#include "MyTimer.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <virtuabotixRTC.h>

void drawFrame(LiquidCrystal_I2C lcd, int mode)
{
    byte leftUpCorner[] = {
    0x00,
    0x00,
    0x00,
    0x0F,
    0x0F,
    0x0C,
    0x0C,
    0x0C
    };

    byte leftDownCorner[] = {
    0x0C,
    0x0C,
    0x0C,
    0x0F,
    0x0F,
    0x00,
    0x00,
    0x00
    };

    byte rightUpCorner[] = {
    0x00,
    0x00,
    0x00,
    0x1E,
    0x1E,
    0x06,
    0x06,
    0x06
    };

    byte rightDownCorner[] = {
    0x06,
    0x06,
    0x06,
    0x1E,
    0x1E,
    0x00,
    0x00,
    0x00
    };

    byte dash[] = {
    0x00,
    0x00,
    0x00,
    0x1F,
    0x1F,
    0x00,
    0x00,
    0x00
    };

    byte barLeft[] = {
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C,
    0x0C
    };

    byte barRight[] = {
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06
    };

    byte arrow[] = {
    0x08,
    0x04,
    0x02,
    0x01,
    0x01,
    0x02,
    0x04,
    0x08
    };

    lcd.createChar(0, leftUpCorner);
    lcd.createChar(1, leftDownCorner);
    lcd.createChar(2, rightUpCorner);
    lcd.createChar(3, rightDownCorner);
    lcd.createChar(4, dash);
    lcd.createChar(5, barLeft);
    lcd.createChar(6, barRight);
    lcd.createChar(7, arrow);

    lcd.setCursor(0, 0);
    lcd.write(0);
    if(mode == WELCOME)
    {
        for(int i = 1; i < 19; i++)
        {
            lcd.setCursor(i, 0);
            lcd.write(4);
        }
    }
    if(mode == MENU)
    {
        for(int i = 1; i < 8; i++)
        {
            lcd.setCursor(i, 0);
            lcd.write(4);
        }
        for(int i = 12; i < 19; i++)
        {
            lcd.setCursor(i, 0);
            lcd.write(4);
        }
    }
    lcd.setCursor(19, 0);
    lcd.write(2);

    lcd.setCursor(0, 1);
    lcd.write(5);
    lcd.setCursor(19, 1);
    lcd.write(6);

    lcd.setCursor(0, 2);
    lcd.write(5);
    lcd.setCursor(19, 2);
    lcd.write(6);

    lcd.setCursor(0, 3);
    lcd.write(1);
    for(int i = 1; i < 19; i++)
    {
        lcd.setCursor(i, 3);
        lcd.write(4);
    }
    lcd.setCursor(19, 3);
    lcd.write(3);
}

void welcomeScreen(LiquidCrystal_I2C lcd)
{
    drawFrame(lcd, WELCOME);
    lcd.setCursor(3, 1);
    lcd.print("THPT Nguyen Du");
    lcd.setCursor(8, 2);
    lcd.print("****");
}

void menuScreen(LiquidCrystal_I2C lcd, int selection)
{
    byte arrow[] = {
    0x08,
    0x04,
    0x02,
    0x01,
    0x01,
    0x02,
    0x04,
    0x08
    };
    lcd.createChar(7, arrow);
    lcd.setCursor(8, 0);
    lcd.print("MENU");
    switch(selection)
    {
        case 1:
        {
            lcd.setCursor(1, 2);
            lcd.print(" ");
            lcd.setCursor(1, 1);
            break;
        }
        case 2:
        {
            lcd.setCursor(1, 1);
            lcd.print(" ");
            lcd.setCursor(1, 2);
            break;
        }
    }
    lcd.write(7);
    lcd.setCursor(2, 1);
    lcd.print("Chinh dong ho");
    lcd.setCursor(2, 2);
    lcd.print("Hen gio ON/OFF");
}

void setTimerScreen(LiquidCrystal_I2C lcd, TimerManager* timerManager, int h, int m, int mode, bool enableTimer, int selection)
{
       
    lcd.setCursor(3, 0);
    lcd.print("HEN GIO ON/OFF");

    lcd.setCursor(3, 1);
    if(h < 10)
    {
        lcd.print("0");
    }
    lcd.print(h);
    lcd.print(":");
    if(m < 10)
    {
        lcd.print("0");
    }
    lcd.print(m);
    lcd.print(":");
    if(mode == 0)
    {
        lcd.print("OFF");
    }
    else if(mode == 1)
    {
        lcd.print("ON");
        lcd.print(" ");
    }
    lcd.print(" ");
    if(enableTimer == true)
    {
        lcd.print("OK ");
    }
    else
    {
        lcd.print("HUY");
    }

    switch(selection)
    {
        case 1:
        {
            lcd.setCursor(3, 2);
            lcd.print("^");
            break;
        }
        case 2:
        {
            lcd.setCursor(6, 2);
            lcd.print("^");
            break;
        }
        case 3:
        {
            lcd.setCursor(9, 2);
            lcd.print("^");
            break;
        }
        case 4:
        {
            lcd.setCursor(13, 2);
            lcd.print("^");
            break;
        }
    }
}

void timerListScreen(LiquidCrystal_I2C lcd, TimerManager* timerManager, int selection)
{
    lcd.setCursor(3, 0);
    lcd.print("HEN GIO ON/OFF");

    switch(selection)
    {
        case 1:
        {
            lcd.setCursor(0, 1);
            lcd.write(7);
            break;
        }
        case 2:
        {
            lcd.setCursor(10, 1);
            lcd.write(7);
            break;
        }
        case 3:
        {
            lcd.setCursor(0, 2);
            lcd.write(7);
            break;
        }
        case 4:
        {
            lcd.setCursor(10, 2);
            lcd.write(7);
            break;
        }
        case 5:
        {
            lcd.setCursor(0, 3);
            lcd.write(7);
            break;
        }
        case 6:
        {
            lcd.setCursor(10, 3);
            lcd.write(7);
            break;
        }
    }
    for(int i = 0; i < MAX; i++)
    {
        switch(i)
        {
            case 0:
            {
                lcd.setCursor(1, 1);
                break;
            }
            case 1:
            {
                lcd.setCursor(11, 1);
                break;
            }
            case 2:
            {   
                lcd.setCursor(1, 2);
                break;
            }
            case 3:
            {
                lcd.setCursor(11, 2);
                break;
            }
            case 4:
            {
                lcd.setCursor(1, 3);
                break;
            }
            case 5:
            {
                lcd.setCursor(11, 3);
                break;
            }
        }
        if(timerManager->getTimer(i) != NULL)
        {
            if(timerManager->getTimer(i)->getHour() < 10)
            {
                lcd.print("0");
            }
            lcd.print(timerManager->getTimer(i)->getHour());
            lcd.print(":");
            if(timerManager->getTimer(i)->getMinute() < 10)
            {
                lcd.print("0");
            }
            lcd.print(timerManager->getTimer(i)->getMinute());
            lcd.print(":");
            if(timerManager->getTimer(i)->getMode() == 0)
            {
                lcd.print("OFF");
            }
            else
            {
                lcd.print("ON");
            }
        }
        else
        {
            lcd.print("////////");
        }
    }
}

void setRtcScreen(LiquidCrystal_I2C lcd, virtuabotixRTC rtc, int h, int m, int dow, int d, int month, int y, int selection)
{
    lcd.setCursor(3, 0);
    lcd.print("CHINH DONG HO");
 
    /* set time */
    lcd.setCursor(1, 1);
    if(h < 10)
    {
        lcd.print("0");
    }
    lcd.print(h);
    lcd.print(":");
    if(m < 10)
    {
        lcd.print("0");
    }
    lcd.print(m);
    /* set date */
    lcd.setCursor(7, 1);
    if(dow > 1)
    {
        lcd.print("T");
        lcd.print(dow);
    }
    else
    {
        lcd.print("CN");
    }
    lcd.print("/");
    if(d < 10)
    {
        lcd.print("0");
    }
    lcd.print(d);
    lcd.print("/");
    if(month < 10)
    {
        lcd.print("0");
    }
    lcd.print(month);
    lcd.print("/");
    lcd.print(y);
    
    switch(selection)
    {
        case 1:
        {
            lcd.setCursor(1, 2);
            lcd.print("^");
            break;
        }
        case 2:
        {
            lcd.setCursor(4, 2);
            lcd.print("^");
            break;
        }
        case 3:
        {
            lcd.setCursor(7, 2);
            lcd.print("^");
            break;
        }
        case 4:
        {
            lcd.setCursor(10, 2);
            lcd.print("^");
            break;
        }
        case 5:
        {
            lcd.setCursor(13, 2);
            lcd.print("^");
            break;
        }
        case 6:
        {
            lcd.setCursor(16, 2);
            lcd.print("^");
            break;
        }
    }
}

