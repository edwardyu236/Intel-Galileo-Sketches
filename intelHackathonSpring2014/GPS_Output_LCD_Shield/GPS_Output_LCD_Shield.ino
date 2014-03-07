#include <LiquidCrystal.h>
#include <Adafruit_GPS.h>
Adafruit_GPS GPS(&Serial1);
#define GPSECHO  false

LiquidCrystal *lcd;
int backLight = 13;

void setup()  
{
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  Serial1.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);

  //delay(1000);
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd->begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd->clear();                  // start with a blank screen
  lcd->setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd->print("GPS:");    // change this text to whatever you like. keep it clean.
}



uint32_t timer = millis();
void loop()                     // run over and over again
{
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
//  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
//  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      
      int latTK = (int) (GPS.latitude * 10000 + 0.5);
      int lonTK = (int) (GPS.longitude * 10000 +  0.5);

      String data = "Lat: ";
      data += latTK;
      data += " Long: ";
      data += lonTK;
           
      
      String cmd = "echo '";
      cmd += data;
      cmd += "' > locFile ";
      
      int buffLen = cmd.length();
      char cmdArr[buffLen];
      
      cmd.toCharArray(cmdArr, buffLen);
      
      system(cmdArr);
      
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
      
      lcd->setCursor(0,0);  // set cursor to column 0, row 1
      lcd->print("Lat: "); lcd->print(GPS.latitude, 4);
      lcd->setCursor(0,1);
      lcd->print("Long: "); lcd->print(GPS.longitude, 4);
    } else {
      lcd->setCursor(0,1);
      lcd->print("NO GPS Location");
      system("echo 'Location Not found' > locFile");
    }

  }
}
