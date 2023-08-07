#include "Switch.h"
#include "BlynkSimpleEsp8266.h"
#include "..\Conmon\Conmon.h"

Switch::Switch() {}
Switch::~Switch() {}

int status_BULL = 0; // Trạng thái thiết bị 1
int status_FAN = 0;  // Trạng thái thiết bị 2

void Switch::connectToBlynk()
{
    // while (!cni.isConnected())
    // {
    //     cni.connect();
    // }
    readFromIntEEPROM(STATE_FAN_ADDR, status_BULL);
    readFromIntEEPROM(STATE_BULL_ADDR, status_FAN);
    Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
    Blynk.connect();
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(BULL, status_BULL);
        Blynk.virtualWrite(FAN, status_FAN);
        Blynk.virtualWrite(BUTTON_BULL, status_BULL);
        Blynk.virtualWrite(BUTTON_FAN, status_FAN);
        Blynk.virtualWrite(ALERT, 0);
    }
}

void Switch::changeDeviceBull(int level)
{
    status_BULL = level;
    // Gửi trạng thái lên blynk
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(BULL, status_BULL);
        Blynk.virtualWrite(BUTTON_BULL, status_BULL);
    }
}

void Switch::changeDeviceFan(int level)
{
    status_FAN = level;
    // Gửi trạng thái lên blynk
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(FAN, status_FAN);
        Blynk.virtualWrite(BUTTON_FAN, status_FAN);
    }
}

void Switch::alert(int level)
{
    // Gửi trạng thái lên blynk
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(ALERT, level);
    }
}

void Switch::changeMode(int level)
{
    // Gửi trạng thái lên blynk
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(BUTTON_CHANGE_MODE, level);
    }
}

void Switch::sendDataToBlynk(float temp, float light)
{
    Blynk.run();
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(NHIETDO, temp);
        Blynk.virtualWrite(ANHSANG, light);
    }
}

BLYNK_WRITE(BUTTON_BULL)
{ // Xử lý khi giá trị của đầu vào ảo thay đổi
    int mode;
    readFromIntEEPROM(MODE_ADDR, mode);
    if (mode == 1)
        return;
    status_BULL = param.asInt();
    writeIntToEEPROM(STATE_BULL_ADDR, status_BULL);
    Serial.println(param.asInt());
    digitalWrite(BULB_PIN, status_BULL);
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(BULL, status_BULL);
        Blynk.virtualWrite(BUTTON_BULL, status_BULL);
    }
}

BLYNK_WRITE(BUTTON_FAN)
{ // Xử lý khi giá trị của đầu vào ảo thay đổi
    int mode;
    readFromIntEEPROM(MODE_ADDR, mode);
    if (mode == 1)
        return;
    status_FAN = param.asInt();
    Serial.println(param.asInt());
    digitalWrite(FAN_PIN, status_FAN);
    writeIntToEEPROM(STATE_FAN_ADDR, status_FAN);
    if (WiFi.status() == WL_CONNECTED)
    {
        Blynk.virtualWrite(FAN, status_FAN);
        Blynk.virtualWrite(BUTTON_FAN, status_FAN);
    }
}

BLYNK_WRITE(BUTTON_CHANGE_MODE)
{ // Xử lý khi giá trị của đầu vào ảo thay đổi
    int mode;
    int status = param.asInt();
    if (status == 0)
    {
        writeIntToEEPROM(MODE_ADDR, 1);
    }
    else
    {
        writeIntToEEPROM(MODE_ADDR, 2);
    }
}