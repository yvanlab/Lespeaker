#include "main.h"

//SdFat sd;

SettingManager *settingMger;//(pinLed);
WifiManager *wifiMger;//(pinLed, &smManager);
ActionManager *actionMger;//(pinLed)
//FlashLed flLed(pinLed);
FileManager *fileMger;//(pinLed);*/


//LedManager          ldManager(pinLed,BLOCKED_MODE);

#ifdef MCPOC_TELNET
RemoteDebug Debug;
#endif

#ifdef MCPOC_TELNET // Not in PRODUCTION
void processCmdRemoteDebug() {
	String lastCmd = Debug.getLastCommand();
	/*  if (lastCmd == "o") {
	 dManager.activateModule(true);
	 } else if (lastCmd == "r") {
	 fpManager.recordFingerPrint(0,"yvan");
	 } else if (lastCmd == "a") {
	 fpManager.activateModule(true);
	 } else if (lastCmd == "restart") {
	 ESP.restart();
	 } else if (lastCmd == "reset") {
	 WiFi.disconnect();
	 }*/
}
#endif

/*AudioGeneratorMP3 *mp3;*/
//AudioFileSourceSD *file;
/*AudioOutputI2SNoDAC *out;
 AudioFileSourceID3 *id3;*/
AudioGeneratorMP3 *mp3 = NULL;
/*AudioFileSourceICYStream *file;
 AudioFileSourceSD *file;*/
AudioFileSource *file = NULL;
//AudioFileSourceBuffer *buff;
//AudioOutputI2SNoDAC *out = NULL;
AudioOutputI2S *out = NULL;
uint8_t *space = NULL;


#define SOUND_INPUT_TYPE_SD 0
#define SOUND_INPUT_TYPE_URL 1

/*
 * 	GPIO2/TX1  D4 - LRCK
 GPIO3/RX0 RX  - DATA
 GPIO15     D8 - BCLK
 *
 */
//uint8_t  space[30000];
void startNewSound(String link, uint8_t InputType) {
	DEBUGLOGF("Before stop...Free mem=%d\n", ESP.getFreeHeap());
	if(mp3!=NULL && mp3->isRunning() ) {
		mp3->stop();
		delay(250);
	}

	if (file != NULL)
		delete file;
	if (InputType == SOUND_INPUT_TYPE_SD) {
		file = new AudioFileSourceSD(link.c_str());
	} else if (InputType == SOUND_INPUT_TYPE_URL) {
		file = new AudioFileSourceICYStream(link.c_str());
	}
	/*if (space == NULL)
		space = (uint8_t *) malloc(29200);*/
	//delay(500);
	//out = new AudioOutputI2SNoDAC();
	if (out == NULL) out = new AudioOutputI2S();//AudioOutputI2S();
	out->SetGain(((float)settingMger->gain*4.0)/100);
	//out->SetGain(1.0);
	//AudioGeneratorMP3(void *space, int size)
	if (mp3 == NULL) mp3 = new AudioGeneratorMP3(/*space, 29200*/);
	//mp3 = new AudioGeneratorMP3();//preallocateSpace,1500);
	boolean res = mp3->begin(file, out);
	DEBUGLOGF("after stop...Free mem=%d\n", ESP.getFreeHeap());
	DEBUGLOGF("Start playing [%s],%d,%d\n",link.c_str(),InputType, res);
	/*  const char *URL="http://streaming.shoutcast.com/80sPlanet?lang=en-US";
	 file = new AudioFileSourceICYStream(URL);
	 file->RegisterMetadataCB(MDCallback, (void*)"ICY");
	 out = new AudioOutputI2SNoDAC();
	 mp3 = new AudioGeneratorMP3();
	 mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
	 mp3->begin(file, out);*/
//delay(1000);
}

void startWiFiserver() {
	if (wifiMger->begin(IPAddress(MODULE_IP), MODULE_NAME, MODULE_MDNS,
			MODULE_MDNS_AP) == WL_CONNECTED) {
		wifiMger->getServer()->on("/", dataPage);
		wifiMger->getServer()->onNotFound(dataPage);
	}
	wifiMger->getServer()->on("/status", dataJson);
	wifiMger->getServer()->on("/setting", dataPage);
	wifiMger->getServer()->on("/setData", setData);
	Serial.println("startWiFiserver end");
	Serial.println(wifiMger->toString(STD_TEXT));
}


void setup(void) {
	//delay(5000);
	//node.setcpufreq(node.CPU160MHZ)
	Serial.begin(115200);//, SERIAL_8N1, 16, 17);
	//Serial.begin(115200);
	delay(500);
	Serial.println("start debuging");
	DEBUGLOGF("Frq : %d \n", ESP.getCpuFreqMHz());
	//system_update_cpu_freq(SYS_CPU_160MHZ);
	DEBUGLOGF("Free memory : %d \n", ESP.getFreeHeap());
	DEBUGLOGF("SDK Version : %d \n", ESP.getSdkVersion());

	settingMger = new SettingManager (pinLed);
	wifiMger = new WifiManager(pinLed, settingMger);
	fileMger = new FileManager(pinLed);
	actionMger = new ActionManager(pinLed);

	//delay(5000);
	settingMger->readData();
	DEBUGLOG("");DEBUGLOG(settingMger->toString(STD_TEXT));
	startWiFiserver();

#ifdef MCPOC_TELNET
	Debug.begin(MODULE_NAME);
	String helpCmd = "l1\n\rl2\n\rl3\n\rrestart\n\rreset\n\r";
	Debug.setHelpProjectsCmds(helpCmd);
	Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
#endif

#ifdef MCPOC_MOCK
	randomSeed(analogRead(0));
#endif

	/*mtTimer.onTimerAction(std::bind(&FlashLed::flashCallback,&flLed));
	 mtTimer.begin(timerFrequence);
	 mtTimer.setCustomMS(3000); //10s*/

#ifdef MCPOC_TEST
	Serial.println("Testing device connections...");
#endif

	fileMger->begin();
	//getNextFile("", "") ;

	pinMode(13, INPUT);
	DEBUGLOGF("D3 : %d\n",digitalRead(13));

	Serial.printf("Sample MP3 playback begins...\n");

	startNewSound("/init.mp3", SOUND_INPUT_TYPE_SD);

	String folder = fileMger->readCfg("soir", "msi");
	fileMger->setCurrentFolder(folder);


}

/*
 Matin         00:00 > 11:00
 Midi          11:00 > 13:00
 apres-midi    13:00 > 18:00
 Soir          18:00 > 23:59

 annonce
 Musique local/Internet


 */
uint_fast32_t lastms;
bool _someOneHere = true;

void loop(void) {

	wifiMger->handleClient();
	actionMger->handle(_someOneHere);
	ActionManager::SPEAKER_ACTION action = actionMger->getAction();
	//ACTION_NONE,VOLUME_UP,VOLUME_DOWN,SELECTION_NEXT,SELECTION_PREVIOUS,SWITH_OFF};
	switch(action) {
		case ActionManager::ACTION_NONE:
			break;
		case ActionManager::VOLUME_UP:
			DEBUGLOGF("Volume up [%d]\n",settingMger->gain);
			if (settingMger->gain<100) {
				settingMger->gain++;
				// 100 --->4.0
				//  50 ---> X
				out->SetGain(((float)settingMger->gain*4.0)/100.0);
			}
			break;
		case ActionManager::VOLUME_DOWN:
			DEBUGLOGF("Volume down [%d]\n",settingMger->gain);
			if (settingMger->gain>0) {
				settingMger->gain--;
				out->SetGain(((float)settingMger->gain*4.0)/100.0);
			}
			break;
		case ActionManager::SELECTION_NEXT:
			startNewSound(fileMger->getNextFile(), SOUND_INPUT_TYPE_SD);
			DEBUGLOGF("Selection next\n");
			break;
		case ActionManager::SELECTION_PREVIOUS:
			startNewSound(fileMger->getPreviousFile(), SOUND_INPUT_TYPE_SD);
			DEBUGLOGF("Selection previous\n");
			break;
		case ActionManager::SWITH_OFF:
			DEBUGLOGF("SWITH_OFF\n");
			startNewSound("/close.mp3", SOUND_INPUT_TYPE_SD);
			break;
		case ActionManager::WAKE_UP:{
			DEBUGLOGF("WAKE_UP\n");
			String dayPeriod;
			if (wifiMger->getHourManager()->isNight()) {dayPeriod = "soir";}
			else {dayPeriod = "matin";}
			String Mfolder = fileMger->readCfg(dayPeriod.c_str(), "ane");
			fileMger->setCurrentFolder(Mfolder);
			startNewSound(fileMger->getNextFile(), SOUND_INPUT_TYPE_SD);
			Mfolder = fileMger->readCfg(dayPeriod.c_str(), "msi");
			fileMger->setCurrentFolder(Mfolder);
			break;
		}
		case ActionManager::SELECTION_CHAIN:
			if (!mp3->isRunning()) {
				DEBUGLOGF("SELECTION_CHAIN\n");
				//startNewSound(fileMger->getNextFile(), SOUND_INPUT_TYPE_SD);
				startNewSound("http://mp3lg3.tdf-cdn.com/9146/lag_103325.mp3", SOUND_INPUT_TYPE_URL);
			}
			break;

					
	}

	if (mp3->isRunning()) {
		 if (!mp3->loop()) mp3->stop();
	
		if (millis() - lastms > 1000) {
			lastms = millis();
			//Serial.printf("READ for %d ms %d ...\n", lastms, ESP.getFreeHeap());
			//actionMger->toString(STD_TEXT);

		}
	}

	/*char data [21];
	 int number_of_bytes_received;

	 if(Serial.available() > 0)
	 {
	   number_of_bytes_received = Serial.readBytesUntil (13,data,20); // read bytes (max. 20) from buffer, untill <CR> (13). store bytes in data. count the bytes recieved.
	   data[number_of_bytes_received] = 0; // add a 0 terminator to the char array
	   Serial.println(data);
	 }

	/*
	while(Serial.available())
	  Serial.read();
*/

	char c = Serial.read();
	if (c=='P'){
		_someOneHere = true;
		Serial.println(c);
	}

	if (c=='N'){
		_someOneHere = false;
		Serial.println(c);
	}
	//if (c != 0) Serial.print(c);

	/*if (mtTimer.is1SPeriod()) {
		DEBUGLOG("is1SPeriod ");
		if (!digitalRead(D3)) {
		 //mp3->stop();
		 //startNewSound(readCfg("matin", "url"), SOUND_INPUT_TYPE_URL);


		 }
	}*/

	/*if (mtTimer.is5MNPeriod()) {

		if (!WiFi.isConnected()) {
			ESP.restart();
		}
	}*/

	//mtTimer.clearPeriod();
}
