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
#include "versions.h"

// Give your Module a name
// it will be displayed when you use the method log("Hello")
//  -> Log     Hello
const std::string ArylicUART::name()
{
    return "ArylicUART";
}

// You can also give it a version
// will be displayed in Command Infos
const std::string ArylicUART::version()
{
    return MAIN_Version;
}

void ArylicUART::loop()
{
    handleIncomingData();
    static unsigned long lastMillis = 0; // Speichert den letzten Zeitpunkt
    unsigned long currentMillis = millis(); // Aktuelle Zeit in Millisekunden

    // Prüfen, ob eine Minute (60.000 Millisekunden) vergangen ist
    if (currentMillis - lastMillis >= 60000)
    {
        lastMillis = currentMillis; // Aktualisiere den letzten Zeitpunkt
        getDeviceStatus(); // Rufe den Status des Geräts ab
    }
}

void ArylicUART::setup()
{
    _serial.setTX(ARYLIC_TX_PIN);
    _serial.setRX(ARYLIC_RX_PIN);
    _serial.begin(BAUD_ARLYIC);
}

void ArylicUART::sendRawCommandToArylic(const String command)
{
    _serial.flush(); // Wartet, bis die Übertragung der ausgehenden seriellen Daten abgeschlossen ist.
    _serial.print(command + "\r\n");
#if DEBUG
    logDebugP("[SEND]: %s", command);
#endif
}

void ArylicUART::getDeviceStatus(void) // get device status, available in network playback and bluetooth
{
    sendRawCommandToArylic("STA;");
    /*
    Device status summary, and the response message {states} will
    consist with: current source,mute,volume,treble,bass,net,internet,playing,led,upgrading.
    STA response sample
    NET,0,33,-2,0,1,1,1,1,0
    */
}
void ArylicUART::getVolume() // get volume, available in network playback and bluetooth
{
    sendRawCommandToArylic("VOL;");
}
void ArylicUART::getSource() // get source, available in network playback and bluetooth
{
    sendRawCommandToArylic("SRC;");
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
    sendRawCommandToArylic("LPM:" + loopmode + ";");
}

void ArylicUART::playPause() // POP play or pause, available in network playback and bluetooth
{
    sendRawCommandToArylic("POP;");
}

void ArylicUART::stop() // STP stop, available only in network playback
{
    sendRawCommandToArylic("STP;");
}

void ArylicUART::next() // NXT next track, available in network playback and bluetooth
{
    sendRawCommandToArylic("NXT;");
}

void ArylicUART::previous() // PRE previous track, available in network playback and bluetooth
{
    sendRawCommandToArylic("PRE;");
}

void ArylicUART::playPreset(int presetNum) // start to play preset playlist
{
    sendRawCommandToArylic("PST:" + String(presetNum) + ";");
}

void ArylicUART::setVolume(int volume)
{
    volume = constrain(volume, 0, 100);
    sendRawCommandToArylic("VOL:" + String(volume) + ";");
}

void ArylicUART::setSource(uint sourcenumber) // SRC
{
    String source = " ";
    switch (sourcenumber)
    {
    case PT_Source_network:
    {
        source = "NET";
    }
    case PT_Source_bluetooth:
    {
        source = "BT";
    }
    break;
    case PT_Source_USBDAC:
    {
        source = "USBDAC";
    }
    break;
    case PT_Source_linein:
    {
        source = "LINE-IN";
    }
    break;
    case PT_Source_Optical:
    {
        source = "OPT";
    }
    break;
    case PT_Source_Coaxial:
    {
        source = "COAX";
    }
    break;

    default:
        break;
    }

    sendRawCommandToArylic("SRC:" + source + ";");
}

// Overload für String-Parameter
// Diese Methode wird aufgerufen, wenn der Quellparameter ein String ist
void ArylicUART::setSource(const String &source) // SRC
{
    sendRawCommandToArylic("SRC:" + source + ";");
}

void ArylicUART::setMute(int onoff)
{
    sendRawCommandToArylic("MUT:" + String(onoff) + ";");
}

// will be called once a KO received a telegram
void ArylicUART::processInputKo(GroupObject &iKo)
{
    uint16_t lAsap = iKo.asap();
    switch (lAsap)
    {
    case APP_Kovolume_inc: // Increase ++
    {
        if (KoAPP_volume_inc.value(DPT_Step))
        {
            currentVolume++;
        }
        setVolume(currentVolume);
        logDebugP("setVolume: %d", currentVolume);
    }
    break;
    case APP_Kovolume_dec: // Decrease --
    {
        if (KoAPP_volume_inc.value(DPT_Step))
        {
            currentVolume--;
        }
        setVolume(currentVolume);
        logDebugP("setVolume: %d", currentVolume);
    }
    break;
    case APP_Kovolume_value: // SET
    {
        currentVolume = (u_int8_t)KoAPP_volume_value.value(DPT_Scaling);
        setVolume(currentVolume);
        logDebugP("setVolume: %d", currentVolume);
    }
    break;
    case APP_Komute_onoff:
    {
        muteStatus = KoAPP_mute_onoff.value(DPT_Switch);
        setMute(muteStatus);
        logDebugP("MuteMode: %d", muteStatus);
    }
    break;
    case APP_KoPlayPause:
    {
        playPause();
    }
    break;
    case APP_KoStop:
    {
        stop();
    }
    break;
    case APP_KoNext:
    {
        next();
    }
    break;
    case APP_KoPrev:
    {
        previous();
    }
    break;
    case APP_Kosource:
    {
        uint icurrentSource;
        icurrentSource = (uint8_t)KoAPP_source.value(DPT_Value_1_Ucount);
        setSource(icurrentSource);
        logDebugP("setSource: %d", icurrentSource);
    }
    break;
    }
}

void ArylicUART::handleIncomingData(void)
{
    // UART-Daten lesen
    if (_serial.available() > 0)
    {
        String receivedData = _serial.readStringUntil('\n');
        receivedData.trim(); // Entfernt alle führenden und nachfolgenden Leerzeichen aus der aktuellen Zeichenfolge.
        logDebugP("Empfangen: : %s", receivedData);

        int separatorIndex = receivedData.indexOf(':');
        if (separatorIndex > 0 && separatorIndex < receivedData.length() - 1)
        {
            String commandType = receivedData.substring(0, separatorIndex);
            String commandValue = receivedData.substring(separatorIndex + 1);

            // Daten auswerten
            processReceivedUARTCommand(commandType, commandValue);
        }
    }
}

int ArylicUART::sourceStringToInt(const String source)
{
    if (source == "NET")
    {
        return PT_Source_network;
    }
    else if (source == "BT")
    {
        return PT_Source_bluetooth;
    }
    else if (source == "USBDAC")
    {
        return PT_Source_USBDAC;
    }
    else if (source == "LINE-IN")
    {
        return PT_Source_linein;
    }
    else if (source == "OPT")
    {
        return PT_Source_Optical;
    }
    else if (source == "COAX")
    {
        return PT_Source_Coaxial;
    }
    else
    {
        logDebugP("[ERROR] Unbekannte Quelle: %s", source);
        //return -1; // Fehlerwert
    }
    return 99; // Fehlerwert
}


/*---------------------------------------------------------------------------------------------------
                      Funktion zur Verarbeitung empfangener UART-Kommandos
 ---------------------------------------------------------------------------------------------------*/
void ArylicUART::processReceivedUARTCommand(const String commandType, const String commandValue)
{
    // Logik zum Verarbeiten der UART-Kommandos vom ArlyicAmp
    // string currentSource;
    if (commandType == "SRC")
    {
        string_currentSource = commandValue;
        icurrentSource = sourceStringToInt(string_currentSource);
        logDebugP("[INFO] Quelle aktualisiert: %s", string_currentSource);
        logDebugP("[INFO] Quelle aktualisiert int: %d", icurrentSource);
    }
    else if (commandType == "VOL")
    {
        currentVolume = commandValue.toInt();
        logDebugP("[INFO] Lautstärke aktualisiert:  %d", currentVolume);
    }
    else if (commandType == "MUT")
    {
        muteStatus = (bool)commandValue.toInt();
        logDebugP("[INFO] Mute Status:  %d", muteStatus);
    }
    else if (commandType == "BAS")
    {
        currentBassTone = commandValue.toInt();
        logDebugP("[INFO] Bass aktualisiert:  %d", currentBassTone);
    }
    else if (commandType == "TRE")
    {
        currentTrebleTone = commandValue.toInt();
        logDebugP("[INFO] Treble aktualisiert:  %d", currentTrebleTone);
    }
    else if (commandType == "MID")
    {
        currentMidTone = commandValue.toInt();
        logDebugP("[INFO] Mid aktualisiert:  %d", currentMidTone);
    }
    else if (commandType == "LED")
    {
        if (commandValue == "1;")
        {
            ledStatus = true;
            logDebugP("LED ON");
        }
        else if (commandValue == "0;")
        {
            ledStatus = false;
            logDebugP("LED OFF");
        }
    }
    else if (commandType == "BTC")
    {
        if (commandValue == "1;")
        {
            bluetoothConnected = true;
            logDebugP("Bluetooth Connected");
        }
        else if (commandValue == "0;")
        {
            bluetoothConnected = false;
            logDebugP("Bluetooth Disconnect");
        }
    }
    else if (commandType == "VBS")
    {
        if (commandValue == "1;")
        {
            virtualBassEnabled = true;
            logDebugP("virtualBass VBS ON");
        }
        else if (commandValue == "0;")
        {
            virtualBassEnabled = false;
            logDebugP("virtualBass VBS OFF");
        }
    }
    else if (commandType == "BEP")
    {
        if (commandValue == "1;")
        {
            beepEnabled = true;
            logDebugP("BEEP ON");
        }
        else if (commandValue == "0;")
        {
            beepEnabled = false;
            logDebugP("BEEP OFF");
        }
    }
    else if (commandType == "STA")
    {
        processSTACommand(commandValue);
        logDebugP("commandValue: %s", commandValue);
    }
}

void ArylicUART::processSTACommand(const String commandValue)
{
    // Beispiel: NET,0,33,-2,0,1,1,1,1,0
    // Zerlege die empfangenen Daten anhand des Trennzeichens ','
    // STA
    // Device status summary, and the response message {states} will consist with: 
    // current source,mute,volume,treble,bass,net,internet,playing,led,upgrading.

    std::vector<String> statusParts;
    int startIndex = 0;
    int separatorIndex = commandValue.indexOf(',');

    while (separatorIndex != -1)
    {
        statusParts.push_back(commandValue.substring(startIndex, separatorIndex));
        startIndex = separatorIndex + 1;
        separatorIndex = commandValue.indexOf(',', startIndex);
    }
    statusParts.push_back(commandValue.substring(startIndex)); // Letzter Teil

    // Überprüfen, ob genügend Daten vorhanden sind
    if (statusParts.size() < 10)
    {
        logDebugP("[ERROR] Ungültige STA-Daten: %s", commandValue);
        return;
    }

    // Werte zuweisen
     string_currentSource = statusParts[0];
     icurrentSource = sourceStringToInt(string_currentSource);

     muteStatus = statusParts[1].toInt();
     currentVolume = statusParts[2].toInt();
     currentTrebleTone = statusParts[3].toInt();
     currentBassTone = statusParts[4].toInt();
     netStatus = statusParts[5].toInt();
     internetStatus = statusParts[6].toInt();
     playingStatus = statusParts[7].toInt();
     ledStatus = statusParts[8].toInt();
     upgradingStatus = statusParts[9].toInt();

    // Debug-Ausgabe
    logDebugP("[STA] Quelle: %s, Quelle int: %d, Mute: %d, Lautstärke: %d, Treble: %d, Bass: %d, Net: %d, Internet: %d, Playing: %d, LED: %d, Upgrading: %d",
              string_currentSource, icurrentSource, muteStatus, currentVolume, currentTrebleTone, currentBassTone, netStatus, internetStatus, playingStatus, ledStatus, upgradingStatus);

}

ArylicUART openknxArylicUARTModule;
