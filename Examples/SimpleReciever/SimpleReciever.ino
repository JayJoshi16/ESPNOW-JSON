/*  Codes that Receives  JSON data using ESPNOW Protocol

*   Developed by  Jay Joshi 
*   github.com/JayJoshi16
*/


#include <esp_now.h>
#include <WiFi.h>
uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x4C, 0x9C, 0xD0};  //Source ESP32's MAC Address

#include <ArduinoJson.h>
String jsondata;
DynamicJsonDocument doc(1024);


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

  char* buff = (char*) incomingData;        //char buffer
  jsondata = String(buff);                  //converting into STRING
  Serial.print("Recieved ");
  Serial.println(jsondata);                 //Complete JSON data will be printed here
  DeserializationError error = deserializeJson(doc, jsondata);
    
  if (!error) {
        long a   = doc["a"]; 
        const char* b  =   doc["b"]; 
        Serial.println(a);                   //values of a
        Serial.println(b);                   //values of b
  }

  else {
        Serial.print(F("deserializeJson() failed: "));  //Just in case of an ERROR of ArduinoJSon
        Serial.println(error.f_str());
        return;
  }

}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
    
  if (esp_now_init() != ESP_OK) {       //Init ESPNOW
        Serial.println("Error initializing ESP-NOW");
        return;
  }

  esp_now_register_recv_cb(OnDataRecv);         //Reciever CallBack function

    
}

void loop() {

}
