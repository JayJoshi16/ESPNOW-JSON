# ESPNOW JSON : Sending and Recieving JSON Data using ESP NOW Protocol 
Learn how to use **ESP-NOW** to exchange **JSON data** between **ESP32** boards programmed with Arduino IDE.

   Send and Recieve _**JSON**_ data by either One way or Two way communication .
   
   _**See EXAMPLES codes**_ and **TWOWAY_ESPNOW_JSON codes**




**Bidirectional JSON communication using ESPNOW**

![ESP_NOW_two_way_communication_two_boards](https://user-images.githubusercontent.com/86542830/155992746-9b694dc1-44b1-4276-b457-b2158428e47d.jpg)



**ESP-NOW supports the following features:**

   >   _Encrypted and unencrypted unicast communication_ 
   
   >  _Mixed encrypted and unencrypted peer devices_ 
   
   >  _Up to **250-byte** payload can be carried_  
   
   >  _-Sending callback function that can be set to inform the application layer of transmission success or failure_  
   
  
**ESP-NOW technology also has the following limitations:**

   >  _Limited encrypted peers. 10 encrypted peers at the most are supported in Station mode
    6 at the most in SoftAP or SoftAP + Station mode_  
    
   >  _Multiple unencrypted peers are supported, however, their total number should be less than 20,
    including encrypted peers_  
    
   >  _**Payload is limited to 250 bytes**_
