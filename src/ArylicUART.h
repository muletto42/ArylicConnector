#pragma once
#include <Arduino.h>

class ArylicUART {
public:
    // Konstruktor: Übergibt die HardwareSerial-Instanz
    ArylicUART(SerialUART &serial);

    // Initialisierung der UART-Verbindung mit TX/RX Pins und Baudrate
    void begin(unsigned long baud, int txPin, int rxPin);

    // Methoden zum Senden von Befehlen und zum Steuern
    void sendRawCommandToArylic(const String& command);

    /*Playback*/
    void setSource(const String& source); // SRC
    /*
    {source} 	description
    NET 	    network
    BT 	        bluetooth
    USBDAC 	    USB DAC
    LINE-IN 	line-in
    OPT 	    Optical
    COAX 	    Coaxial
    LINE-IN2 	extra line-in
    OPT2 	    extra Optical
    COAX2 	    extra Coaxial
    HDMI 	    HDMI ARC
    */

    void playPause(); //POP play or pause, available in network playback and bluetooth
    void stop(); //STP stop, available only in network playback
    void next(); //NXT next track, available in network playback and bluetooth
    void previous(); //PRE previous track, available in network playback and bluetooth
    void playPreset(int presetNum); //start to play preset playlist
    void setLoopShuffleMode(const String& loopmode); //LPM[:{loopmode}]   set/get loop and shuffle mode, available in network playback. 
    /*
    {loopmode} 	    description
    REPEATALL 	    repeat all in playlist
    REPEATONE 	    repeat track
    REPEATSHUFFLE 	repeat all and shuffle
    SHUFFLE 	    shuffle and stop when all tracks played
    SEQUENCE 	    stop when reach end of playlist
    */

    void setVolume(int volume);
    void setMute(int onoff);

    // Hauptloop zur Verarbeitung von eingehenden Daten
    void loop();

    // Öffentliche Variablen für Lautstärke und Quelle
    int currentVolume = -1;
    String currentSource = "initValue";
    bool muteMode = false;  // Speichert den MUTE-Zustand


private:
    // Private Methode zur Verarbeitung von empfangenen Zeilen
    void handleIncomingData(void);

    // Interne Variablen
    SerialUART& _serial;
    String _recvBuffer;
};
