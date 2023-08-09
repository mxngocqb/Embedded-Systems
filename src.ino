
#include "src\SiotCore.h"
#include "src\Sensor/Sensor.h"
#include "src\Switch/Switch.h"
// #include "src\NTP\Ntp.h"

// Ntp NetTimePro;
SiotCore core;
Sensor sensor;
Switch switch_1;
String response;
// ntp NetTimeProData;

int addr = 0;
int avgLight = 0;
float avgTemp = 0;
static uint64_t lastSave = 0, lastSend = 0;
int mode;  // Mode = 1, Auto, Mode = 2 Blynk, hen gio

unsigned long timeDelay = millis();
void blink();
void changeMode();
void changeState();

void setup() {
  sensor.init();
  EEPROM.begin(512);
  blink();
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  core.init();
  switch_1.connectToBlynk();
  Serial.println("Wifi is connected");
  core.updateData(URL_STATE, "Hello, you have successfully connected", response, POST);
  // NetTimePro.Start();
  // Setup MODE
  readFromIntEEPROM(MODE_ADDR, mode);
  pinMode(D7, INPUT_PULLUP);
  if (mode == 1)
    Debug::LOG_TO_SCREEN(0, 0, "AUTO MODE");
  else
    Debug::LOG_TO_SCREEN(0, 0, "SWITCH MDOE");
  attachInterrupt(CHANGE_MODE, changeMode, RISING);  // gọi hàm tatled liên tục khi còn nhấn nút
}

void loop() {
  // Đọc dữ liệu
  SensorData data;
  data = sensor.readDataSensor();
  sensor.sendDataToPC(data);

  char data2[50];
  // Chuyển Dữ liệu BLynk, điều khiển công tắc.

  // Ghi dữ liệu vào EEPROM
  if ((data.temp > -10) && (data.temp < 60) && (data.light > 0) && (data.light) < 400) {

    switch_1.sendDataToBlynk(data.temp, data.light);
    // Chuyển dữ liệu về Server Lưu trữ SIoT.
    sprintf(data2, "%f", data.temp);
    if (millis() - lastSend >= 50000) {
      core.updateData(URL_TEMP, data2, response, POST);
      sprintf(data2, "%d", data.light);
      core.updateData(URL_LIGHT, data2, response, POST);
      lastSend = millis();
    }

    if (addr < MIN_ADDR_DATA || addr >= MAX_ADDR_DATA) {
      addr = MIN_ADDR_DATA;
    } else {
      addr += sizeof(data);
    }

    writeDataToEEPROM(addr, data);
  }
  // Tính giá trị trung bình
  int count = 0;
  int diachi = MIN_ADDR_DATA;
  avgLight = 0;
  avgTemp = 0;
  while ((diachi >= MIN_ADDR_DATA) && (diachi <= MAX_ADDR_DATA)) {
    SensorData data_temp;
    readDataFromEEPROM(diachi, data_temp);
    avgLight += data_temp.light;
    avgTemp += data_temp.temp;
    diachi += sizeof(data);
  }
  avgLight = avgLight / 21;
  avgTemp = avgTemp / 21;
  // Chọn Mode nè hihi.
  readFromIntEEPROM(MODE_ADDR, mode);
  if (mode == 1) {
    // Xuất ra màn hình
    sprintf(data2, "MODE: Automatic            Temp: %.3f  AS: %d", data.temp, data.light);
    changeState();
    blink();
  } else {
    int fan_in = digitalRead(SW_FAN);
    int bulb_in = digitalRead(SW_BULB);
    if (fan_in == 0) {
      int tmp_state = 0;
      readFromIntEEPROM(STATE_FAN_ADDR, tmp_state);
      writeIntToEEPROM(STATE_FAN_ADDR, !tmp_state);
    }
    if (bulb_in == 1) {
      int tmp_state = 0;
      readFromIntEEPROM(STATE_BULL_ADDR, tmp_state);
      writeIntToEEPROM(STATE_BULL_ADDR, !tmp_state);
    }

    blink();
    // Xuất ra màn hình
    sprintf(data2, "MODE: Switch               Temp: %.3f  AS: %d", data.temp, data.light);
  }

  Debug::LOG_TO_SCREEN(0, 0, data2);
  // NetTimeProData = NetTimePro.readDataSensor();
  // Serial.println(NetTimeProData.year);
  // Serial.println(NetTimePro.convertDayToStr(NetTimeProData));
  // Serial.println(NetTimePro.convertTimeToStr(NetTimeProData));
  // Debug::LOG_TO_SCREEN(0, 0, NetTimePro.convertTimeToStr(NetTimeProData));
}

void blink() {
  int tmp_state = 0;
  readFromIntEEPROM(STATE_FAN_ADDR, tmp_state);
  if (tmp_state == 1) {
    digitalWrite(FAN_PIN, HIGH);
    switch_1.changeDeviceFan(1);
  } else {
    digitalWrite(FAN_PIN, LOW);
    switch_1.changeDeviceFan(0);
  }

  readFromIntEEPROM(STATE_BULL_ADDR, tmp_state);
  if (tmp_state == 1) {
    digitalWrite(BULB_PIN, HIGH);
    switch_1.changeDeviceBull(1);
  } else {
    digitalWrite(BULB_PIN, LOW);
    switch_1.changeDeviceBull(0);
  }
}

void changeState() {
  // Đoạn code này dùng cho mode tự động đo nhiệt đọ
  if (avgTemp >= 30.25) {
    writeIntToEEPROM(STATE_FAN_ADDR, 1);
  } else if (avgTemp >= 29.75) {
    writeIntToEEPROM(STATE_FAN_ADDR, 0);
  }

  if (avgLight < 30) {
    writeIntToEEPROM(STATE_BULL_ADDR, 1);
  } else if (avgLight > 40) {
    writeIntToEEPROM(STATE_BULL_ADDR, 0);
  }
  if ((millis() - timeDelay > 10000)) {
    if ((avgTemp > 100)) {
      switch_1.alert(1);
    } else {
      switch_1.alert(0);
    }
    timeDelay = millis();
  }
}

ICACHE_RAM_ATTR void changeMode() {
  if (millis() - timeDelay > 1000) {
    int tmp;
    readFromIntEEPROM(MODE_ADDR, tmp);
    if (tmp == 1) {
      tmp = 2;
      writeIntToEEPROM(MODE_ADDR, tmp);
      switch_1.changeMode(1);
    } else {
      tmp = 1;
      writeIntToEEPROM(MODE_ADDR, tmp);
      switch_1.changeMode(0);
    }
    timeDelay = millis();
  }
}
