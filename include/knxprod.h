#pragma once

#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                            (time & 0x3FFF) * 3600000 ) : 0 )
//--------------------Allgemein---------------------------
#define MAIN_OpenKnxId 0xFA
#define MAIN_ApplicationNumber 0x02
#define MAIN_ApplicationVersion 0x02
#define MAIN_OrderNumber "ARCCON"
#define MAIN_ParameterSize 3
#define MAIN_MaxKoNumber 30


#define APP_color		0x0000
#define APP_color_Shift	6
#define APP_color_Mask	0x0003
// Offset: 0, Size: 2 Bit, Text: Farbe
#define ParamAPP_color ((uint32_t)((knx.paramByte(APP_color) >> APP_color_Shift) & APP_color_Mask))
#define APP_blink		0x0000
// Offset: 0, BitOffset: 2, Size: 1 Bit, Text: Blinken?
#define ParamAPP_blink knx.paramBit(APP_blink, 2)
#define APP_interval		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Interval
#define ParamAPP_interval ((uint32_t)((knx.paramByte(APP_interval))))
#define APP_Volume		0x0002
#define APP_Volume_Shift	1
#define APP_Volume_Mask	0x007F
// Offset: 2, Size: 7 Bit, Text: Lautstaerke
#define ParamAPP_Volume ((uint32_t)((knx.paramByte(APP_Volume) >> APP_Volume_Shift) & APP_Volume_Mask))
#define APP_Source		0x0000
#define APP_Source_Shift	2
#define APP_Source_Mask	0x0007
// Offset: 0, BitOffset: 3, Size: 3 Bit, Text: Quelle
#define ParamAPP_Source ((uint32_t)((knx.paramByte(APP_Source) >> APP_Source_Shift) & APP_Source_Mask))
//!< Number: 1, Text: LED, Function: Schalten
#define APP_Koonoff 1
#define KoAPP_onoff knx.getGroupObject(APP_Koonoff)
//!< Number: 2, Text: LED, Function: Status
#define APP_Kostate 2
#define KoAPP_state knx.getGroupObject(APP_Kostate)
//!< Number: 10, Text: VOL++, Function: VOL++
#define APP_Kovolume_inc 10
#define KoAPP_volume_inc knx.getGroupObject(APP_Kovolume_inc)
//!< Number: 11, Text: VOL--, Function: VOL--
#define APP_Kovolume_dec 11
#define KoAPP_volume_dec knx.getGroupObject(APP_Kovolume_dec)
//!< Number: 12, Text: Volume, Function: Wert
#define APP_Kovolume_value 12
#define KoAPP_volume_value knx.getGroupObject(APP_Kovolume_value)
//!< Number: 30, Text: Quelle, Function: Dummy
#define APP_Kosource 30
#define KoAPP_source knx.getGroupObject(APP_Kosource)
//!< Number: 20, Text: Dummy, Function: Dummy
#define APP_Komute_onoff 20
#define KoAPP_mute_onoff knx.getGroupObject(APP_Komute_onoff)
//!< Number: 21, Text: Dummy, Function: Dummy
#define APP_KoPlayPause 21
#define KoAPP_PlayPause knx.getGroupObject(APP_KoPlayPause)
//!< Number: 22, Text: Dummy, Function: Dummy
#define APP_KoStop 22
#define KoAPP_Stop knx.getGroupObject(APP_KoStop)
//!< Number: 23, Text: Dummy, Function: Dummy
#define APP_KoNext 23
#define KoAPP_Next knx.getGroupObject(APP_KoNext)


//!< Number: 24, Text: Dummy, Function: Dummy
#define APP_KoPREV 24
#define KoAPP_prev knx.getGroupObject(APP_KoPREV)