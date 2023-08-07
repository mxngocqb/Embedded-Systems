#ifndef _SWITCH_H_
#define _SWITCH_H_

#define BLYNK_TEMPLATE_ID "TMPL6a4dLgmmy"
#define BLYNK_TEMPLATE_NAME "Ngoc Thanh"
#define BLYNK_AUTH_TOKEN "iIvspxRjmJ4-s7Gb9DW2oyJo7QHxFyEp"

#define NHIETDO V0     // Dữ liệu nhiệt độ
#define ANHSANG V1     // Dữ liệu ánh sáng
#define BULL V2        // Bóng đèn
#define FAN V3         // Quạt
#define BUTTON_BULL V4 // Nút đèn ảo
#define BUTTON_FAN V5  // Nút quạt ảo
#define BUTTON_CHANGE_MODE V6
#define ALERT V7
#define BULB_PIN D5
#define FAN_PIN D6
#define MODE_ADDR 8

// Khai báo địa chỉ trên EEPROM
#define STATE_FAN_ADDR 0
#define STATE_BULL_ADDR 4

class Switch
{
public:
    Switch();
    ~Switch();
    void connectToBlynk();
    void sendDataToBlynk(float temp, float light);
    void changeDeviceBull(int level);
    void changeDeviceFan(int level);
    void changeMode(int level);
    void alert(int level);
};

#endif