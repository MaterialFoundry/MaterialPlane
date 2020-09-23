#define DEBUG false

#include <Arduino.h>
#include <MatrixMath.h>
#include <math.h>
#include <EEPROM.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <WebSocketsServer.h>

//Fill in your SSID and password
#define SSID  "Your SSID"
#define PASS  "Your Password"

//If using the complete sensor unit, leave this, otherwise comment it out (place // before the line)
#define FULL_SENSOR



#define MSGSIZE 40

//If the complete sensor is used, add libraries and define stuff
#ifdef FULL_SENSOR
  #include <TinyPICO.h>
  #include <analogWrite.h>
  #define LED_R_G 25
  #define LED_R_R 26
  #define LED_L_G 27
  #define LED_L_R 15
  #define USB_CHECK_PIN 32
  #define LED_R_BRIGHTNESS 7
  #define LED_G_BRIGHTNESS 255
  #define BAT_WARNING_VOLTAGE 3.9
  TinyPICO tp = TinyPICO();
  bool chargeLedOld = false;
  uint16_t chargeCounter = 0;
  uint16_t chargeSum = 0;
  unsigned long batteryTimer = 0;
  int batteryState = 0;
#endif

WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(81);

String data = "";
int IRsensorAddress = 0xB0;
int slaveAddress;
int ledPin = 13;
boolean ledState = false;
byte data_buf[MSGSIZE];
int i;
int Ix[4], Iy[4], Ii[4],spotSize[4];
uint16_t cal[2][4];
uint16_t bounds[2][4] ={0,0,1023,1023,
                        1023,0,0,1023};

uint16_t offset[2][4]; 
uint16_t checkSum = 0;
uint16_t checkSumOld = 0;
unsigned long ledTimer = 0;
unsigned long serialTimer = 0;
unsigned long pollingTimer = 0;
uint8_t sensitivity = 127;
bool homography = false;
bool mirrorX = false;
bool mirrorY = false;
bool rotation = false;
bool offsetOn = false;
uint8_t pointsVisible = 0;
mtx_type H[3][3];
mtx_type HO[3][3];
bool stopCal = false;
unsigned long millisOld = 0;
int debounceCounter = 0;




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

void Write_2bytes(byte d1, byte d2)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(d1); Wire.write(d2);
    Wire.endTransmission();
}

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
  Wire.begin();

  slaveAddress = IRsensorAddress >> 1;   // This results in 0x21 as the address to pass to TWI
  // IR sensor initialize
  Write_2bytes(0x30,0x01); delay(10);
  setSensitivity(sensitivity);
  Write_2bytes(0x33,0x05); delay(10);
 
  WiFiMulti.addAP(SSID,PASS);

  while(WiFiMulti.run() != WL_CONNECTED) {
      delay(100);
  }

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
    int result = checkSerial(); 
    if (result == 1) if (DEBUG) Serial.println("OK");
    else if (result == 0) if (DEBUG) Serial.println("ERROR"); 
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
    
    //checkSum = 0;
    checkSum = Ix[0] + Iy[0];
    //else for (int i=0; i<4; i++) checkSum += Ix[i] + Iy[i] + Ii[i];
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
