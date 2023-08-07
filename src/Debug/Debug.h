
#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "Arduino.h"
#include <Wire.h> // include wire library (for I2C devices such as the SSD1306 display)
#include "Oled/SSD1306Wire.h"

#define MAX_WIDTH 128
#define MAX_HIGHT 64


class Debug
{
public:
    Debug();
    ~Debug();
    static void LOG_TO_SCREEN(int x, int y, String string);
    static void LOG_PROGRESS_UPDATE(int current, int sum);
    static void SCREEN_WELCOME();
    // Data members

private:
    // Data members
};

#endif
