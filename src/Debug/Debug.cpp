#include "Debug.h"

static SSD1306Wire display(0x3c, 4, 5); // ADDRESS, SDA, SCL

Debug::Debug(){};
Debug::~Debug(){};

void Debug::LOG_TO_SCREEN(int x, int y, String string)
{
  if (!display.init())
  {
    display.init();
  }
  // display.displayOn();
  if (x > 128)
    x = 0;
  if (y > 64)
    y = 0;
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  // display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawStringMaxWidth(x, y, MAX_WIDTH, string);
  display.display();
  delay(2);
}

void Debug::LOG_PROGRESS_UPDATE(int current, int sum)
{
  delay(10);
  display.init();
  display.displayOn();
  display.clear();
  int progress = current * 100 / sum;
  display.drawProgressBar(0, 32, 120, 10, progress);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, "Update..." + String(progress) + "%");
  display.drawString(64, 50, String(current) + " of " + String(sum) + "kb");
  display.display();
}

void Debug::SCREEN_WELCOME()
{
  LOG_TO_SCREEN(0, 0, "WELCOME TO\n FARM SUPPORT SYSTEM!");
  delay(2000);
}