#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Test LCD");         // print a simple message
}

void loop()
{
}
