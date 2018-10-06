#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int year;
int month;
int day;
int hour;
int minute;
int second;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("01/06/2018");
  lcd.setCursor(4, 1);
  lcd.print("00:00:00");
}

void loop()
{
  setupByUSB();

  ticTac();

  writeDate();
  writeTime();
}