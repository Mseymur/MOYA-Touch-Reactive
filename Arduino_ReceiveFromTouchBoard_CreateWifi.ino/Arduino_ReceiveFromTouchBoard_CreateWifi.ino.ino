#include <WiFiS3.h>
#include <ArduinoOSCWiFi.h>
WiFiUDP Udp;

#include "secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;

unsigned int localPort = 8101;
const int sendPort = 8001;

// broadcast address will be calculated
IPAddress broadcastIP;

int touch1 = 0, touch2 = 0, touch3 = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true) ;
  }

  // check firmware version
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // Start the Access Point
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true) ;
  }
  Serial.println("Access Point Created");

  printWifiStatus();

  // compute broadcast address: bcast = ip | ~mask
  IPAddress ip   = WiFi.localIP();
  IPAddress mask = WiFi.subnetMask();
  for (int i = 0; i < 4; i++) {
    broadcastIP[i] = ip[i] | ~mask[i];
  }
  Serial.print("Broadcast IP: ");
  Serial.println(broadcastIP);

  // start UDP listener
  Udp.begin(localPort);
}

void loop() {
  if (Serial1.available()) {
    String incoming = Serial1.readStringUntil('\n');
    incoming.trim();

    Serial.print("Received: ");
    Serial.println(incoming);

    if (incoming.startsWith("touch ")) {
      int id = incoming.substring(6).toInt();
      if (id == 11) touch1 = 1;
      else if (id == 10) touch2 = 1;
      else if (id == 9) touch3 = 1;
    }
    else if (incoming.startsWith("release ")) {
      int id = incoming.substring(8).toInt();
      if (id == 11) touch1 = 0;
      else if (id == 10) touch2 = 0;
      else if (id == 9) touch3 = 0;
    }
  }

  // publish to broadcast (toString() converts IPAddress → String)
  String b = broadcastIP.toString();
  OscWiFi.publish(b, sendPort, "/arduino/touch1", touch1);
  OscWiFi.publish(b, sendPort, "/arduino/touch2", touch2);
  OscWiFi.publish(b, sendPort, "/arduino/touch3", touch3);
  OscWiFi.update();
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}