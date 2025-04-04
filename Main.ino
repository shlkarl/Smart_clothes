
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include "Termal.h"
#include "Charge.h"
#include "HTML.h"
#include "Led.h"

AsyncWebServer server(80);
const char* ssid = "mywear.com";
const char* password = NULL;
IPAddress IP(192, 168, 1, 4);
DNSServer dnsServer;
const char *server_name = "mywear.com";

TERMAL Termal;
CHARGE Charge;
LED Led;

String processor(const String& var){
  if(var == "BUTTONPLACEHOLDER"){
    String buttons ="";
    String outputStateValue = "checked";
    
     buttons = "<span id=\"outputState\"></span></h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"output\" " + outputStateValue + "><span class=\"slider\"></span></label>";
    return buttons; }

  if(var == "POWER"){String buttons ="";
return buttons+ "<pow>""</pow>";}
  return String();}

void setup(){
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.softAPConfig(IP, IP, IPAddress(255, 255, 255, 0));
  const byte DNS_PORT = 53;
  dnsServer.start(DNS_PORT, server_name, IP);


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){request->send_P(200, "text/html", index_html, processor);});
  
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;

        if (request->hasParam(Led_off))    Led.light(3);          
      
    else if (request->hasParam(Led_blue))     Led.light(2);         
      
    else if (request->hasParam(Led_green))    Led.light(1);     
      
    else if (request->hasParam(Led_red))   Led.light(0);        
      
       if (request->hasParam(Heat_back)) {inputMessage = request->getParam(Heat_back)->value(); Termal.SetBack(inputMessage.toInt());}
      
    else if (request->hasParam(Heat_left)) {inputMessage = request->getParam(Heat_left)->value(); Termal.SetLeft(inputMessage.toInt());}
      
    else if (request->hasParam(Heat_right)) {inputMessage = request->getParam(Heat_right)->value(); Termal.SetRight(inputMessage.toInt());}

    request->send(200, "text/plain", "OK");});
server.on("/state", HTTP_GET, [] (AsyncWebServerRequest *request) { request->send(200, "text/plain",(String(Charge.getCharge())+ "% Temperature:" + String(Termal.GetRight()) + "°C"+ String(Termal.GetBack()) + "°C"+ String(Termal.GetLeft()) + "°C").c_str());});
 
  server.begin();
}

void loop(){
  dnsServer.processNextRequest();
  Termal.HeatingBack();
  Termal.HeatingRight();
  Termal.HeatingLeft();
}
