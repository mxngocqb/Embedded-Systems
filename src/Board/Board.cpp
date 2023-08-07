#include "Board.h"

Board::Board(){};
Board::~Board(){};
void Board::getChipInfo(){
    this->esp.chipId = ESP.getChipId();
    this->esp.coreVersion=ESP.getCoreVersion();
    this->esp.sketchSize =ESP.getSketchSize();
    this->esp.freeSketchSize =ESP.getFreeSketchSpace();
}

bool Board::checkActived(){
  EEPROM.begin(512);
  char status[] = "ACTIVED";
  int startAddress = 10;
  int index =0;
  while(status[index] == EEPROM.read(startAddress+index) && status[index] !='\0'){
    Serial.print(EEPROM.read(startAddress+index));
    index++;
  }
  if(index ==7) return true;
  return false;
}
void Board::getBoardInfo(){
  this->board.chipId = this->esp.chipId;
  this->board.checkActived = this->checkActived();
  if(this->board.checkActived == false){
    this->board.boardId = "null";
  }else{
    //read from EEPROM
  }
}
