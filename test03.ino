#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "mongbus";
const char* password = "79427942qQ";
String line = "";

void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http; //Object of class HTTPClient
    http.begin("http://minseok128.pythonanywhere.com/Fire_extinguisher/1/");
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      line = http.getString();
      Serial.println(line);
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, line);
      JsonObject obj = doc.as<JsonObject>();

      
      int num = obj[String("num")]; 
      int fireState = obj[String("fire_state")];
      Serial.print("num:");
      Serial.println(num);
      Serial.print("fireState:");
      Serial.println(fireState);
      if (digitalRead(12) == LOW){
        //http.post
      }
      if (fireState == 1){
        digitalWrite(13, LOW);
        delay(1000); 
        digitalWrite(13, HIGH);
        delay(1000);   
      } else {
        delay(2000);
      }
    }
    http.end(); //Close connection
  }
}
