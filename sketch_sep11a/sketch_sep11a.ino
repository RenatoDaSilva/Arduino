#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x69, 0xE6 };
byte ip[] = { 10, 0, 0, 20 };
char server[] = "jsonplaceholder.typicode.com";

EthernetClient client;

void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
//  Serial.println("connecting...");
//  client.setTimeout(1000);
//  Serial.println(client.connect(server, 80)); // Returns -5.
//  if (client.connect(server, 80)) {
//    Serial.println("connected");
//    client.println("GET /posts/1 HTTP/1.1");
//    client.println("Host: jsonplaceholder.typicode.com");
//    client.println("cache-control: no-cache");
//    client.println("Connection: close");
//    client.println("Content-Type: application/json");
//    client.println();
//  }
//  else {
//    Serial.println("connection failed");
//  }
}

void loop()
{
  Serial.println("connecting...");
//  Serial.println(client.connect(server, 80)); // Returns -5.
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /posts/1 HTTP/1.1");
    client.println("Host: jsonplaceholder.typicode.com");
    client.println("cache-control: no-cache");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }
  
  while(client.connected()) {
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
}
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    delay(5000);

  }
}
