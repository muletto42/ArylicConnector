/*
// Arduino-Pico core for RP2040 
// https://arduino-pico.readthedocs.io/en/latest/
*/



#include <Arduino.h>
#include "ArylicUART.h"

//#define DEBUG 0
#define DEBUG 1

 /*
 * Serial is the USB serial port
 * The RP2040 provides two hardware-based UARTS with configurable pin selection.
 * Serial1 is UART0 --> KNX 
 * Serial2 is UART1 --> frei
 */
 #define ArylicUARTPORT Serial2 // Serial2 = UART1 //auto& ArylicUART = Serial1; //das geht auch als Namensgeber
 #define ARYLIC_TX_PIN 6 // UART1 TX mit Amp RX verbinden //GP4 
 #define ARYLIC_RX_PIN 7 // UART1 RX mit Amp TX verbinden //GP5 
//#define ARYLIC_TX			11 // UART1 TX mit Amp RX verbinden //GP8 
//#define ARYLIC_RX	    12 // UART1 RX mit Amp TX verbinden //GP9 

ArylicUART arylic; //Objektdefinitionen
String userInput;

void parseUserCommand(const String &line)
{
    if (line.startsWith("vol ") ||line.startsWith("VOL "))
    {
        int vol = line.substring(4).toInt();
        arylic.setVolume(vol);
    }
    else if (line.startsWith("src ") || line.startsWith("SRC ") )
    {
        String source = "";
        int src = line.substring(4).toInt();
        if (src == 1)
        {
            source = "NET";
        }
        else if (src == 2)
        {
            source = "BT"; 	 //       bluetooth
        }
        else if (src == 3)
        {
            source = "USBDAC"; 	 //       USB DAC
        }
        arylic.setSource(source);
    }
    else
    {
        Serial.println("[INFO] Unbekannter Befehl. Nutze: 'vol <0-100>' oder 'src <id>'");
    }
}

void setup() 
{
    Serial.begin(115200);
    Serial.println("Serial0 Startet...");

    pinMode(LED_BUILTIN, OUTPUT);
  //  UART-Verbindung zum AMP initialisieren
    //arylic.config(115200, ARYLIC_TX_PIN, ARYLIC_RX_PIN); //PIN Zuordnung funktioniert so nicht! FIXME wenn man das Aufruft dann zerlegt sich alles.
}
  
unsigned long lastHeartbeat = 0;
const unsigned long heartbeatInterval = 5000;

void loop()
{
#if DEBUG
  digitalWrite(LED_BUILTIN, millis() % 1000 > 500); // blinking LED 500ms an, 500ms aus Lifesign

    if (millis() - lastHeartbeat >= heartbeatInterval) 
    {
      Serial.println("lebt");
      lastHeartbeat = millis();
    }
#endif

#if DEBUG
// Benutzereingabe lesen
if (Serial.available()) {
  char c = Serial.read();
  if (c == '\n' || c == '\r') {
      if (userInput.length() > 0) {
          parseUserCommand(userInput);
          userInput = "";
      }
  } else {
      userInput += c;
  }
}
#endif
  // Arylic-Daten verarbeiten
   arylic.loop();
}

