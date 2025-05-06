#pragma once

#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                            (time & 0x3FFF) * 3600000 ) : 0 )
#define PT_Source_network 0
#define PT_Source_bluetooth 1
#define PT_Source_USBDAC 2
#define PT_Source_linein 3
#define PT_Source_Optical 4
#define PT_Source_Coaxial 5
#define PT_Source_ERROR 99
//--------------------Allgemein---------------------------
#define MAIN_OpenKnxId 0xAF
#define MAIN_ApplicationNumber 0x00
#define MAIN_ApplicationVersion 0x10
#define MAIN_OrderNumber "ArylicConnector"
#define MAIN_ParameterSize 2
#define MAIN_MaxKoNumber 9


#define APP_Volume		0x0000
#define APP_Volume_Shift	1
#define APP_Volume_Mask	0x007F
// Offset: 0, Size: 7 Bit, Text: Lautstärke
#define ParamAPP_Volume ((uint32_t)((knx.paramByte(APP_Volume) >> APP_Volume_Shift) & APP_Volume_Mask))
#define APP_Source		0x0001
#define APP_Source_Shift	1
#define APP_Source_Mask	0x007F
// Offset: 1, Size: 7 Bit, Text: Quelle
#define ParamAPP_Source ((uint32_t)((knx.paramByte(APP_Source) >> APP_Source_Shift) & APP_Source_Mask))
#define APP_mute		0x0000
// Offset: 0, BitOffset: 7, Size: 1 Bit, Text: Mute
#define ParamAPP_mute knx.paramBit(APP_mute, 7)
#define APP_daynight		0x0001
// Offset: 1, BitOffset: 7, Size: 1 Bit, Text: Tag/Nacht Objekt
#define ParamAPP_daynight knx.paramBit(APP_daynight, 7)
//!< Number: 1, Text: Lautstärke, Function: Wert
#define APP_Kovolume_value 1
#define KoAPP_volume_value knx.getGroupObject(APP_Kovolume_value)
//!< Number: 2, Text: Lautstärke, Function: Vol++
#define APP_Kovolume_inc 2
#define KoAPP_volume_inc knx.getGroupObject(APP_Kovolume_inc)
//!< Number: 3, Text: Lautstärke, Function: Vol--
#define APP_Kovolume_dec 3
#define KoAPP_volume_dec knx.getGroupObject(APP_Kovolume_dec)
//!< Number: 4, Text: Quelle, Function: Auswahl
#define APP_Kosource 4
#define KoAPP_source knx.getGroupObject(APP_Kosource)
//!< Number: 5, Text: Mute, Function: Mute
#define APP_Komute_onoff 5
#define KoAPP_mute_onoff knx.getGroupObject(APP_Komute_onoff)
//!< Number: 6, Text: Track, Function: PlayPause
#define APP_KoPlayPause 6
#define KoAPP_PlayPause knx.getGroupObject(APP_KoPlayPause)
//!< Number: 7, Text: Track, Function: Stop
#define APP_KoStop 7
#define KoAPP_Stop knx.getGroupObject(APP_KoStop)
//!< Number: 8, Text: Track, Function: next
#define APP_KoNext 8
#define KoAPP_Next knx.getGroupObject(APP_KoNext)
//!< Number: 9, Text: Track, Function: prev
#define APP_KoPrev 9
#define KoAPP_Prev knx.getGroupObject(APP_KoPrev)

