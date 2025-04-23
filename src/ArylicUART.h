#include "OpenKNX.h"
#include <Arduino.h>

class ArylicUART : public OpenKNX::Module
{
public:
    const std::string name() override;
    const std::string version() override;
    const uint8_t _major = MODULE_FileTransferModule_Version_Major; // also update library.json
    const uint8_t _minor = MODULE_FileTransferModule_Version_Minor;
    const uint8_t _revision = MODULE_FileTransferModule_Version_Revision;
    void loop() override;
    void setup() override;

    // Konstruktor: Übergibt die HardwareSerial-Instanz
    //ArylicUART(SerialUART &serial);
    ArylicUART(SerialUART &serial = Serial2, unsigned long baud = 115200, int txPin=6, int rxPin=7) : _serial(serial), _baud(baud), _txPin(txPin), _rxPin(rxPin){};
    
    // Initialisierung der UART-Verbindung mit TX/RX Pins und Baudrate
    void config(unsigned long baud, int txPin, int rxPin);

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


    void processInputKo(GroupObject &ko) override;

    // Öffentliche Variablen für Lautstärke und Quelle
    int currentVolume = -1;
    String currentSource = "initValue";
    bool muteMode = false;  // Speichert den MUTE-Zustand


private:
    // Private Methode zur Verarbeitung von empfangenen Zeilen
    void handleIncomingData(void);

    // Interne Variablen
    unsigned long _baud = 115200;
    int _txPin=6; 
    int _rxPin=7;
    SerialUART& _serial;
    String _recvBuffer;
};

extern ArylicUART openknxArylicUARTModule;