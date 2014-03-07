#include <LiquidCrystal.h>
LiquidCrystal *lcd;
int input = 0;

void setup() {
  // put your setup code here, to run once:
    lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
    lcd->begin(16,2);
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Button Pressed:");
    
    Serial.begin(115200);
}

int curr = 0;
void loop() {
  // put your main code here, to run repeatedly:
  input = analogRead(0);
  Serial.println(input);
  lcd->setCursor(0,1);
  if (input > 600) {
   //btnNONE
   curr = 0;
   lcd->print("NONE  ");
  } else if (input < 50) {
    curr = 1;
    lcd->print("RIGHT ");
  } else if (input < 150) {
    curr = 2;
    lcd->print("UP    ");
  } else if (input < 300) {
    curr = 3;
    lcd->print("DOWN  ");
    curr = 4;
  } else if (input < 400) {
    curr = 5;
    lcd->print("LEFT  ");
  } else if (input < 600) {
    curr = 6;
    lcd->print("SELECT"); 
  }
}
