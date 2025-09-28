#include <WiFiS3.h>
#include <ArduinoOSCWiFi.h>
WiFiUDP Udp;

#include "secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

unsigned int localPort = 8102;
const int sendPort = 8001;

// We'll store the broadcast as an IPAddress
IPAddress broadcastIP;

int touch1 = 0, touch2 = 0, touch3 = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  // check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true) ;
  }

  // connect to WiFi
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    delay(5000);
  }
  Serial.println("Connected!");
  printWifiStatus();

  // figure out broadcast address:
  IPAddress ip   = WiFi.localIP();
  IPAddress mask = WiFi.subnetMask();
  broadcastIP[0] = ip[0] | ~mask[0];
  broadcastIP[1] = ip[1] | ~mask[1];
  broadcastIP[2] = ip[2] | ~mask[2];
  broadcastIP[3] = ip[3] | ~mask[3];
  Serial.print("Broadcast IP: ");
  Serial.println(broadcastIP);

  // start UDP and OSC
  Udp.begin(localPort);
}

void loop() {
  // read your touch data…
  if (Serial1.available()) {
    String inc = Serial1.readStringUntil('\n');
    inc.trim();
    Serial.print("Received: "); Serial.println(inc);
    if (inc.startsWith("touch ")) {
      int id = inc.substring(6).toInt();
      if (id==0) touch1=1;
      else if (id==1) touch2=1;
      else if (id==2) touch3=1;
    } else if (inc.startsWith("release ")) {
      int id = inc.substring(8).toInt();
      if (id==0) touch1=0;
      else if (id==1) touch2=0;
      else if (id==2) touch3=0;
    }
  }

    String bcast = broadcastIP.toString();

    OscWiFi.publish( bcast, sendPort, "/arduino/touch1", touch1 );
    OscWiFi.publish( bcast, sendPort, "/arduino/touch2", touch2 );
    OscWiFi.publish( bcast, sendPort, "/arduino/touch3", touch3 );
    OscWiFi.update();
}

void printWifiStatus() {
  Serial.print("SSID: ");       Serial.println(WiFi.SSID());
  Serial.print("IP Addr: ");    Serial.println(WiFi.localIP());
  Serial.print("Subnet mask: ");Serial.println(WiFi.subnetMask());
  Serial.print("RSSI: ");       Serial.print(WiFi.RSSI()); Serial.println(" dBm");
}