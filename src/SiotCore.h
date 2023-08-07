#ifndef _SIOTCORE_H
#define _SIOTCORE_H_

#include "Arduino.h"
// #include "Define_Infor_core.h"
#include "Debug/Debug.h"
#include "Board/Board.h"
#include "Conmon/Conmon.h"
// #include "Switch/Switch.h"
// #include "Sensor/Sensor.h"
#include "ConnectServer/ConnectServer.h"
#include "ConnectInternet/ConnectInternet.h"

class SiotCore
{
private:
    /* data */
    String _ssid;
    String _pass;
    int _baudrate;
    String _version;

public:

    SiotCore(/* args */);
   // SiotCore(String ssid, String pass, int baudrate);
    ~SiotCore();
    void init();
    void info();
    void updateData();
    void updateData(String URI, String value, String& response, int method);
};


#endif