#include "main.h"
//#include "SPIFFS.h"*
#include "myAudioOutputI2S.h"

#include "fileExplorerUI.h"



SettingManager *settingMger;
WifiManager *wifiMger;
ActionManager *actionMger;
AudioManager *audioMger;

FlashLed *flLedControl;
FlashLed *flLedSystem;

FileManager *fileMger;
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


ActionManager::SPEAKER_MODE previousMode;


void viewFile() {
	String filename = wifiMger->getServer()->arg("file");
	if (filename.length()!=0) {
		if (filename.indexOf(".mp3")>0 || filename.indexOf(".MP3")>0) {
			audioMger->startNewSound(filename, ActionManager::SOURCE_MICROSD,settingMger->volume);
		} else {

			File f = SD.open(filename);
			if (!f) {
				DEBUGLOGF("viewFile No TXT [%s]\n",filename.c_str());
			} else {
				DEBUGLOGF("viewFile TXT [%s][%d]\n",filename.c_str(), f.size());
				unsigned char _buffer[250];
				wifiMger->getServer()->sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
				wifiMger->getServer()->sendHeader("Pragma", "no-cache");
				wifiMger->getServer()->sendHeader("Expires", "-1");
				wifiMger->getServer()->setContentLength(CONTENT_LENGTH_UNKNOWN); // *** BEGIN ***
				wifiMger->getServer()->send(200, "text/html", "");
				wifiMger->getServer()->sendContent("<html><body>");
				//wifiMger->getServer()->sendHeader("Content-Length", String(f.size()) );
				//wifiMger->getServer()->send(200, "text/html", "");
				 while (f.available()) {
					 int s = f.read(_buffer, 250);
					 if (s>0) {
						 //String sTmp(_buffer);
						 //sTmp = _buffer;
						 wifiMger->getServer()->sendContent("Fuck"); //send the current buffer
					 	 DEBUGLOGF("%s",_buffer);
					 }
				 }
				 wifiMger->getServer()->sendContent("</body></html>");
				 wifiMger->getServer()->sendContent(""); // *** END 1/2 ***
				 wifiMger->getServer()->client().stop();
				 f.close();
			}

		}
	}
	wifiMger->getServer()->send ( 200, "text/html", "KO man" );
}


void playSound() {
	String filename = wifiMger->getServer()->arg("file");
	if (filename.length()!=0) {
		audioMger->startNewSound(filename, ActionManager::SOURCE_MICROSD,settingMger->volume);
	}
	wifiMger->getServer()->send ( 200, "text/html", "Ok man" );
}

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
	wifiMger->getServer()->on("/upload",  HTTP_POST,[](){ wifiMger->getServer()->send(200);flLedSystem->stopLed();}, std::bind(&FileExplorerUI::handleFileUpload, fileExplorer ));
	//wifiMger->getServer()->on("/stream",   File_Stream);
	wifiMger->getServer()->on("/del",      std::bind(&FileExplorerUI::File_Delete, fileExplorer ));
	wifiMger->getServer()->on("/dir",      std::bind(&FileExplorerUI::SD_dir, fileExplorer ));
	wifiMger->getServer()->on("/play",     viewFile);

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

	audioMger->startNewSound("/init.mp3", ActionManager::SOURCE_MICROSD,settingMger->volume);

	flLedSystem->stopFlashLed();
	flLedSystem->stopLed();


	if (actionMger->getMode() == ActionManager::MODE_VOLUME) {
		flLedControl->startLed(LED_GREEN_PIN, 5);
	} else {
		flLedControl->startLed(LED_BLUE_PIN, 5);
	}
	actionMger->setActionForced(ActionManager::WAKE_UP);
	//pinMode(21,INPUT_PULLUP);

}


FileManager::PERIOD_TYPE getDayPeriod() {
	if (wifiMger->getHourManager()->isNight()) {
		DEBUGLOGF("FileManager::PERIOD_SOIR [%d] \n", FileManager::PERIOD_SOIR);
		return FileManager::PERIOD_SOIR;
	} else if (wifiMger->getHourManager()->isMorning()) {
		DEBUGLOGF("FileManager::PERIOD_MATIN [%d] \n", FileManager::PERIOD_MATIN);
		return FileManager::PERIOD_MATIN;
	} else {
		DEBUGLOGF("FileManager::PERIOD_ENTRE [%d] \n", FileManager::PERIOD_ENTRE);
		return FileManager::PERIOD_ENTRE;
	
	}
}

//uint_fast32_t lastms;
bool _someOneHere = true;

//String st_prev;

ActionManager::SPEAKER_ACTION previousAction = ActionManager::ACTION_NONE;

void loop(void) {

	wifiMger->handleClient();
	actionMger->handle(_someOneHere);
	flLedControl->handle();
	audioMger->handle();

	ActionManager::SPEAKER_ACTION action = actionMger->getAction();

	/*String lAction = actionMger->toString(STD_TEXT);
	if (st_prev != lAction) {
		st_prev = lAction;
		DEBUGLOGF("READ for %d ms %s ...\n", lastms, lAction.c_str());
	}*/

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
		previousAction = ActionManager::CHANGE_SOURCE;
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
		audioMger->startNewSound(fileMger->getNextFile(), settingMger->source,settingMger->volume);
		DEBUGLOGF("Selection next\n");

		break;
	case ActionManager::SELECTION_PREVIOUS:
		flLedControl->startFlashLed(100);
		audioMger->startNewSound(fileMger->getPreviousFile(), settingMger->source,settingMger->volume);
		DEBUGLOGF("Selection previous\n");
		break;
	case ActionManager::SWITH_OFF:
		DEBUGLOGF("SWITH_OFF\n");
		flLedControl->startLed(LED_RED_PIN, 64, 5000);
		settingMger->mode = actionMger->getMode();
		settingMger->writeData();
		audioMger->startNewSound("/close.mp3", ActionManager::SOURCE_MICROSD,settingMger->volume);
		break;
	case ActionManager::WAKE_UP: {
		flLedControl->startFlashLed(100);
		DEBUGLOGF("WAKE_UP\n");
		// load annonce
		fileMger->loadPlayList(getDayPeriod(), FileManager::CONFIG_ANE);
		audioMger->startNewSound(fileMger->getNextFile(), ActionManager::SOURCE_MICROSD,settingMger->volume);
		previousAction = ActionManager::WAKE_UP;
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
			if (previousAction == ActionManager::WAKE_UP || previousAction == ActionManager::CHANGE_SOURCE) {
				audioMger->startNewSound(fileMger->getFile(), settingMger->source,settingMger->volume);
				previousAction = ActionManager::SELECTION_CHAIN;
			}else{
				audioMger->startNewSound(fileMger->getNextFile(), settingMger->source,settingMger->volume);
			}


			//startNewSound("http://mp3lg3.tdf-cdn.com/9146/lag_103325.mp3", SOUND_INPUT_TYPE_URL);
		}
		break;

	}

/*	if (audioMger->isRunning()) {
		if (millis() - lastms > 1000) {
			lastms = millis();
			;

		}
	}
*/

/*
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
	if (c=='M'){
	 pinMode(17,OUTPUT);
	 digitalWrite(17, LOW);
	 Serial.println(c);
	 }
	 if (c=='Z'){
	 pinMode(17,OUTPUT);
	 digitalWrite(17, HIGH);
	 Serial.println(c);
	 }

	 */


	if (mtTimer.is5MNPeriod()) {
		if (!WiFi.isConnected() || wifiMger->getHourManager()->isNextDay()) {
			ESP.restart();
		}
	}



	mtTimer.clearPeriod();
}
