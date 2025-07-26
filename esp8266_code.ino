#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

// Pin Definitions
#define SEEDING_PIN D5
#define WATERING_PIN D6
#define BUZZER_PIN D0
#define TRIG_PIN D3
#define ECHO_PIN D4

// WiFi Credentials
const char* ssid = "farming";
const char* password = "12345678";

// Object Initialization
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);
ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Global Variables
unsigned int distance;
String Seedingstat = "OFF";
String pumpstat = "OFF";
unsigned long currentMillis = 0;
unsigned long previousMillis1 = 0;
const unsigned int interval = 100;
unsigned int sec = 0;
unsigned int msec100 = 0;
unsigned int msec1100 = 0;

void handleRoot() {
  String cmd = "<!DOCTYPE HTML><html>";
  cmd += "<head><title>CONTROLPANEL</title>";
  cmd += "<meta http-equiv=\"refresh\" content=\"3\"/>";
  cmd += "<style>";
  cmd += "a{border-radius:10px;background-color:#DD5A3E;border:red;color:black;padding:7px 50px;text-align:center;text-decoration:none;}";
  cmd += "a:hover{background-color:#72DD3E;}";
  cmd += "</style></head>";
  cmd += "<body><h1>Farmbot Monitoring Control</h1>";
  cmd += "<a href=\"/wateringon\">PUMP ON</a> ";
  cmd += "<a href=\"/wateringoff\">PUMP OFF</a>";
  cmd += "<h3>Pump: " + pumpstat + "</h3>";
  cmd += "<a href=\"/seedingon\">SEEDING ON</a> ";
  cmd += "<a href=\"/seedingoff\">SEEDING OFF</a>";
  cmd += "<h3>Seeding: " + Seedingstat + "</h3>";
  cmd += "<h3>Distance: " + String(distance) + "cm</h3>";
  cmd += "</body></html>";
  server.send(200, "text/html", cmd);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: " + server.uri();
  message += "\nMethod: " + String((server.method() == HTTP_GET) ? "GET" : "POST");
  message += "\nArguments: " + String(server.args()) + "\n";
  
  for (uint8_t i = 0; i < server.args(); i++) {
    message += server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize pins
  pinMode(SEEDING_PIN, OUTPUT);
  pinMode(WATERING_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(SEEDING_PIN, LOW);
  digitalWrite(WATERING_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();

  // WiFi Setup
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Server Routes
  server.on("/", handleRoot);
  
  server.on("/wateringon", []() {
    digitalWrite(WATERING_PIN, HIGH);
    pumpstat = "ON";
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON       ");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/wateringoff", []() {
    digitalWrite(WATERING_PIN, LOW);
    pumpstat = "OFF";
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF      ");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/seedingon", []() {
    digitalWrite(SEEDING_PIN, HIGH);
    Seedingstat = "ON";
    lcd.setCursor(10, 1);
    lcd.print("Seed:ON");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/seedingoff", []() {
    digitalWrite(SEEDING_PIN, LOW);
    Seedingstat = "OFF";
    lcd.setCursor(10, 1);
    lcd.print("Seed:OFF");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  timer();
  server.handleClient();
  
  distance = distanceSensor.measureDistanceCm();
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm    ");
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 20 && distance > 0) {  // Added > 0 to handle sensor errors
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  delay(50);
}

void timer() {
  currentMillis = millis();
  if ((currentMillis - previousMillis1) >= interval) {
    msec100++;
    msec1100++;
    if (msec100 > 9) {
      msec100 = 0;
      sec++;
    }
    previousMillis1 = currentMillis;
  }
}