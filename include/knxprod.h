
#define MAIN_OpenKnxId 0xFA
#define MAIN_ApplicationNumber 0x01
#define MAIN_ApplicationVersion 0x01
#define MAIN_OrderNumber "TEST"
#define MAIN_ParameterSize 2
#define MAIN_MaxKoNumber 2

#define APP_color		0x0000
#define APP_color_Shift	6
#define APP_color_Mask	0x0003
// Offset: 0, Size: 2 Bit, Text: Farbe
#define ParamAPP_color ((uint)((knx.paramByte(0) >> APP_color_Shift) & APP_color_Mask))
#define APP_blink		0x0000
// Offset: 0, BitOffset: 2, Size: 1 Bit, Text: Blinken?
#define ParamAPP_blink knx.paramBit(0, 2)
#define APP_interval		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Interval
#define ParamAPP_interval ((uint)((knx.paramByte(1))))
//!< Number: 1, Text: LED, Function: Schalten
#define APP_Koonoff 1
#define KoAPP_onoff knx.getGroupObject(1)
//!< Number: 2, Text: LED, Function: Status
#define APP_Kostate 2
#define KoAPP_state knx.getGroupObject(2)


#define KoAPP_Volume_INC 10 // knx.getGroupObject(10) // Increase ++
#define KoAPP_Volume_DEC 11 // knx.getGroupObject(11) // Decrease --
#define KoAPP_Volume_SET 12 // knx.getGroupObject(12) // SET value

#define KoAPP_Mute_onoff 20 // knx.getGroupObject(20)
#define KoAPP_PlayPause 21 //knx.getGroupObject(21)
#define KoAPP_stop 22 //knx.getGroupObject(22)
#define KoAPP_next 23 //knx.getGroupObject(23)

#define KoAPP_source 30 //knx.getGroupObject(30)
