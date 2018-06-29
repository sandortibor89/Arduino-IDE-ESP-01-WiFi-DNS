#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

String ssid = "Force";
String pass = "Force0321";

ESP8266WebServer webServer(80);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("ESP");
  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin("esp")) {while(1) {delay(1000);}}
  
  webServer.on("/", []() {
    webServer.send(200, "text/plain", "Hello DNS!");
  });
  webServer.begin();

  MDNS.addService("http", "tcp", 80);
}

void loop() {
  webServer.handleClient();
}
