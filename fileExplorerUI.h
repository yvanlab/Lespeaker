#ifndef fileManagerUI_h
#define fileManagerUI_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

#ifdef ESP32
#include <WebServer.h>
#include <esp_wifi.h>
//#include <HTTPUpdateServer.h>
#else
#include <ESP8266WebServer.h>
#endif

#include "basemanager.h"

class FileExplorerUI: public BaseManager {

public:
	FileExplorerUI(uint8_t pinLed, WebServer *server) : BaseManager (pinLed){
		_server = server;
	};

	void File_Upload();
	void handleFileUpload();
	void HomePage();
	void SD_file_download(String filename);
	void SD_dir();
	String printDirectory(const char * dirname, uint8_t levels);
	void File_Stream();
	void SD_file_stream(String filename);
	void File_Delete();
	void SD_file_delete(String filename);

	String file_size(int bytes);


	String webpage;
	boolean SD_present = true;

	String 			_currentDirectory;

	WebServer        *_server;
};

#endif
