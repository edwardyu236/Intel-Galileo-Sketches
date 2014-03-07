// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// make barchart custom characters:
byte b0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte b1[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte b2[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
byte b3[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};
byte b4[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};
byte b5[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte b6[8] = {
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111,
  0b01111
};
byte b7[8] = {
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111,
  0b00111
};
byte b8[8] = {
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011
};
byte b9[8] = {
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001,
  0b00001
};
// last shown barchart value
int BarLastBlocks = 0;
const int ScrollTextLength = 11;
String ScrollTextField[ScrollTextLength] = {
  "                ",
  "Scroll Text Demo",
  "                ",
  "egg             ",
  "   egg          ",
  "     egg        ",
  "      egg       ",
  "      egg       ",
  "    splash      ",
  "----((..))------",
  "need new egg ;^)"};

void setup() {
  // create a new character
  lcd.createChar(1, b0);
  lcd.createChar(2, b1);
  lcd.createChar(3, b2);
  lcd.createChar(4, b3);  
  lcd.createChar(5, b4);
  lcd.createChar(6, b5);

  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);

  Serial.begin(115200);

}

void loop() {
  int barDelay=20;
  // Print a message to the lcd.
  lcd.setCursor(0, 0);
  lcd.print("Barchart test  "); 
  // draw barchart
  // max barchart size = 16x5 = 80
  for (int j=0; j<1; j++){
    lcd.setCursor(15, 0);
    lcd.print(j); 
    for (int i=0; i<80; i++) {
      DrawBar(i);
      delay(barDelay);
    }
    for (int i=80; i>=0; i--) {
      DrawBar(i);
      delay(barDelay);
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Barchart reverse"); 
  // draw barchart
  // max barchart size = 16x5 = 80
  for (int j=0; j<1; j++){
    for (int i=0; i<80; i++) {
      DrawBarLeft(i);
      delay(barDelay);
    }
    for (int i=80; i>=0; i--) {
      DrawBarLeft(i);
      delay(barDelay);
    }
  }
  lcd.setCursor(0, 0);
  BarLastBlocks=0;
  lcd.print("Barchart random "); 
  for (int i=0; i<20; i++) {
    DrawBar(random(80));
    delay(100);
  }

  delay(1000); 
  ScrollText(1000);
  delay(2000);
}

void DrawBar(int value) {
  int fullblocks;
  int rightblock;
  int cursorPos;
  
  lcd.createChar(2, b1);
  lcd.createChar(3, b2);
  lcd.createChar(4, b3);  
  lcd.createChar(5, b4);

  lcd.setCursor(0, 1);

  // check value size and reset if neccessary
  if (value < 0) value = 0;
  if (value > 80) value = 80;
  // calulate number of full blocks
  fullblocks=0;
  while (fullblocks*5 < value) {
    fullblocks++;
  }
  fullblocks--;
  if (fullblocks < 0) fullblocks = 0;
  rightblock = value - fullblocks*5 + 1;
  cursorPos = fullblocks;
  if (BarLastBlocks < fullblocks) cursorPos = BarLastBlocks;
  lcd.setCursor(cursorPos, 1);
  for (int i=BarLastBlocks; i<fullblocks; i++) {
    lcd.write(6);
  }
  lcd.setCursor(fullblocks, 1);
  lcd.write(rightblock);
  for (int j=fullblocks+1; j<16; j++) {
    lcd.write(1);
  }
  BarLastBlocks = fullblocks;
}

void DrawBarLeft(int value) {
  int fullblocks;
  int rightblock;
  int cursorPos;
  
  lcd.createChar(2, b6);
  lcd.createChar(3, b7);
  lcd.createChar(4, b8);
  lcd.createChar(5, b9);

  lcd.setCursor(0, 1);

  value=80-value;
  // check value size and reset if neccessary
  if (value < 0) value = 0;
  if (value > 80) value = 80;
  // calulate number of full blocks
  fullblocks=0;
  while (fullblocks*5 < value) {
    fullblocks++;
  }
  fullblocks--;
  if (fullblocks < 0) fullblocks = 0;
  rightblock = value - fullblocks*5 + 1;
  cursorPos = fullblocks;
  if (BarLastBlocks < fullblocks) cursorPos = BarLastBlocks;
  lcd.setCursor(cursorPos, 1);
  for (int i=BarLastBlocks; i<fullblocks; i++) {
    lcd.write(1);
  }
  lcd.setCursor(fullblocks, 1);
  lcd.write(rightblock+5);
  for (int j=fullblocks+1; j<16; j++) {
    lcd.write(6);
  }
  BarLastBlocks = fullblocks;
}

void ScrollText (int sdelay) {
  String outp;
  int sline=0;
  for (int i=0; i<ScrollTextLength; i++) {
    sline=i;
    lcd.setCursor(0, 0);
    outp=ScrollTextField[sline];
    lcd.print(outp);
    sline=i+1;
    if (sline>=ScrollTextLength) sline = 0;
    lcd.setCursor(0, 1);
    outp=ScrollTextField[sline];
    lcd.print(outp);
    delay(sdelay);
  }
}









