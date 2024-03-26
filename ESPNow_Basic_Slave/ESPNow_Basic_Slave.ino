/**
   ESPNOW - Basic communication - Slave
   Date: 26th September 2017
   Author: Arvind Ravulavaru <https://github.com/arvindr21>
   Purpose: ESPNow Communication between a Master ESP32 and multiple ESP8266 Slaves
   Description: This sketch consists of the code for the Slave module.
   Resources: (A bit outdated)
   a. https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
   b. http://www.esploradores.com/practica-6-conexion-esp-now/

   << This Device Slave >>

   Flow: Master
   Step 1 : ESPNow Init on Master and set it in STA mode
   Step 2 : Start scanning for Slave ESP32 (we have added a prefix of <code data-enlighter-language="raw" class="EnlighterJSRAW">slave</code> to the SSID of slave for an easy setup)
   Step 3 : Once found, add Slave as peer
   Step 4 : Register for send callback
   Step 5 : Start Transmitting data from Master to Slave(s)

   Flow: Slave
   Step 1 : ESPNow Init on Slave
   Step 2 : Update the SSID of Slave with a prefix of <code data-enlighter-language="raw" class="EnlighterJSRAW">slave</code>
   Step 3 : Set Slave in AP mode
   Step 4 : Register for receive callback and wait for data
   Step 5 : Once data arrives, print it in the serial monitor

   Note: Master and Slave have been defined to easily understand the setup.
         Based on the ESPNOW API, there is no concept of Master and Slave.
         Any devices can act as master or salve.
*/

#include <espnow.h>
#include <ESP8266WiFi.h>

#define CHANNEL 1
typedef struct struct_message {
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;


// config AP SSID

void setup() {
  Serial.begin(115200);
  //Set device in AP mode to begin with
  WiFi.mode(WIFI_STA);
  // configure device AP mode
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
  if (esp_now_init() != ERR_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
void OnDataRecv(uint8_t * mac,uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.println(myData.d == 1 ? "Button is Toggled" : "Button is Toggled Again");
  Serial.println();
}

void loop() {
  // Chill
}