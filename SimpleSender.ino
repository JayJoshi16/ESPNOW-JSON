
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x3C, 0x99, 0x30}; //Destination ESP32's MAC Address

String jsondata;

StaticJsonDocument<200> doc;


//function for Sending data
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) { 
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

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
  jsondata = "";  //clearing String after data is being sent
  
  doc["a"] = 1;   
  doc["b"] = "ON";
  serializeJson(doc, jsondata);  //Serilizing JSON
  esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata)*jsondata.length());  //Sending "jsondata"  
  Serial.println(jsondata);                                                       
  delay(20);

  
  
  jsondata = "";  //clearing String after data is being sent
  
  doc["a"] = 0;
  doc["b"] = "OFF";
  serializeJson(doc, jsondata);
  esp_now_send(broadcastAddress, (uint8_t *) jsondata.c_str(), sizeof(jsondata)*jsondata.length());
  Serial.println(jsondata);
  delay(20);
}
