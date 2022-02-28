/*  Codes Sends and Recieves JSON data using ESPNOW Protocol
*   Developed by  Jay Joshi 
*   github.com/JayJoshi16
*/

#include <esp_now.h>
#include <WiFi.h>
uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x4C, 0x9C, 0xD0}; //add peer address

#include <ArduinoJson.h>
String recv_jsondata;
String send_jsondata;

//StaticJsonDocument<256> doc;  // for data < 1KB
DynamicJsonDocument doc(1024);  // for data > 1KB

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//recieved data will process here
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {

  char* buff = (char*) incomingData;      //char buffer
  recv_jsondata = String(buff);           //converting into STRING
  Serial.print("Recieved ");
  Serial.println(recv_jsondata);          //Complete JSON data will be printed here
  DeserializationError error = deserializeJson(doc, recv_jsondata);
    
  if (!error) {
    
        //RECIEVED DATA 
        long a   = doc["a"]; 
        const char* b  =   doc["b"];
        Serial.println(a);               //values of a
        Serial.println(b);           //values of b
   }

  else {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
  }

}

void setup() {
  
  //    ONBOARD LED WILL GLOW IN CASE OF RESET 
  //    {Remove if you want}
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(2000);
  digitalWrite(2,LOW);
  delay(2000);
   
  //
   
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
  send_jsondata = "";               //Clearing  JSON STRING
  doc["a"] = 1;                     //Creating JSON
  doc["b"] = "ON";
  serializeJson(doc, send_jsondata); //DATA TO BE SENT
  esp_now_send(broadcastAddress, (uint8_t *) send_jsondata.c_str(), sizeof(send_jsondata)*send_jsondata.length());
  Serial.println(send_jsondata);
  delay(20);

    
  send_jsondata = "";               //Clearing JSON STRING
  doc["a"] = 0;
  doc["b"] = "OFF";
  serializeJson(doc, send_jsondata);
  esp_now_send(broadcastAddress, (uint8_t *) send_jsondata.c_str(), sizeof(send_jsondata)*send_jsondata.length());
  Serial.println(send_jsondata);
  delay(20);
}
