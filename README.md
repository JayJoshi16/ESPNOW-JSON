# ESPNOW-JSON
Learn how to use **ESP-NOW** to exchange **JSON data** between **ESP32** boards programmed with Arduino IDE.

Send and Recieve _**JSON**_ data by either One way or Two way communication.
_**See EXAMPLES codes**_

One Way JSON communication using ESPNOW
![ESP_NOW_one_way_communication_two_boards](https://user-images.githubusercontent.com/86542830/155991657-12cc67e7-ee2d-4846-a7a9-2f7b0a3045ae.jpg)


ESP-NOW supports the following features:

    Encrypted and unencrypted unicast communication;
    Mixed encrypted and unencrypted peer devices;
    Up to **250-byte** payload can be carried;
    Sending callback function that can be set to inform the application layer of transmission success or failure.
  
ESP-NOW technology also has the following limitations:

    Limited encrypted peers. 10 encrypted peers at the most are supported in Station mode; 6 at the most in SoftAP or SoftAP + Station mode;
    Multiple unencrypted peers are supported, however, their total number should be less than 20, including encrypted peers;
    **Payload is limited to 250 bytes**.
