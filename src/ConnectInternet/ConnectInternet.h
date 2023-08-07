#ifndef _CONNECTINTERNET_H
#define _CONNECTINTERNET_H

#include "Arduino.h"
#include "WiFiManager.h"
#include "../Debug/Debug.h"
#include <EEPROM.h>
#define SSID_DEFAULT "FARM_SUPPORT_SYSTEMS"
class ConnectInternet
{
private:
    /* data */
public:
    char *ssid;
    char *pass;
    // Hàm khởi tạo
    ConnectInternet();
    ConnectInternet(char *ssid,char *pass);
    // Kết nối và kiểm tra kết nối
    void connect();
    bool isConnected();
    bool resetConnect();
    // Get, set thuộc tính
    void setSSID(char *ssid);
    void setPass(char *pass);
    String getSSID();
    String getPass();
};
#endif
