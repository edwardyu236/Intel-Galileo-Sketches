#include <SPI.h>
#include <Ethernet.h>

// the media access control (ethernet hardware) address for the Galileo:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
//the IP address for the Galileo:
byte ip[] = { 192, 168, 0, 2 };    

void setup()
{
    if (Ethernet.begin(mac) == 0) {
        Serial.begin(9600);
        Serial.println("Failed to configure Ethernet using DHCP");
        Serial.println("Attempting to configure Ethernet using Static IP");
        if (Ethernet.begin(mac, ip) == 0) {
            Serial.println("Failed to configure Ethernet using Static IP");
        }
    }
}

void loop () {}