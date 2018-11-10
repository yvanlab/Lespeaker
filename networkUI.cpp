
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

const char HTML[] PROGMEM ="<!DOCTYPE html><html><head> <meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\"> <title>lespeaker</title> <script type=\"application/x-javascript\"></script></head><body> <h1 style=\"text-align: center;\"><span id=\"modulename\">Module</span> configuration </h1> <div style=\"text-align: center;\"> <p>Version : <span id=\"version\">3.0</span></p></div><div style=\"text-align: center;\"> <p>Date build : <span id=\"builddate\">10/08/1900</span> </p></div><div style=\"text-align: center;\"> <p>Up time : <span id=\"uptime\">un moment</span> </p></div><hr style=\"margin-top: 51px; margin-left: auto; width: 177px; margin-right: auto;\"> <form action=\"/action_page.php\" style=\"height: 57px;\"> <div> <div> <h3 style=\"height: 3px;\">Titre </h3> <hr> <p><i><b><span id=\"titre\">Le titreeee</span></b></i> </p><div> <h3 style=\"height: 4px;\">Source </h3> <hr> <input id=\"msd_id\" onclick=\"changeSetting('source','2')\" type=\"radio\"> MicroSD <br><input id=\"rad_id\" onclick=\"changeSetting('source','1')\" type=\"radio\"> Radio </div><div> <h3 style=\"height: 3px;\">Periode </h3> <hr> <input onclick=\"changeSetting('period','soir')\" id=\"soir_id\" type=\"radio\" > Soir <br><input onclick=\"changeSetting('period','matin')\" id=\"matin_id\" type=\"radio\" > Matin </div><div> <h3 style=\"height: 3px;\">Action </h3> <hr> <input onclick=\"changeSetting('mode','vol')\" id=\"act_vol_id\" type=\"radio\" > Volume <br><input onclick=\"changeSetting('mode','sel')\" id=\"act_sel_id\" type=\"radio\" > Selection </div><div> <h3 style=\"height: 5px;\">Actions</h3> <hr> <input onclick=\"changeSetting('action','stop')\" value=\"Stop\" type=\"button\"> <input onclick=\"changeSetting('action','start')\" value=\"Start\" type=\"button\"> <input onclick=\"changeSetting('action','next')\" value=\"Suivante\" type=\"button\"> <input onclick=\"changeSetting('action','prev')\" value=\"Precedent\" type=\"button\"> <br>Volume <input onchange=\"changeSetting('volume',this.value)\" id=\"volume\" name=\"volume\" min=\"0\" max=\"30\" type=\"range\"> </div></div><script>function changeSetting(act, val){document.getElementById(\"version\").innerHTML=val; var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){update(this.responseText)}}; xhttp.open(\"GET\", \"setData?\" + act + \"=\" + val, true); xhttp.send();}; function update(responseText){var myObj=JSON.parse(responseText); document.getElementById(\"builddate\").innerHTML=myObj.module.build_date; document.getElementById(\"version\").innerHTML=myObj.module.version; document.getElementById(\"modulename\").innerHTML=myObj.module.nom; document.getElementById(\"uptime\").innerHTML=myObj.module.uptime; document.getElementById(\"titre\").innerHTML=myObj.sound; document.getElementById(\"volume\").value=myObj.setting.volume; if (myObj.setting.source==2) document.getElementById(\"msd_id\").checked=\"checked\"; else document.getElementById(\"rad_id\").checked=\"checked\"; if (myObj.setting.period==1) document.getElementById(\"matin_id\").checked=\"checked\"; else document.getElementById(\"soir_id\").checked=\"checked\"; if (myObj.setting.mode==1) document.getElementById(\"act_vol_id\").checked=\"checked\"; else document.getElementById(\"act_sel_id\").checked=\"checked\";}function init(){var xhttp=new XMLHttpRequest(); xhttp.onreadystatechange=function(){if (this.readyState==4 && this.status==200){update(this.responseText)}}; xhttp.open(\"GET\", \"status\", true); xhttp.send();}window.onload=init; </script> </div></form></body></html>";



void dataPage() {
	//digitalWrite ( pinLed, LOW );
	flLedSystem->startLed( LED_RED_PIN, 2);

	DEBUGLOG("dataPage");

	wifiMger->getServer()->send ( 200, "text/html", HTML );

	flLedSystem->stopLed();
	//digitalWrite ( pinLed, HIGH );

}

