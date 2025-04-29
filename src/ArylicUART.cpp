/*
  # Arylic's UART API developer documentation
  # https://developer.arylic.com/uartapi/#uart-api

# Basic Rules
   * messages are defined in 3 characters, and will use : to seperate the different part.
   * messages sent over UART need to be terminated with ;
   * messages might be received without query when state changed.
   * Content between {} is variable name, you need to replace with the real content, and {} itself is not meant to be sent.
   * Content between [] means optional, and [] itself is not meant to be sent.
   * normally, messages sent by host without param means to query current state or direct control
   * messages sent with param means to control or change state.
   * messages received normally with param indicating current state.
*/

#include "ArylicUART.h"

#define DEBUG 1 // auskommentieren wenn nicht benötigt

ArylicUART::ArylicUART(SerialUART &serial)
    : _serial(serial) {}

void ArylicUART::begin(unsigned long baud, int txPin, int rxPin)
{
    // Pins direkt vor begin() setzen // FIXME TODO funktioniert noch nicht!!!
    //_serial.setPinout(txPin, rxPin);
    _serial.begin(baud);
    // _serial.setTX(txPin);
    // _serial.setRX(rxPin);

    // delay(100); // Kurze Verzögerung, damit sich die Verbindung stabilisiert
}

void ArylicUART::sendRawCommandToArylic(const String &command)
{
    _serial.flush(); // Wartet, bis die Übertragung der ausgehenden seriellen Daten abgeschlossen ist.
    _serial.print(command+"\r\n");
#if DEBUG
    Serial.print("[SEND] ");
    Serial.println(command);
#endif
}

void ArylicUART::setLoopShuffleMode(const String &loopmode) // LPM[:{loopmode}]   set/get loop and shuffle mode, available in network playback.
{
    /*
    {loopmode} 	    description
    REPEATALL 	    repeat all in playlist
    REPEATONE 	    repeat track
    REPEATSHUFFLE 	repeat all and shuffle
    SHUFFLE 	    shuffle and stop when all tracks played
    SEQUENCE 	    stop when reach end of playlist
    */
    sendRawCommandToArylic("LPM:" + loopmode);
}

void ArylicUART::playPause() // POP play or pause, available in network playback and bluetooth
{
    sendRawCommandToArylic("POP");
}

void ArylicUART::stop() // STP stop, available only in network playback
{
    sendRawCommandToArylic("STP");
}

void ArylicUART::next() // NXT next track, available in network playback and bluetooth
{
    sendRawCommandToArylic("NXT");
}

void ArylicUART::previous() // PRE previous track, available in network playback and bluetooth
{
    sendRawCommandToArylic("PRE");
}

void ArylicUART::playPreset(int presetNum) // start to play preset playlist
{
    sendRawCommandToArylic("VOL:" + String(presetNum));
}

void ArylicUART::setVolume(int volume)
{
    volume = constrain(volume, 0, 100);
    sendRawCommandToArylic("VOL:" + String(volume));
}

void ArylicUART::setSource(const String &source) // SRC
{
    sendRawCommandToArylic("SRC:" + source);
    
}

void ArylicUART::setMute(int onoff)
{
    sendRawCommandToArylic("MUT:" + String(onoff));
}

void ArylicUART::loop()
{
    handleIncomingData();
}

void ArylicUART::handleIncomingData(void)
{
    // UART-Daten lesen
    if (_serial.available() > 0)
    {
        String receivedData = _serial.readStringUntil('\n');
        receivedData.trim(); // Entfernt alle führenden und nachfolgenden Leerzeichen aus der aktuellen Zeichenfolge.
#if DEBUG
        Serial.println("Empfangen: " + receivedData);
#endif
        int separatorIndex = receivedData.indexOf(':');
        if (separatorIndex > 0 && separatorIndex < receivedData.length() - 1)
        {
            String commandType = receivedData.substring(0, separatorIndex);
            String commandValue = receivedData.substring(separatorIndex + 1);

            // Daten auswerten
            if (commandType == "VOL")
            {
                currentVolume = commandValue.toInt();
#if DEBUG
                Serial.print("[INFO] Lautstärke aktualisiert: ");
                Serial.println(currentVolume);
#endif
            }
            else if (commandType == "SRC")
            {
                currentSource = commandValue;
#if DEBUG
                Serial.print("[INFO] Quelle aktualisiert: ");
                Serial.println(currentSource);
#endif
            }
            else if (commandType == "MUT")
            {
                muteMode = (bool)commandValue.toInt();
#if DEBUG
                Serial.print("[INFO] Mute Status: ");
                Serial.println(muteMode);
#endif
            }
            else
            {
                // Erweiterungen
            }
        }
    }
}
