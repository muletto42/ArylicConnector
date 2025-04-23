#define INFO_LED_PIN 13
#define INFO_LED_PIN_ACTIVE_ON HIGH

#define PROG_LED_PIN_ACTIVE_ON 1
#define PROG_LED_PIN 25
#define PROG_BUTTON_PIN 2

#define KNX_UART_TX_PIN 0
#define KNX_UART_RX_PIN 1

// Serial is the USB serial port
 // The RP2040 provides two hardware-based UARTS with configurable pin selection.
 // Serial1 is UART0 --> KNX 
 // Serial2 is UART1 --> frei
 
 #define ArylicUARTPORT Serial2 // Serial2 = UART1 //auto& ArylicUART = Serial1; //das geht auch als Namensgeber
 #define ARYLIC_TX_PIN 6 // UART1 TX mit Amp RX verbinden //GP4 
 #define ARYLIC_RX_PIN 7 // UART1 RX mit Amp TX verbinden //GP5 
//#define ARYLIC_TX			11 // UART1 TX mit Amp RX verbinden //GP8 
//#define ARYLIC_RX	    12 // UART1 RX mit Amp TX verbinden //GP9 




//#ifdef BOARD_ARYLIC_CONNECTOR_BOARD

// #define HARDWARE_NAME "ArylicConnector_CONTROLLERV00.10"

// #define OKNXHW_UP1_CONTROLLER2040
// #include "OpenKNXHardware.h"

// #define INFO_LED_PIN 13
// #define INFO_LED_PIN_ACTIVE_ON HIGH

// #define PROG_LED_PIN_ACTIVE_ON 1
// #define PROG_LED_PIN 25
// #define PROG_BUTTON_PIN 2

// #define KNX_UART_TX_PIN 0
// #define KNX_UART_RX_PIN 1

// #define BTN_ChannelCount 3

// #define THPCHANNEL_A_SCL 29
// #define THPCHANNEL_A_SDA 28
// #define THPCHANNEL_B_SCL 27
// #define THPCHANNEL_B_SDA 26
// #define THPCHANNEL_C_SCL 25
// #define THPCHANNEL_C_SDA 24
// #define THPCHANNEL_D_SCL 23
// #define THPCHANNEL_D_SDA 22
// #define THPCHANNEL_E_SCL 21
// #define THPCHANNEL_E_SDA 20
// #define THPCHANNEL_F_SCL 19
// #define THPCHANNEL_F_SDA 18
// #define THPCHANNEL_G_SCL 17
// #define THPCHANNEL_G_SDA 16
// #define THPCHANNEL_H_SCL 15
// #define THPCHANNEL_H_SDA 14
// #endif