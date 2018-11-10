#include "audioManager.h"
#include "actionManager.h"

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2)-1]=0;
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
  Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}






void AudioManager::handle() {

	//if (stopHandle) return;
	//DEBUGLOGF("handle");
	if (mp3 != NULL && mp3->isRunning()) {
		if (!mp3->loop())
			mp3->stop();
	}
}

void AudioManager::stopSound() {
	//stopHandle = true;
	if (mp3 != NULL && mp3->isRunning()) {
		mp3->stop();
		delay(250);
	}
}

/*float AudioManager::buildGain() {
 return (float)(settingMger->volume);
 }*/

void AudioManager::startNewSound(String link, uint8_t InputType) {
	DEBUGLOGF("Before stop...Free mem=%d\n", ESP.getFreeHeap());
	stopSound();
	boolean res = false;
	if (file != NULL) {
		delete file;
		file = NULL;
	}
	if (buff != NULL) {
		delete buff;
		buff = NULL;
	}
	if (InputType == ActionManager::SOURCE_MICROSD) {
		file = new AudioFileSourceSD(link.c_str());
		res = mp3->begin(file, out);
	} else if (InputType == ActionManager::SOURCE_RADIO) {
		 file = new AudioFileSourceHTTPStream(link.c_str());
		 //((AudioFileSourceHTTPStream)(file))->SetReconnect(3,500);
		 /*(AudioFileSourceICYStream)file->SetReconnect(3,500);
		  file->RegisterMetadataCB(MDCallback, (void*)"ICY");*/
		  buff = new AudioFileSourceBuffer(file, 4096);
		  //buff->RegisterStatusCB(StatusCallback, (void*)"buffer");*/
		/* file = new AudioFileSourceICYStream(link.c_str());
		  buff = new AudioFileSourceBuffer(file, 8192);*/
		  //mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
		  res = mp3->begin(buff, out);
	}
	//boolean res = mp3->begin(file, out);
	//out->SetGain(buildGain());
	DEBUGLOGF("after stop...Free mem=%d\n", ESP.getFreeHeap());
	DEBUGLOGF("Start playing [%s],%d,%d\n",link.c_str(),InputType, res);
	//stopHandle = false;
}

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
