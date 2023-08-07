#ifndef _BOARD_H_
#define _BOARD_H_
#include"Arduino.h"
#include <EEPROM.h>
#include <ESP8266WiFi.h>
struct ESP8266_Info
{
    /* data */
    int chipId;
    unsigned int sketchSize;
    unsigned int freeSketchSize;
    String coreVersion;
};
struct Board_Info{
  int chipId;
  char* boardId;
  char* currentFirmware;
  bool checkActived;
  bool autoUpdate;
  
};
class Board
{
private:
public:
    ESP8266_Info esp;
    Board_Info board;
    Board();
    ~Board();
    void getChipInfo();
    bool checkActived();
    void getBoardInfo();

};





#endif
