#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0x69, 0xE6};
byte ip[] = {10, 0, 0, 20};
char server[] = "homeautomation5.herokuapp.com";

void setup()
{
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
}

EthernetClient client;

void loop()
{
  getSchedule();
}

void getSchedule()
{
  Serial.println("connecting...");
  if (client.connect(server, 80))
  {
    Serial.println("connected");
    client.println("GET /api/v1/reschedules.json HTTP/1.1");
    //    client.println("GET /api/v1/reschedules/36 HTTP/1.1");
    client.println("Host: homeautomation5.herokuapp.com");
    client.println("X-User-Email: renato.katia@gmail.com");
    client.println("X-User_Token: LyWh6EcmdVUF2fKsgnSL");
    client.println("cache-control: no-cache");
    client.println("Connection: close");
    client.println("Content-Type: application/json");
    client.println();
  }
  else
  {
    Serial.println("connection failed");
  }

  boolean inJSON = false;
  String json = "";

  while (client.connected())
  {
    while (client.available())
    {
      char c = client.read();
      if (c == 91)
      {
        inJSON = true;
      }
      if (inJSON == true)
      {
        json += c;
      }
      if (c == 93)
      {
        inJSON = false;
      }
    }
  }
  Serial.println(json);

  if (!client.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    delay(5000);
  }
}
//
//struct schedule
//{
//  int id;
//  int pin;
//  int state;
//};

//schedule nextSchedule;
//
//void processSchedules(String sJSON)
//{
//DynamicJsonDocument doc(1024);
//  deserializeJson(doc, sJSON);
//  JsonObject obj = doc.as<JsonObject>();
//
//  nextSchedule.id = obj[String("id")];
//  nextSchedule.pin = obj[String("pin")];
//  nextSchedule.state = obj[String("state")];
//
//   Serial.println(nextSchedule.id);
//   Serial.println(nextSchedule.pin);
//   Serial.println(nextSchedule.state);
//}
