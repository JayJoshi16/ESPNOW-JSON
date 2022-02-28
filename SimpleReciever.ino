
#include <esp_now.h>
#include <WiFi.h>
uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x4C, 0x9C, 0xD0};  //Source ESP32's MAC Address
#include <ArduinoJson.h>
String jsondata;
DynamicJsonDocument doc(1024);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  //memcpy(&jsondata, incomingData, sizeof(jsondata));
  char* buff = (char*) incomingData;
  jsondata = String(buff);
  Serial.print("Recieved ");
  Serial.println(jsondata);
  DeserializationError error = deserializeJson(doc, jsondata);
  if (!error) {

    long a   = doc["a"]; //values are 1 or 0
    const char* b  =   doc["b"];//values are "ON" or "OFF" 
    Serial.println(a);
    Serial.println(b);
  }

  else {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

}
