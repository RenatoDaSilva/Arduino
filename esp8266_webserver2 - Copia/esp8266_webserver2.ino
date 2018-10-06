#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "wifi_sem_sinal";
const char *password = "contabilidade";

WiFiServer server(80);

String header;

String output1State = "off";
String output0State = "off";

const int output1 = 0;
const int output0 = 1;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setting up");
  pinMode(output1, OUTPUT);
  pinMode(output0, OUTPUT);
  digitalWrite(output1, LOW);
  digitalWrite(output0, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /5/on") >= 0)
            {
              Serial.println("GPIO 5 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            }
            else if (header.indexOf("GET /5/off") >= 0)
            {
              Serial.println("GPIO 5 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            }
            else if (header.indexOf("GET /4/on") >= 0)
            {
              Serial.println("GPIO 4 on");
              output0State = "on";
              digitalWrite(output0, HIGH);
            }
            else if (header.indexOf("GET /4/off") >= 0)
            {
              Serial.println("GPIO 4 off");
              output0State = "off";
              digitalWrite(output0, LOW);
            }

            loadHTML(client);

            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void loadHTML(WiFiClient client)
{
  client.println("<!DOCTYPE html>");
  client.println("<html>");

  client.println("<head>");
  client.println("  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("  <link rel=\"icon\" href=\"data:,\">");
  client.println("  <style>");
  client.println("    html {");
  client.println("      font-family: Helvetica;");
  client.println("      display: inline-block;");
  client.println("      margin: 0px auto;");
  client.println("      text-align: center;");
  client.println("    }");

  client.println("    .switch {");
  client.println("      position: relative;");
  client.println("      display: inline-block;");
  client.println("      width: 60px;");
  client.println("      height: 34px;");
  client.println("    }");

  client.println("    .switch input {");
  client.println("      display:none;");
  client.println("    }");

  client.println("    .slider {");
  client.println("      position: absolute;");
  client.println("      cursor: pointer;");
  client.println("      top: 0;");
  client.println("      left: 0;");
  client.println("      right: 0;");
  client.println("      bottom: 0;");
  client.println("      background-color: #ccc;");
  client.println("      -webkit-transition: .4s;");
  client.println("      transition: .4s;");
  client.println("    }");

  client.println("    .slider:before {");
  client.println("      position: absolute;");
  client.println("      content: \"\";");
  client.println("      height: 26px;");
  client.println("      width: 26px;");
  client.println("      left: 4px;");
  client.println("      bottom: 4px;");
  client.println("      background-color: white;");
  client.println("      -webkit-transition: .4s;");
  client.println("      transition: .4s;");
  client.println("    }");

  client.println("    input:checked + .slider {");
  client.println("      background-color: #2196F3;");
  client.println("    }");

  client.println("    input:focus + .slider {");
  client.println("      box-shadow: 0 0 1px #2196F3;");
  client.println("    }");

  client.println("    input:checked + .slider:before {");
  client.println("      -webkit-transform: translateX(26px);");
  client.println("      -ms-transform: translateX(26px);");
  client.println("      transform: translateX(26px);");
  client.println("    }");

  client.println("    .slider.round {");
  client.println("      border-radius: 34px;");
  client.println("    }");

  client.println("    .slider.round:before {");
  client.println("      border-radius: 50%;");
  client.println("    }");
  client.println("  </style>");

  client.println("</head>");

  client.println("<body>");
  client.println("  <script>");
  client.println("    function loadPage(element) {");
  client.println("      var result = '/' + element.id + '/';");
  client.println("      if (element.checked) {");
  client.println("        result += 'on';");
  client.println("      }");
  client.println("      else {");
  client.println("        result += 'off';");
  client.println("      }");
  client.println("      window.location.replace(result);");
  client.println("    }");
  client.println("  </script>");

  client.println("  <h1>Controle de L&acirc;mpadas</h1>");

  client.println("  <p>L&acirc;mpada 1</p>");
  client.println("  <p>");
  client.println("    <label class=\"switch\">");

  if (output1State = "on")
  {
    client.println("      <input type=\"checkbox\" id=\"5\" checked onclick=\"loadPage(this);\">");
  }
  else
  {
    client.println("      <input type=\"checkbox\" id=\"5\" onclick=\"loadPage(this);\">");
  }

  client.println("      <span class=\"slider round\"></span>");
  client.println("    </label></p>");

  client.println("  <p>L&acirc;mpada 2</p>");
  client.println("  <p>");
  client.println("    <label class=\"switch\">");
  if (output0State = "on")
  {
    client.println("      <input type=\"checkbox\" id=\"4\" checked onclick=\"loadPage(this);\">");
  }
  else
  {
    client.println("      <input type=\"checkbox\" id=\"4\" onclick=\"loadPage(this);\">");
  }
  client.println("      <span class=\"slider round\"></span>");
  client.println("    </label></p>");

  client.println("</body>");

  client.println("</html>");

  client.println();
}
