

#ifdef BOARD_ARYLIC_CONNECTOR_BOARD

#define DEVICE_ID "ArylicConnector_V0"

#define PROG_LED_PIN 21
#define PROG_LED_PIN_ACTIVE_ON HIGH
#define PROG_BUTTON_PIN 22
#define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
#define SAVE_INTERRUPT_PIN 20
#define KNX_SERIAL Serial1
#define KNX_UART_RX_PIN 1
#define KNX_UART_TX_PIN 0


// Serial is the USB serial port
// The RP2040 provides two hardware-based UARTS with configurable pin selection.
// Serial1 is UART0 --> KNX
// Serial2 is UART1 --> frei

#define ArylicUARTPORT Serial2 // Serial2 = UART1 //auto& ArylicUART = Serial1; //das geht auch als Namensgeber
//#define ARYLIC_TX_PIN 6        // UART1 TX mit Amp RX verbinden //GP4
//#define ARYLIC_RX_PIN 7        // UART1 RX mit Amp TX verbinden //GP5
#define ARYLIC_TX_PIN	11      // UART1 TX mit Amp RX verbinden //GP8
#define ARYLIC_RX_PIN	12      // UART1 RX mit Amp TX verbinden //GP9
#define BAUD_ARLYIC 115200 // Baudrate für Arylic UART

#endif