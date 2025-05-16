
#ifdef BOARD_ARYLIC_CONNECTOR_BOARD

    #define DEVICE_ID "ArylicConnector_V2"
    #define HARDWARE_NAME "ARC_CON"
    #define DEVICE_NAME "ARYLIC CONNECTOR"

    #define INFO_LED_PIN 15
    #define INFO_LED_PIN_ACTIVE_ON HIGH
    #define PROG_LED_PIN 14
    #define PROG_LED_PIN_ACTIVE_ON HIGH
    #define PROG_BUTTON_PIN 10
    #define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
    #define SAVE_INTERRUPT_PIN 11
    #define KNX_SERIAL Serial1
    #define KNX_UART_RX_PIN 13
    #define KNX_UART_TX_PIN 12


    // Serial is the USB serial port
    // The RP2040 provides two hardware-based UARTS with configurable pin selection.
    // Serial1 is UART0 --> KNX
    // Serial2 is UART1 --> frei

    #define ArylicUARTPORT Serial2 // Serial2 = UART1 //auto& ArylicUART = Serial1; //das geht auch als Namensgeber
    #define ARYLIC_TX_PIN	8      // UART1 TX mit Amp RX verbinden //GP8
    #define ARYLIC_RX_PIN	9      // UART1 RX mit Amp TX verbinden //GP9

    #define BAUD_ARLYIC 115200 // Baudrate für Arylic UART


    #define OPENKNX_SWA_CHANNEL_COUNT 2
    #define OPENKNX_SWA_SET_PINS 3, 18
    #define OPENKNX_SWA_RESET_PINS 2, 19
    #define OPENKNX_SWA_SET_ACTIVE_ON HIGH
    #define OPENKNX_SWA_RESET_ACTIVE_ON HIGH
    #define OPENKNX_SWA_BISTABLE_IMPULSE_LENGTH 30

    #define OPENKNX_SWA_GPIO_OUTPUT_OFFSET 0x0100
    #define OPENKNX_SWA_GPIO_OUTPUT_ACTIVE_ON HIGH
    #define OPENKNX_SWA_GPIO_INPUT_OFFSET 0x0108
    #define OPENKNX_SWA_GPIO_INPUT_ACTIVE_ON LOW



#endif