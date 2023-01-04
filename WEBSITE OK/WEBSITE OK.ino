#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "NETSINCODE";
const char* password = "aabbccdd";

const char* host = "192.168.100.229";
const char* serverName = "http://192.168.100.229/nodemcu/lib/insertdb.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
WiFiClient client;
HTTPClient http;


const int httpPort = 80;
String url;

unsigned long timeout;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {

  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    //return;
  }

  // We now create a URI for the request
  url = "/nodemcu/lib/get_mcu.php";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    //    String line = client.readStringUntil('\r');
    //    Serial.print(line);
    if (client.find("ON")) {
      delay(5000);
      Serial.println("GPS HIDUP");
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "id=FNOlqZXmbd";
      int httpResponseCode = http.POST(httpRequestData);
       Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    } else {
      delay(5000);
      Serial.println("GPS MATI");
    }
  }

  Serial.println();
  Serial.println("closing connection");
  Serial.println();
}
