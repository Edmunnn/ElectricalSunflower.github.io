#include <Servo.h>
#include <WiFiEsp.h>
#include "ThingSpeak.h"

char ssid[] = "EE3070_P1404_1";
char password[] = "EE3070P1404";
unsigned long CHANNEL_ID = 2499645;
const char* WRITE_API_KEY = "KTNKX76ZXJDZBOBN";
const char* server = "api.thingspeak.com";

WiFiEspClient client;
Servo servo;

#define LDR_UR A1  // Upper Right Light Sensor
#define LDR_BR A2  // Bottom Right Light Sensor
#define LDR_UL A3  // Upper Left Light Sensor
#define LDR_BL A4  // Bottom Left Light Sensor
#define ERROR_THRESHOLD 10
#define LIGHT_THRESHOLD 100
#define DEFAULT_POSITION 90
#define ADJUSTMENT_STEP 1

unsigned long lastThingSpeakUpdate = 0; 

void setup() { //Setup for Serial Monitor
  Serial.begin(115200); 
  Serial1.begin(115200); 
  WiFi.init(&Serial1);
  connectToWiFi();
  ThingSpeak.begin(client); 
  
  servo.attach(9); //servo motor analogWrite/ analogRead pin to pin 9
  servo.write(DEFAULT_POSITION);
}

void loop() {
  static int currentPosition = DEFAULT_POSITION;
  int ldrUR = analogRead(LDR_UR);
  int ldrBR = analogRead(LDR_BR);
  int ldrUL = analogRead(LDR_UL);
  int ldrBL = analogRead(LDR_BL); // Read the light intensity of each light sensors respectivly
  
  int avgUpper = (ldrUR + ldrUL) / 2;
  int avgBottom = (ldrBR + ldrBL) / 2;

 
  if(abs(avgUpper - avgBottom) > ERROR_THRESHOLD) {
    if(avgUpper > avgBottom) {
      currentPosition -= ADJUSTMENT_STEP; 
    } else {
      currentPosition += ADJUSTMENT_STEP; 
    }
    currentPosition = constrain(currentPosition, 0, 180);
    servo.write(currentPosition);
  }

 
  if(millis() - lastThingSpeakUpdate > 15000) {
    lastThingSpeakUpdate = millis();
    int avgIntensity = (ldrUR + ldrBR + ldrUL + ldrBL) / 4;
    String direction = currentPosition < 90 ? "South" : "North";
    sendDataToThingSpeak(avgIntensity, currentPosition, direction);
  }

  delay(100); 
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void sendDataToThingSpeak(int avgIntensity, int position, String direction) {
  ThingSpeak.setField(1, avgIntensity);
  ThingSpeak.setField(2, position);
  ThingSpeak.setField(3, direction.equals("South") ? 0 : 1);
  ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);
  Serial.println("Data sent to ThingSpeak.");
}

void setToDefaultPosition() {
  servo.write(DEFAULT_POSITION);
  Serial.println("Servo set to default position.");
}





