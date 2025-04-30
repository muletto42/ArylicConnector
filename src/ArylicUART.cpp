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
}

void ArylicUART::setup()
{
    _serial.setTX(ARYLIC_TX_PIN);
    _serial.setRX(ARYLIC_RX_PIN);
    _serial.begin(BAUD_ARLYIC);
}

void ArylicUART::sendRawCommandToArylic(const String &command)
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
        else
        {
            currentVolume--;
        }
        setVolume(currentVolume);
        logDebugP("setVolume: %d", currentVolume);
    }
    break;
    case APP_Kovolume_dec: // Decrease --
    {
        if (KoAPP_volume_inc.value(DPT_Step))
        {
            currentVolume++;
        }
        else
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
        muteMode = KoAPP_mute_onoff.value(DPT_Switch);
        setMute(muteMode);
        logDebugP("MuteMode: %d", muteMode);
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

/*---------------------------------------------------------------------------------------------------
                      Funktion zur Verarbeitung empfangener UART-Kommandos
 ---------------------------------------------------------------------------------------------------*/
void ArylicUART::processReceivedUARTCommand(const String &commandType, const String &commandValue)
{
    // Logik zum Verarbeiten der UART-Kommandos vom ArlyicAmp
    // string currentSource;
    if (commandType == "SRC")
    {
        // currentSource = commandValue;
        logDebugP("[INFO] Quelle aktualisiert: %s", commandValue);
    }
    else if (commandType == "VOL")
    {
        currentVolume = commandValue.toInt();
        logDebugP("[INFO] Lautstärke aktualisiert:  %d", currentVolume);
    }
    else if (commandType == "MUT")
    {
        muteMode = (bool)commandValue.toInt();
        logDebugP("[INFO] Mute Status:  %d", muteMode);
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
            logDebugP("LED ON");
            // digitalWrite(LED_PIN, HIGH);
            Serial.println("LED eingeschaltet");
        }
        else if (commandValue == "0;")
        {
            logDebugP("LED OFF");
            // digitalWrite(LED_PIN, LOW);
            Serial.println("LED ausgeschaltet");
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
}

ArylicUART openknxArylicUARTModule;
