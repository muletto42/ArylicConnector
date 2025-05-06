#include "OpenKNX.h"
#include <Arduino.h>
#include "hardware.h"

class ArylicUART : public OpenKNX::Module
{
public:
    const std::string name() override;
    const std::string version() override;
    void loop() override;
    void setup() override;

    // Konstruktor: Übergibt die HardwareSerial-Instanz
    // ArylicUART(SerialUART &serial);
    ArylicUART(SerialUART &serial = Serial2, unsigned long baud = 115200, int txPin = 6, int rxPin = 7) : _serial(serial), _baud(baud), _txPin(txPin), _rxPin(rxPin) {};

    // Initialisierung der UART-Verbindung mit TX/RX Pins und Baudrate
    // void config(unsigned long baud, int txPin, int rxPin);

    void setSource(uint sourcenumber);    // SRC
    void setSource(const String &source); // SRC
                                          /*
                                          {source} 	description
                                          NET 	    network
                                          BT 	    bluetooth
                                          USBDAC 	USB DAC
                                          LINE-IN 	line-in
                                          OPT 	    Optical
                                          COAX 	    Coaxial
                                          */
    void getSource(void);

    void playPause();                                // POP play or pause, available in network playback and bluetooth
    void stop();                                     // STP stop, available only in network playback
    void next();                                     // NXT next track, available in network playback and bluetooth
    void previous();                                 // PRE previous track, available in network playback and bluetooth
    void playPreset(int presetNum);                  // start to play preset playlist
    void setLoopShuffleMode(const String &loopmode); // LPM[:{loopmode}]   set/get loop and shuffle mode, available in network playback.
    /*
    {loopmode} 	    description
    REPEATALL 	    repeat all in playlist
    REPEATONE 	    repeat track
    REPEATSHUFFLE 	repeat all and shuffle
    SHUFFLE 	    shuffle and stop when all tracks played
    SEQUENCE 	    stop when reach end of playlist
    */

    void setVolume(int volume);
    void getVolume(void);

    void setMute(int onoff);
    void getDeviceStatus(void); // get device status, available in network playback and bluetooth

    void processInputKo(GroupObject &ko) override;

    // Öffentliche Variablen für Lautstärke und Quelle
    int currentVolume = 0;
    uint icurrentSource = PT_Source_network;
    String string_currentSource = "NET";
    bool muteStatus = false; // Speichert den MUTE-Zustand
    bool beepEnabled = false;
    bool virtualBassEnabled = false;
    bool bluetoothConnected = false;
    int currentBassTone = 0;
    int currentTrebleTone = 0;
    int currentMidTone = 0;
    bool netStatus = false;
    bool internetStatus = false;
    bool playingStatus = false;
    bool ledStatus = false;
    bool upgradingStatus = false;

private:
    // Private Methode zur Verarbeitung von empfangenen Zeilen
    void handleIncomingData(void);
    void processReceivedUARTCommand(const String commandType, const String commandValue);
    void sendRawCommandToArylic(const String command);
    void processSTACommand(const String commandValue);
    int sourceStringToInt(const String source);

    // Interne Variablen
    unsigned long _baud = 115200;
    int _txPin = ARYLIC_TX_PIN;
    int _rxPin = ARYLIC_RX_PIN;
    SerialUART &_serial;
    String _recvBuffer;
};

extern ArylicUART openknxArylicUARTModule;