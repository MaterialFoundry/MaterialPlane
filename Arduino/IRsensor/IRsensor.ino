#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include "src/WebSocketsServer/src/WebSocketsServer.h"
#include "src/homography/homography.h"

/*****************************************************************************************************************
 * User settings
 *****************************************************************************************************************/
//Fill in your SSID and password
#define SSID  "Your SSID"
#define PASS  "Your Password"

//If using the complete sensor unit, leave this, otherwise comment it out (place // before the line)
#define FULL_SENSOR

/*****************************************************************************************************************
 * End of user settings
 *****************************************************************************************************************/

#define DEBUG false

//I2C message size
#define MSGSIZE 40

//I2C address
#define IR_ADDRESS 0x58

//If the complete sensor is used, add libraries and define stuff
#ifdef FULL_SENSOR
  #include "src/TinyPICO_Helper_Library/src/TinyPICO.h"
  #include "src/ESP32_AnalogWrite/analogWrite.h"
  #define LED_R_G 25
  #define LED_R_R 26
  #define LED_L_G 27
  #define LED_L_R 15
  #define USB_CHECK_PIN 32
  #define LED_R_BRIGHTNESS 7
  #define LED_G_BRIGHTNESS 255
  #define BAT_WARNING_VOLTAGE 3.6
  TinyPICO tp = TinyPICO();
  bool chargeLedOld = false;
  uint16_t chargeCounter = 0;
  uint16_t chargeSum = 0;
  uint32_t batteryTimer = 0;
  uint8_t batteryState = 0;
#endif

WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);
homography cal;
homography offset;

int16_t Ix[4], Iy[4], Ii[4],spotSize[4];
uint16_t checkSumOld = 0;
uint32_t ledTimer = 0;
uint32_t serialTimer = 0;
uint32_t pollingTimer = 0;
uint8_t sensitivity = 3;
bool homography = false;
bool mirrorX = false;
bool mirrorY = false;
bool rotation = false;
bool offsetOn = false;
uint8_t pointsVisible = 0;
bool stopCal = false;
uint32_t millisOld = 0;
uint8_t debounceCounter = 0;

#ifdef FULL_SENSOR
  /**
   * Set the right led, depending on whether there are any active connections
   */
  void setRightLED(bool connections){
    if (connections) {
      analogWrite(LED_R_R,0);
      analogWrite(LED_R_G,LED_G_BRIGHTNESS);
    }
    else {
      analogWrite(LED_R_R,LED_R_BRIGHTNESS);
      analogWrite(LED_R_G,0);
    }
  }
  
  /**
   * Set the left led, depending on power/battery state
   */
  void setLeftLED(int batteryState){
    if(analogRead(USB_CHECK_PIN)>0){
      if (batteryState == 0) {  //no battery
        analogWrite(LED_L_R,0);
        analogWrite(LED_L_G,0);
      }
      else if (batteryState == 1) { //charging
        if (chargeLedOld) analogWrite(LED_L_R,0);
        else analogWrite(LED_L_R,LED_R_BRIGHTNESS);
        chargeLedOld = !chargeLedOld;
        analogWrite(LED_L_G,0);
      }
      else {    //full battery
        analogWrite(LED_L_R,0);
        analogWrite(LED_L_G,LED_G_BRIGHTNESS);
      }
    }
    else {
      if (tp.GetBatteryVoltage() < BAT_WARNING_VOLTAGE){
        analogWrite(LED_L_R,LED_R_BRIGHTNESS);
        analogWrite(LED_L_G,0);
      }
      else {
        analogWrite(LED_L_R,0);
        analogWrite(LED_L_G,LED_G_BRIGHTNESS);
      }
    }
  }
#endif

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(DEBUG);
  Serial.println("\nInitializing");
  
  #ifdef FULL_SENSOR
    pinMode(LED_R_R,OUTPUT);
    pinMode(LED_R_G,OUTPUT);
    pinMode(LED_L_R,OUTPUT);
    pinMode(LED_L_G,OUTPUT);
    pinMode(USB_CHECK_PIN,INPUT);
    adcAttachPin(USB_CHECK_PIN);
    setRightLED(false);
    digitalWrite(LED_L_R,LOW);
    digitalWrite(LED_L_G,LOW);
    digitalWrite(LED_R_R,LOW);
    digitalWrite(LED_R_G,LOW);

    //Disable on-board led
    tp.DotStar_SetPower(false);
  #endif
  
  //Disable bluetooth radio
  btStop();

  EEPROM.begin(200);
  startupEEPROM();
  
  initializeIR();
  
  //Initialize wifi and websocket
  WiFiMulti.addAP(SSID,PASS);
  while(WiFiMulti.run() != WL_CONNECTED) delay(100);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  delay(1000);
  
  Serial.print("\nDone initializing\nConnected to: ");
  Serial.println(SSID);
  Serial.print("With IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  webSocket.loop();
    
  if (Serial.available() > 0) {
    bool result = checkSerial(); 
    if (result == true) if (DEBUG) Serial.println("OK");
    else if (result == false) if (DEBUG) Serial.println("ERROR"); 
  }

#ifdef FULL_SENSOR
  if (millis()-batteryTimer > 1){
    batteryTimer = millis();
    chargeSum += (int)tp.IsChargingBattery();
    chargeCounter ++;

    if (chargeCounter >= 500){
      batteryState = 0;
      if (chargeSum < 15) { //full battery
        batteryState = 3;
      }
      else if (chargeSum < 75){ //no battery
        batteryState = 0;
      }
      else {                  //charging
        batteryState = 1;
      }
      setLeftLED(batteryState);
      chargeSum = 0;
      chargeCounter = 0;
      if (webSocket.connectedClients() > 0) setRightLED(true);
      else                                  setRightLED(false);
    }
  }
#endif  

  if (millis()-pollingTimer > 1000) {
      sendData();
      pollingTimer = millis();
    }
  else if (millis() - pollingTimer > 25){
    readSensor();
    
    if (pointsVisible == 0) 
      if (debounceCounter < 25) {
        debounceCounter++;
        return;
      }
    debounceCounter = 0;

    uint16_t checkSum = Ix[0] + Iy[0];
    if (checkSum != checkSumOld) {
      checkSumOld = checkSum;
      if (DEBUG) Serial.print(millis() - millisOld);
      millisOld = millis();
      if (DEBUG) Serial.print(" ");
      sendData();
      pollingTimer = millis();
    }
  }
}
