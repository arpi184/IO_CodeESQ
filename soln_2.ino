#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VillageServer";
const char* password = "test1234";

const char* ap_ssid = "ESP8266_RuralServer";
const char* ap_password = "test1234";

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Welcome to ESP8266 Relay Server</h1>";
  html += "<p><a href='/fetch_website'>Go To The Website</a></p>";
  html += "<p><a href='/fetch_chatbot'>Go To The ChatBot</a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleFetchWebsite() {
  WiFiClient client;
  String response;
  if (client.connect("192.168.137.1", 80)) {
    client.print(String("GET /test_site/index.html HTTP/1.1\r\n") +
                 "Host: 192.168.137.1\r\n" +
                 "Connection: close\r\n\r\n");
    
    while (client.connected() || client.available()) {
      while (client.available()) {
        response += client.readString();
      }
    }
    client.stop();
    server.send(200, "text/html", response);
  } else {
    server.send(500, "text/plain", "Failed to connect to website");
  }
}

void handleFetchChatbot() {
  WiFiClient client;
  String response;
  if (client.connect("192.168.137.1", 3000)) {
    client.print(String("GET / HTTP/1.1\r\n") +
                 "Host: 192.168.137.1\r\n" +
                 "Connection: close\r\n\r\n");
    
    while (client.connected() || client.available()) {
      while (client.available()) {
        response += client.readString();
      }
    }
    client.stop();
    server.send(200, "text/html", response);
  } else {
    server.send(500, "text/plain", "Failed to connect to chatbot");
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Access Point Started");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.on("/fetch_website", handleFetchWebsite);
  server.on("/fetch_chatbot", handleFetchChatbot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
