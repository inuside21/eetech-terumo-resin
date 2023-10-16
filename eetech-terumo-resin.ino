// WIFI
#include <ESP8266WiFi.h>

// HTTP
#include <ESP8266HTTPClient.h>

// server
String serverAdd = "http://192.168.137.1/";

// device
int dId1 = 2;                              // device ID
int dId2 = 3;
int dId3 = 4;
String dStatus1 = "";
String dStatus2 = "";
String dStatus3 = "";

// input
int pin1 = D1;                            // emergency light 1
int pin2 = D2;                            // emergency light 2
int pin3 = D5;                            // emergency light 3

// output
int outpin1 = D0;                         // tower light

// wifi
WiFiClient nodeclient;
const char* ssid     = "teteteet";
const char* password = "12345678";

// wifi manual
//IPAddress local_IP(192, 168, 50, 146);          // Terumo
//IPAddress gateway(192, 168, 50, 144);
//IPAddress subnet(255, 255, 255, 240);
//IPAddress primaryDNS(8, 8, 8, 8);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional

// http
HTTPClient http1;
HTTPClient http2;
HTTPClient http3;
int httpCode1;
int httpCode2;
int httpCode3;



// ================
// START
// ================
void setup()
{
  // init serial
  Serial.begin(9600);

  // init button
  pinMode(pin1, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);

  /*
    // init wifi manual
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Resin Equipment Monitoring - Wifi Setup Failed");
    }
    else {
    Serial.println("Resin Equipment Monitoring - Wifi Setup Success");
    }
  */

  // init wifi connection
  Serial.println("Resin Equipment Monitoring - Wifi Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Resin Equipment Monitoring - Wifi Connected");
  Serial.println("Resin Equipment Monitoring - IP address: ");
  Serial.println(WiFi.localIP());
}



// ================
// LOOP
// ================
void loop()
{
  // input read
  int reading1 = digitalRead(pin1);
  int reading2 = digitalRead(pin2);
  int reading3 = digitalRead(pin3);

  // check wifi
  if (WiFi.status() != WL_CONNECTED)
  {
    // exit
    delay(500);
    return;
  }

  // check input 1
  // ---------------------------
  if (!reading1)
  {
    dStatus1 = "active";
    digitalWrite(outpin1, LOW);
  }
  else
  {
    dStatus1 = "online";
    digitalWrite(outpin1, HIGH);
  }

  // check input 2
  // ---------------------------
  if (!reading2)
  {
    dStatus2 = "active";
    digitalWrite(outpin1, LOW);
  }
  else
  {
    dStatus2 = "online";
    digitalWrite(outpin1, HIGH);
  }

  // check input 3
  // ---------------------------
  if (!reading3)
  {
    dStatus3 = "active";
    digitalWrite(outpin1, LOW);
  }
  else
  {
    dStatus3 = "online";
    digitalWrite(outpin1, HIGH);
  }

  // send data - 1
  http1.begin(nodeclient, serverAdd + "eetech-monitoring/server/api.php?mode=1&id=" + String(dId1) + "&st=" + dStatus1);    // device id, device status
  httpCode1 = http1.GET();
  http1.end();

  // send data - 2
  http2.begin(nodeclient, serverAdd + "eetech-monitoring/server/api.php?mode=1&id=" + String(dId2) + "&st=" + dStatus2);    // device id, device status
  httpCode2 = http2.GET();
  http2.end();

  // send data - 3
  http3.begin(nodeclient, serverAdd + "eetech-monitoring/server/api.php?mode=1&id=" + String(dId3) + "&st=" + dStatus3);    // device id, device status
  httpCode3 = http3.GET();
  http3.end();

  /*
    // check reply
    if (httpCode2 > 0) {
      if (httpCode2 == HTTP_CODE_OK) {
        Serial.println("Resin Equipment Monitoring - HTTP Success");
      }
      else {
        Serial.println("Resin Equipment Monitoring - HTTP Failed[1] - " + String(httpCode2));
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }
    else {
      Serial.println("Resin Equipment Monitoring - HTTP Failed[0]");
    }
  */


  // exit
  delay(1000);
}
