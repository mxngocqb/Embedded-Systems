#include "SiotCore.h"
ConnectInternet cni;
ConnectServer cns;
SiotCore::SiotCore(){};
SiotCore::~SiotCore(){};

void SiotCore::init()
{
    this->_baudrate = 115200;
    this->_ssid = "FARM - SUPPORT";
    this->_pass = "123456";
    this->_version = "0.0";
    Wire.begin(4, 5);
    Debug::SCREEN_WELCOME();
}

void SiotCore::info()
{
}

void SiotCore::updateData()
{
    while (!cni.isConnected())
    {
        cni.connect();
    }
    while (cni.isConnected())
    {
        if (cns.isServerConnected())
        {
            cns.pushData();
        }
        else
        {
            Serial.println("Fail!");
        }
    }
}
void SiotCore::updateData(String URI, String value, String &response, int method)
{
    while (!cni.isConnected())
    {
        cni.connect();
    }
    cns.communicationSever(URI, value, response, method);
    // response = "abc";
}