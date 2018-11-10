#include "main.h"
//#include "SPIFFS.h"*
#include "myAudioOutputI2S.h"

#include "fileExplorerUI.h"



SettingManager *settingMger; //(pinLed);
WifiManager *wifiMger; //(pinLed, &smManager);
ActionManager *actionMger; //(pinLed)

AudioManager *audioMger;

FlashLed *flLedControl;
FlashLed *flLedSystem;

FileManager *fileMger; //(pinLed);*/
FileExplorerUI *fileExplorer;

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

/*#define SOUND_INPUT_TYPE_SD 0
 #define SOUND_INPUT_TYPE_URL 1*/

ActionManager::SPEAKER_MODE previousMode;

/*
 bool handleFileRead() { // send the right file to the client (if it exists)
 Serial.println("handleFileRead: ");
 String path = "/lespeaker.html";
 //if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
 String contentType = "text/html";            // Get the MIME type
 if (SPIFFS.exists(path)) {                            // If the file exists
 File file = SPIFFS.open(path, "r");                 // Open it
 size_t sent = wifiMger->getServer()->streamFile(file, contentType); // And send it to the client
 file.close();                                       // Then close the file again
 return true;
 }
 Serial.println("\tFile Not Found");
 return false;                                         // If the file doesn't exist, return false
 }
 */
void startWiFiserver() {
	if (wifiMger->begin(IPAddress(MODULE_IP), MODULE_NAME, MODULE_MDNS,
	MODULE_MDNS_AP) == WL_CONNECTED) {
		//wifiMger->getServer()->on("/", dataPage);
		wifiMger->getServer()->onNotFound(dataPage);
	}
	wifiMger->getServer()->on("/status", dataJson);
	wifiMger->getServer()->on("/setting", dataPage);

	wifiMger->getServer()->on("/sd",       std::bind(&FileExplorerUI::HomePage, fileExplorer ));
/*	wifiMger->getServer()->on("/download", File_Download);
	wifiMger->getServer()->on("/upload",   File_Upload);*/
	wifiMger->getServer()->on("/upload",  HTTP_POST,[](){ wifiMger->getServer()->send(200);}, std::bind(&FileExplorerUI::handleFileUpload, fileExplorer ));
	//wifiMger->getServer()->on("/stream",   File_Stream);
	wifiMger->getServer()->on("/del",      std::bind(&FileExplorerUI::File_Delete, fileExplorer ));
	wifiMger->getServer()->on("/dir",      std::bind(&FileExplorerUI::SD_dir, fileExplorer ));

	wifiMger->getServer()->on("/setData", setData);
	Serial.println("startWiFiserver end");
	Serial.println(wifiMger->toString(STD_TEXT));
}

void setup(void) {
	Serial.begin(115200);
	DEBUGLOGF("Frq : %d \n", ESP.getCpuFreqMHz()); DEBUGLOGF("Free memory : %d \n", ESP.getFreeHeap()); DEBUGLOGF("SDK Version : %d \n", ESP.getSdkVersion());

	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_GREEN_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);
	digitalWrite(LED_RED_PIN, LOW);
	digitalWrite(LED_GREEN_PIN, LOW);
	digitalWrite(LED_BLUE_PIN, LOW);

	flLedSystem = new FlashLed(0);
	flLedSystem->startLed(LED_RED_PIN, 5);
	flLedControl = new FlashLed(1);
	DEBUGLOGF("flLedControl \n");

	settingMger = new SettingManager(pinLed);
	wifiMger 	= new WifiManager(pinLed, settingMger);
	fileMger 	= new FileManager(pinLed);
	fileExplorer= new FileExplorerUI(pinLed,wifiMger->getServer());

	audioMger	= new AudioManager(pinLed);


	/*if (!SPIFFS.begin(true)) {
		Serial.println("An Error has occurred while mounting SPIFFS");
		return;
	}*/

	//delay(5000);
	settingMger->readData();
	DEBUGLOG("");DEBUGLOG(settingMger->toString(STD_TEXT));
	actionMger = new ActionManager(pinLed,
			(ActionManager::SPEAKER_MODE) settingMger->mode,
			(ActionManager::SPEAKER_SOURCE) settingMger->source);
	audioMger->setVolume(settingMger->volume);

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

	/*mtTimer.onTimerAction(std::bind(&FlashLed::flashCallback,&flLedControl));*/
	mtTimer.begin();
	mtTimer.setCustomMS(3000); //10s*/

#ifdef MCPOC_TEST
	Serial.println("Testing device connections...");
#endif
	flLedSystem->startFlashLed(200);
	fileMger->begin();
	//m_InputType = settingMger->input;

	audioMger->startNewSound("/init.mp3", ActionManager::SOURCE_MICROSD);
	/*if (settingMger->source == ActionManager::SOURCE_MICROSD) {
		fileMger->loadPlayList(FileManager::PERIOD_SOIR,
				FileManager::CONFIG_MSI);
	} else {
		fileMger->loadPlayList(FileManager::PERIOD_SOIR,
				FileManager::CONFIG_RADIO);
	}*/
	flLedSystem->stopFlashLed();
	flLedSystem->stopLed();

	//mtTimer.onTimerAction(std::bind(&AudioManager::handle, audioMger));

	if (actionMger->getMode() == ActionManager::MODE_VOLUME) {
		flLedControl->startLed(LED_GREEN_PIN, 5);
	} else {
		flLedControl->startLed(LED_BLUE_PIN, 5);
	}
	actionMger->setActionForced(ActionManager::WAKE_UP);
	//pinMode(21,INPUT_PULLUP);

}

/*
 Matin         00:00 > 11:00
 Midi          11:00 > 13:00
 apres-midi    13:00 > 18:00
 Soir          18:00 > 23:59

 annonce
 Musique local/Internet


 */
FileManager::PERIOD_TYPE getDayPeriod() {
	if (wifiMger->getHourManager()->isNight()) {
		DEBUGLOGF("FileManager::PERIOD_SOIR [%d] \n", FileManager::PERIOD_SOIR);
		return FileManager::PERIOD_SOIR;
	} else {
		DEBUGLOGF("FileManager::PERIOD_MATIN [%d] \n", FileManager::PERIOD_MATIN);
		return FileManager::PERIOD_MATIN;
	}
}

uint_fast32_t lastms;
bool _someOneHere = true;

String st_prev;

void loop(void) {

	wifiMger->handleClient();
	actionMger->handle(_someOneHere);
	flLedControl->handle();
	audioMger->handle();

	ActionManager::SPEAKER_ACTION action = actionMger->getAction();

	String lAction = actionMger->toString(STD_TEXT);
	if (st_prev != lAction) {
		st_prev = lAction;
		Serial.printf("READ for %d ms %s ...\n", lastms, lAction.c_str());
	}

	if (actionMger->isModeChanged() || action == ActionManager::WAKE_UP) {
		if (actionMger->getMode() == ActionManager::MODE_VOLUME) {
			flLedControl->startLed(LED_GREEN_PIN, 5);
		} else {
			flLedControl->startLed(LED_BLUE_PIN, 5);
		}
	}

	if (actionMger->isSourceChanged()) {
		settingMger->source = actionMger->getSource();
		DEBUGLOGF("Source changed [%d]\n",settingMger->source);
		audioMger->stopSound();

	}

	//ACTION_NONE,VOLUME_UP,VOLUME_DOWN,SELECTION_NEXT,SELECTION_PREVIOUS,SWITH_OFF};
	switch (action) {
	case ActionManager::ACTION_NONE:
		break;
	case ActionManager::VOLUME_UP:
		flLedControl->startFlashLed(100);
		if (settingMger->volume < 100) {
			settingMger->volume++;
			audioMger->setVolume(settingMger->volume);
		}
		DEBUGLOGF("Volume up [%d]\n",settingMger->volume);
		break;
	case ActionManager::VOLUME_DOWN:
		if (settingMger->volume > 0) {
			settingMger->volume--;
			audioMger->setVolume(settingMger->volume);
			flLedControl->startFlashLed(100);
		}
		DEBUGLOGF("Volume down [%d]\n",settingMger->volume);
		break;
	case ActionManager::SELECTION_NEXT:
		flLedControl->startFlashLed(100);
		audioMger->startNewSound(fileMger->getNextFile(), settingMger->source);
		DEBUGLOGF("Selection next\n");

		break;
	case ActionManager::SELECTION_PREVIOUS:
		flLedControl->startFlashLed(100);
		audioMger->startNewSound(fileMger->getPreviousFile(), settingMger->source);
		DEBUGLOGF("Selection previous\n");
		break;
	case ActionManager::SWITH_OFF:
		DEBUGLOGF("SWITH_OFF\n");
		flLedControl->startLed(LED_RED_PIN, 64, 5000);
		settingMger->mode = actionMger->getMode();
		settingMger->writeData();
		audioMger->startNewSound("/close.mp3", ActionManager::SOURCE_MICROSD);
		break;
	case ActionManager::WAKE_UP: {
		flLedControl->startFlashLed(100);
		DEBUGLOGF("WAKE_UP\n");
		// load annonce
		fileMger->loadPlayList(getDayPeriod(), FileManager::CONFIG_ANE);
		audioMger->startNewSound(fileMger->getNextFile(), ActionManager::SOURCE_MICROSD);
		//startNewSound(fileMger->getNextFile(), m_InputType);
		break;
	}
	case ActionManager::SELECTION_CHAIN:
		if (!audioMger->isRunning()) {
			flLedControl->startFlashLed(100);
			if (settingMger->source == ActionManager::SOURCE_MICROSD)
				fileMger->loadPlayList(getDayPeriod(), FileManager::CONFIG_MSI);
			else
				fileMger->loadPlayList(getDayPeriod(),
						FileManager::CONFIG_RADIO);

			DEBUGLOGF("SELECTION_CHAIN\n");
			audioMger->startNewSound(fileMger->getNextFile(), settingMger->source);
			//startNewSound("http://mp3lg3.tdf-cdn.com/9146/lag_103325.mp3", SOUND_INPUT_TYPE_URL);
		}
		break;

	}

	if (audioMger->isRunning()) {
		if (millis() - lastms > 1000) {
			lastms = millis();
			//Serial.printf("READ for %d ms %s ...\n", lastms, actionMger->toString(STD_TEXT).c_str());
			;

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
	if (c == 'P') {
		_someOneHere = true;
		Serial.println(c);
	}

	if (c == 'N') {
		_someOneHere = false;
		Serial.println(c);
	}

	if (c == 'R') {
		settingMger->source = ActionManager::SOURCE_RADIO;
		Serial.println(c);
	}
	if (c == 'S') {
		settingMger->source = ActionManager::SOURCE_MICROSD;
		Serial.println(c);
	}
	/*if (c=='M'){
	 pinMode(17,OUTPUT);
	 digitalWrite(17, LOW);
	 Serial.println(c);
	 }
	 if (c=='Z'){
	 pinMode(17,OUTPUT);
	 digitalWrite(17, HIGH);
	 Serial.println(c);
	 }*/

	//DEBUGLOGF("capteur %d\n",digitalRead(21));
	//if (c != 0) Serial.print(c);
	if (mtTimer.is1SPeriod()) {
		//DEBUGLOG("is1SPeriod ");
		//digitalWrite(BUILTIN_LED, mtTimer.is1SFrequence());
		//DEBUGLOGF("is wifi connected %d %d\l",millis(),WiFi.isConnected());

	}

	if (mtTimer.is5MNPeriod()) {
		if (!WiFi.isConnected()) {
			ESP.restart();
		}
	}

	mtTimer.clearPeriod();
}
