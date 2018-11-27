
#include "main.h"

String getJson()
{
	DEBUGLOG("getJson");
	String tt("{\"module\":{");
	tt += "\"nom\":\"" + String(MODULE_NAME) +"\"," ;
	tt += "\"version\":\"" + String(MODEL_VERSION) +"\"," ;
	tt += "\"status\":\"" + String(STATUS_PERIPHERIC_WORKING) +"\"," ;
	tt += "\"uptime\":\"" + NTP.getUptimeString() +"\"," ;
	tt += "\"build_date\":\""+ String(__DATE__" " __TIME__)  +"\"},";
	tt += "\"setting\":{" + settingMger->toString(JSON_TEXT)  + "},";
	tt += "\"sound\":\"" + fileMger->getFile() +"\"," ;
	tt += "\"LOG\":["+ wifiMger->log(JSON_TEXT)  + "," + settingMger->log(JSON_TEXT)+"]";
	tt += "}";
	return tt;
}


void dataJson() {
	flLedSystem->startLed( LED_RED_PIN, 2);
	wifiMger->getServer()->send ( 200, "text/json", getJson() );
	digitalWrite ( pinLed, HIGH );
	flLedSystem->stopLed();
}

void setData(){
	flLedSystem->startLed( LED_RED_PIN, 2);
	DEBUGLOG("setData");
	boolean bModified = false;
	for (int i=0; i< wifiMger->getServer()->args() ; i++)
		DEBUGLOGF("setData : Arg [%d][%s]=[%s]\n", i, wifiMger->getServer()->argName(i).c_str(), wifiMger->getServer()->arg(i).c_str());


	String str = wifiMger->getServer()->arg("volume");
	if (str.length()>0) {
		DEBUGLOGF("setData : Volume [%s]\n", str);
		settingMger->volume = atoi(str.c_str());
		audioMger->setVolume(settingMger->volume);
		bModified = true;
	}
	str = wifiMger->getServer()->arg("source");
	if (str.length()>0) {
		DEBUGLOGF("setData : source [%s]\n", str);
		settingMger->source= atoi(str.c_str());
		if (str == "1")
			actionMger->setSourceForce(ActionManager::SOURCE_RADIO);
		else
			actionMger->setSourceForce(ActionManager::SOURCE_MICROSD);
		bModified = true;
	}

	str = wifiMger->getServer()->arg("mode");
	if (str.length()>0) {
		DEBUGLOGF("setFData : mode [%s]\n", str);
		settingMger->mode= atoi(str.c_str());
		if (str == "sel")
			actionMger->setModeForce(ActionManager::MODE_SELECTION);
		else
			actionMger->setModeForce(ActionManager::MODE_VOLUME);
		bModified = true;
	}

	str = wifiMger->getServer()->arg("action");
	if (str.length()>0) {
		DEBUGLOGF("setData : action [%s]\n", str);
		//VOLUME_UP=1,VOLUME_DOWN=2,SELECTION_CHAIN=3,SELECTION_NEXT=4,SELECTION_PREVIOUS=5,SWITH_OFF=6,WAKE_UP=7,STOPPED=8
		if (str == "next")
			actionMger->setActionForced(ActionManager::SELECTION_NEXT);
		else if (str == "prev")
			actionMger->setActionForced(ActionManager::SELECTION_PREVIOUS);
		else if (str == "stop")
			actionMger->setActionForced(ActionManager::SWITH_OFF);
		else if (str == "start")
			actionMger->setActionForced(ActionManager::WAKE_UP);

		bModified = true;
	}
	if (bModified)
		settingMger->writeData();
	//dataPage();
	 dataJson();
	flLedSystem->stopLed();
}

const char HTML[] PROGMEM =
		"<!DOCTYPE html>\n<html>\n\n<head>\n    <meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\">\n    <title>lespeaker</title>\n    <script type=\"application/x-javascript\"></script>\n</head>\n\n<body>\n    <h1 style=\"text-align: center;\"><span id=\"modulename\">Module</span>\n      configuration </h1>\n    <div style=\"text-align: center;\">\n        <p>Version : <span id=\"version\">3.0</span></p>\n    </div>\n    <div style=\"text-align: center;\">\n        <p>Date build : <span id=\"builddate\">10/08/1900</span> </p>\n    </div>\n    <div style=\"text-align: center;\">\n        <p>Up time : <span id=\"uptime\">un moment</span> </p>\n    </div>\n    <div style=\"text-align: center\">\n\t\t<p>\n\t\t\t<a href='/sd'>Fichier</a><a href='/credential'>Credentiqals</a>/<a href='/reset'>Wifi Reset</a>/<a href='/restart'>Restart</a>\n\t\t</p>\n\t</div>\n    <hr style=\"margin-top: 51px; margin-left: auto; width: 177px; margin-right: auto;\">\n    <form action=\"/action_page.php\" style=\"height: 57px;\">\n        <div>\n            <div>\n                <h3 style=\"height: 3px;\">Titre </h3>\n                <hr>\n                <p><i><b><span id=\"titre\">Le titreeee</span></b></i> </p>\n                <div>\n                    <h3 style=\"height: 4px;\">Source </h3>\n                    <hr>\n                    <input id=\"msd_id\" onclick=\"changeSetting('source','2')\" name=\"in\" type=\"radio\"> MicroSD\n                    <br>\n                    <input id=\"rad_id\" onclick=\"changeSetting('source','1')\" name=\"in\" type=\"radio\"> Radio \n                </div>\n                <div>\n                    <h3 style=\"height: 3px;\">Periode </h3>\n                    <hr>\n                    <input onclick=\"changeSetting('period','soir')\" name=\"period\" id=\"soir_id\" type=\"radio\" > Soir\n                    <br>\n                    <input onclick=\"changeSetting('period','matin')\" name=\"period\" id=\"matin_id\" type=\"radio\" > Matin \n                </div>\n                <div>\n                    <h3 style=\"height: 3px;\">Action </h3>\n                    <hr>\n                    <input onclick=\"changeSetting('mode','vol')\" name=\"act\" id=\"act_vol_id\" type=\"radio\" > Volume\n                    <br>\n                    <input onclick=\"changeSetting('mode','sel')\" name=\"act\" id=\"act_sel_id\" type=\"radio\" > Selection </div>\n                <div>\n                    <h3 style=\"height: 5px;\">Actions</h3>\n                    <hr>\n                    <input onclick=\"changeSetting('action','stop')\" value=\"Stop\" type=\"button\">\n                    <input onclick=\"changeSetting('action','start')\" value=\"Start\" type=\"button\">\n                    <input onclick=\"changeSetting('action','next')\" value=\"Suivante\" type=\"button\">\n                    <input onclick=\"changeSetting('action','prev')\" value=\"Precedent\" type=\"button\">\n                    <br> Volume\n                    <input onchange=\"changeSetting('volume',this.value)\" id=\"volume\" name=\"volume\" min=\"0\" max=\"30\"  type=\"range\"> </div>\n            </div>\n            <script>\n                function changeSetting(act, val) {\n                    document.getElementById(\"version\").innerHTML = val;\n                    var xhttp = new XMLHttpRequest();\n                    xhttp.onreadystatechange = function() {\n                        if (this.readyState == 4 && this.status == 200) {\n                            update(this.responseText)\n                        }\n                    };\n                    xhttp.open(\"GET\", \"setData?\" + act + \"=\" + val, true);\n                    xhttp.send();\n                };\n\n                function update(responseText) {\n                    var myObj = JSON.parse(responseText);\n                    document.getElementById(\"builddate\").innerHTML =\n                        myObj.module.build_date;\n                    document.getElementById(\"version\").innerHTML =\n                        myObj.module.version;\n                    document.getElementById(\"modulename\").innerHTML =\n                        myObj.module.nom;\n                    document.getElementById(\"uptime\").innerHTML =\n                        myObj.module.uptime;\n\n                    document.getElementById(\"titre\").innerHTML =\n                        myObj.sound;\n\n                    document.getElementById(\"volume\").value = myObj.setting.volume;\n\n                    if (myObj.setting.source == 2){\n                        document.getElementById(\"msd_id\").checked = \"checked\";\n                  \t} else {\n                        document.getElementById(\"rad_id\").checked = \"checked\";\n                  \t\t//document.getElementById(\"msd_id\").checked = \"unchecked\";\n                    };\n                    \n                    if (myObj.setting.period == 1) {\n                        document.getElementById(\"matin_id\").checked = \"checked\";\n                  \t\t//document.getElementById(\"soir_id\").checked = \"unchecked\";\n                    } else {\n                        document.getElementById(\"soir_id\").checked = \"checked\";\n                  \t\t//document.getElementById(\"matin_id\").checked = \"unchecked\";\n                \t};\n                  \t\n                    if (myObj.setting.mode == 1){\n                    \tdocument.getElementById(\"act_vol_id\").checked = \"checked\";\n                      \t//document.getElementById(\"act_sel_id\").checked = \"unchecked\";\n                    }else{\n                        document.getElementById(\"act_sel_id\").checked = \"checked\";\n                    \t//document.getElementById(\"act_vol_id\").checked = \"unchecked\";\n                    };\n\n                };\n\n                function init() {\n                    var xhttp = new XMLHttpRequest();\n                    xhttp.onreadystatechange = function() {\n                        if (this.readyState == 4 && this.status == 200) {\n                            update(this.responseText)\n                        }\n                    };\n                    xhttp.open(\"GET\", \"status\", true);\n                    xhttp.send();\n                }\n                window.onload = init;\n            </script>\n        </div>\n    </form>\n</body>\n\n</html>"
		;


void dataPage() {
	//digitalWrite ( pinLed, LOW );
	flLedSystem->startLed( LED_RED_PIN, 2);

	DEBUGLOG("dataPage");

	wifiMger->getServer()->send ( 200, "text/html", HTML );

	flLedSystem->stopLed();
	//digitalWrite ( pinLed, HIGH );

}

