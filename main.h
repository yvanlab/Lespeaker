
#ifndef main_h
#define main_h

#include <Arduino.h>


#include <WifiManagerV2.h>
//#include <myTimer.h>
//#include <FlashLed.h>

#ifdef ESP32
#include <HTTPClient.h>
#else
#include <ESP8266HTTPClient.h>
#include <ESP8266Spiram.h>
#endif

//#include <SPI.h>


#include "fileManager.h"
#include "SettingManager.h"
#include "actionManager.h"

#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
//#include "AudioGeneratorWAV.h"
//#include "AudioGeneratorFLAC.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioOutputI2S.h"

#include "networkUI.h"
#include "ActionManager.h"


#define MODEL_VERSION   LE_SPEAKER_VERSION


#define MODULE_NAME     LE_SPEAKER_NAME
#define MODULE_MDNS     LE_SPEAKER_MDNS
#define MODULE_MDNS_AP  LE_SPEAKER_MDNS_AP
#define MODULE_IP       LE_SPEAKER_IP



#define LAPORTE_OUVERTURE_LABEL  1 //"current"

#define  pinLed  LED_BUILTIN


extern SettingManager      *settingMger;
extern WifiManager         *wifiMger;

#ifdef MCPOC_TELNET
//extern RemoteDebug          Debug;
#endif



#endif
