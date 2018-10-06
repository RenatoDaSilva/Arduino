//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP

//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  lcd.begin(16, 2);
  mainMessage();
}

void loop()
{
  int botao;
  botao = analogRead (0);  //Leitura do valor da porta analógica A0
  lcd.setCursor(8, 1);
  if (botao < 100) {
    onButtonPress ("Direita ");
  }
  else if (botao < 200) {
    onButtonPress ("Cima    ");
  }
  else if (botao < 400) {
    onButtonPress ("Baixo   ");
  }
  else if (botao < 600) {
    onButtonPress ("Esquerda");
  }
  else if (botao < 800) {
    onButtonPress ("Select  ");
  }
}

void mainMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressione");
  lcd.setCursor(0, 1);
  lcd.print(" um botao");
}

void onButtonPress(char message[16]) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voce pressionou");
  lcd.setCursor(0, 1);
  lcd.print(message);
  delay(3000);
  mainMessage();
}

