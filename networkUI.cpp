
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
    tt += "\"LOG\":["+ wifiMger->log(JSON_TEXT)  + "," + settingMger->log(JSON_TEXT)+"]";
    tt += "}}";
    return tt;
}


void dataJson() {
	digitalWrite ( pinLed, LOW );
  wifiMger->getServer()->send ( 200, "text/json", getJson() );
  digitalWrite ( pinLed, HIGH );
}

void setData(){
  //bool bWriteData = false;
  //String str;
  String str = wifiMger->getServer()->arg("vol");
  if (str.length()>0) {
	  settingMger->gain = atoi(str.c_str());
	  settingMger->writeData();
  }

  dataPage();
}


void dataPage() {
	digitalWrite ( pinLed, LOW );
DEBUGLOG("dataPage");
  String message =
  "<html>\
    <head>\
      <title>Summary page</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>\
      <h1>Real time data!</h1>";
  message += "<p>" + wifiMger->toString(STD_TEXT) + "</p>";
  message += "<p>Date Hour : " + wifiMger->getHourManager()->toDTString(STD_TEXT) + "</p>";
  message += "<p>Uptime: " + wifiMger->getHourManager()->toUTString() + "</p>";
  message += "<p>&nbsp;</p>";
  //message += "<p>Empreinte: " + String (fpManager.getTemplateCount()) + "/" + String (fpManager.getCapacityCount()) + "</p>";
  message += "<form method='get' action='setData'>";
  message += "<label>Volume:</label><input name='vol' length=64 value=\""+String(settingMger->gain) +"\"><br>";
  message += "<input type='checkbox' name='new' value='true'>Ajouter nouvelle empreinte<br>";
  message += "<input type='checkbox' name='clean' value='true'>Effacer toutes les empreintes<br>";
  /*message += "<TABLE border=2 cellpadding=10 log>";
  for (uint8_t i=0; i<4 ;i++) {
    message += "<TR><TD>"+String(i)+"</TD><TD>"+smManager.m_name[i]+"</TD></TR>";
  }
  message += "</TABLE>";
  message += "<form method='get' action='setData'>";
  message += "<label>Id:</label><input name='id' length=2 value=\"\">";
  message += "<label>Nome:</label><input name='name' length=20 value=\"\"><br>";
  message += "<label>open:</label><input name='open' length=2 value=\"\"><br>";
*/
  message += "<input type='submit'></form>";
  message += "<A HREF=\""+WiFi.localIP().toString()+ "\">cette page</A></br>";
  message += "<A HREF=\"https://thingspeak.com/channels/"+ String(settingMger->m_privateKey) +"\">thingspeak</A></br>\
              <h2>Commands</h2>\
              <ul><li>/clear => erase credentials</li>\
                  <li>/credential\t=> display credential</li>\
                  <li>/restart\t=> restart module</li>\
                  <li>/status\t=> Json details</li>\
                  <li>/whatever\t=> display summary</li></ul>";
  message += "</body></html>";
  wifiMger->getServer()->send ( 200, "text/html", message );

  digitalWrite ( pinLed, HIGH );

}
