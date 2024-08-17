#include "WiFi.h"
#include "ESPAsyncWebServer.h"
// Credentials

const char *ssid = "JioFiber-4G";
const char *psk = "12345678";

// Async Server Obj
AsyncWebServer webserver(80);

const char index_html[] = R"rawliteral(<!DOCTYPE html>
<html>

<head>
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
    <link rel=\"icon\" href=\"data:,\">
    <style>
        html {
            font-family: Helvetica;
            display: inline-block;
            margin: 0px auto;
            text-align: center;
        }

        .button {
            background-color: #4CAF50;
            border: none;
            color: white;
            padding: 16px 40px;
            text-decoration: none;
            font-size: 30px;
            margin: 2px;
            cursor: pointer;
        }
    </style>
</head>
<script>

    function sendrequest()
    {
        console.log("Send request called");
        var req = new XMLHttpRequest();
        req.open("GET","/update",true);
        req.send();
    }
</script>
<body>
    <h1>ESP32 Web Server</h1>
    <p>Digital Output State</p>
    <p><button class=\"button\" onclick=sendrequest()>ON</button></a></p>
</body>


</html>)rawliteral";

const int LED = 2;
int state = LOW;
void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, psk);
  pinMode(LED, OUTPUT);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("Connected to Wifi ");
  Serial.println(WiFi.localIP());

  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest *req)
               { req->send_P(200, "text/html", index_html, nullptr); });
  webserver.on("/update", HTTP_GET, [](AsyncWebServerRequest *req)
               {
                 Serial.println("Update Pressed!!");

                 digitalWrite(LED, state);

                 if (state)
                 {
                   state = LOW;
                 }
                 else
                 {
                   state = HIGH;
                 }
                 Serial.println("Toggle Pressed");
               });
  Serial.println("Sent Web Page!!");

  webserver.begin();
}

void loop()
{

}
