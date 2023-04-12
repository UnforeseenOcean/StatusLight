#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "StatusLight";  // Enter SSID here
const char* password = "88888888";  //Enter Password here

ESP8266WebServer server(80);

uint8_t LED1pin = D1;
bool LED1status = LOW;

uint8_t LED2pin = D2;
bool LED2status = LOW;

uint8_t LED3pin = D3;
bool LED3status = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);
  uint8 mode = 0;
  WiFi.softAP(ssid, password);
  delay(100);
  WiFi.printDiag(Serial);
  
  server.on("/", handle_OnConnect);
  server.on("/avail", handle_avail);
  server.on("/knock", handle_knock);
  server.on("/dnd", handle_dnd);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}

  if(LED3status)
  {digitalWrite(LED3pin, HIGH);}
  else
  {digitalWrite(LED3pin, LOW);}
}

void handle_OnConnect() {
  Serial.println("Client connected!");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status)); 
}

void handle_avail() {
  LED1status = HIGH;
  LED2status = LOW;
  LED3status = LOW;
  Serial.println("Status set to AVAILABLE");
  server.send(200, "text/html", SendHTML(true,false,false)); 
}

void handle_knock() {
  LED1status = LOW;
  LED2status = HIGH;
  LED3status = LOW;
  Serial.println("Status set to KNOCK FIRST");
  server.send(200, "text/html", SendHTML(false,true,false)); 
}

void handle_dnd() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = HIGH;
  Serial.println("Status set to DO NOT DISTURB");
  server.send(200, "text/html", SendHTML(false,false,true)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Human Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #1f1f1f;}\n";
  ptr +="body {margin-top: 50px;} h1 {color: white;margin: 50px auto 30px;} h3 {color: white;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 120px;background-color: #1abc9c;border: none;color: white;padding: 13px; text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-avail {background-color: #67b500;}\n";
  ptr +=".button-knock {background-color: #b57f00;}\n";
  ptr +=".button-dnd {background-color: #b50c00;}\n";
  ptr +=".active {color: white;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Human Control</h1>\n";
  ptr +="<h3>Will they ever listen?</h3>\n";
  ptr +="<a class=\"button button-avail\" href=\"/avail\">Available</a>\n";
  ptr +="<a class=\"button button-knock\" href=\"/knock\">Knock First</a>\n";
  ptr +="<a class=\"button button-dnd\" href=\"/dnd\">Do Not Disturb</a>\n";
  
   if(led1stat)
  {ptr +="<p class=\"active\">Available &#9745;</p>\n";}
  else
  {ptr +="<p>Available</p>\n";}

  if(led2stat)
  {ptr +="<p class=\"active\">Knock First &#9745;</p>\n";}
  else
  {ptr +="<p>Knock First</p>\n";}

  if(led3stat)
  {ptr +="<p class=\"active\">Do Not Disturb &#9745;</p>\n";}
  else
  {ptr +="<p>Do Not Disturb</p>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
