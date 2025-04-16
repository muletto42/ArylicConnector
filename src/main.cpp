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
 #define ArylicUARTPORT Serial1  //auto& ArylicUART = Serial1; //das geht auch als Namensgeber
 #define ARYLIC_TX_PIN 6 // UART1 TX mit Amp RX verbinden //GP4 
 #define ARYLIC_RX_PIN 7 // UART1 RX mit Amp TX verbinden //GP5 
//#define ARYLIC_TX			11 // UART1 TX mit Amp RX verbinden //GP8 
//#define ARYLIC_RX	    12 // UART1 RX mit Amp TX verbinden //GP9 

// ArylicUART arylic(ArylicUARTPORT, ARYLIC_TX_PIN, ARYLIC_RX_PIN);
ArylicUART arylic(ArylicUARTPORT);
String userInput;

void parseUserCommand(const String &line)
{
    if (line.startsWith("vol "))
    {
        int vol = line.substring(4).toInt();
        arylic.setVolume(vol);
    }
    else if (line.startsWith("src "))
    {
        String source = "NET";
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
//   arylic.begin(115200, ARYLIC_TX_PIN, ARYLIC_RX_PIN);

}

void loop()
{
#if DEBUG
  digitalWrite(LED_BUILTIN, millis() % 1000 > 500); // blinking LED 500ms an, 500ms aus Lifesign
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
//   arylic.loop();
}

