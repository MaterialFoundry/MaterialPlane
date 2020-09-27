/**
 * Initialize IRI bus and IR sensor
 */
 
 void initializeIR(){
  Wire.begin();
 // IR sensor initialize
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x30); 
  Wire.write(0x01);
  Wire.endTransmission();
  delay(10);
  
  setSensitivity(sensitivity);
  
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x33); 
  Wire.write(0x05);
  Wire.endTransmission();
  delay(10);
 }
/**
 * Read the IR sensor and perform a homograph transform if required
 */
void readSensor(){
  //Buffer to store incoming data
  byte data_buf[MSGSIZE];

  //IR sensor read
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x36);
  Wire.endTransmission();

  // Request the 2 byte heading (MSB comes first)
  Wire.requestFrom(IR_ADDRESS, MSGSIZE);

  int i=0;
  //While data is available on the I2C line, write data into the buffer
  while(Wire.available() && i < MSGSIZE) {
      data_buf[i] = Wire.read();
      i++;
  }
  //Reset all stored points
  for (int i=0; i<4; i++){
    Ix[i] = 1023;
    Iy[i] = 1023;
    Ii[i] = 255;
  }
  pointsVisible = 0;
  //Get the X and Y values of point 0, to see if any points are visible
  Ix[0] = ((data_buf[3]>>4)&3) << 8 | data_buf[1];
  Iy[0] = ((data_buf[3]>>6)&3) << 8 | data_buf[2];
  
  if (Ix[0] < 1023 && Iy[0] < 1023){
    //Get intensity of point 0
    Ii[0] = data_buf[9];

    //Get coordinates and intensity of all other points
    for (int i=1; i<4; i++) {
      Ix[i] = ((data_buf[3+9*i]>>4)&3) << 8 | data_buf[1+9*i];
      Iy[i] = ((data_buf[3+9*i]>>6)&3) << 8 | data_buf[2+9*i];
      Ii[i] = data_buf[9+9*i];
    }
    //If calibration is enabled
    if (homography){
      //Perform homography transform on the coordinates
      for (int i=0; i<4; i++){
        cal.calculateCoordinates(Ix[i],Iy[i]);
        Ix[i] = cal.getX();
        Iy[i] = cal.getY();
      }
      //If offset is on, perform second homography transform
      if (offsetOn){
        for (int i=0; i<4; i++){
          offset.calculateCoordinates(Ix[i],Iy[i]);
          Ix[i] = offset.getX();
          Iy[i] = offset.getY();
        } 
      }
      //If values are not between 0 and 1022, set coordinates to 1023 and intensity to 255 (signals that there is no point)
      for (int i=0; i<4; i++)
        if (Ix[i] < 0 || Ix[i] > 1022 || Iy[i] < 0 || Iy[i] > 1022){
          Ix[i] = 1023;
          Iy[i] = 1023;
          Ii[i] = 255;
        }
    }
    //Check how many points are visible
    for(i=0; i<4; i++)
      if (Ix[i] < 1023 && Iy[i] < 1023 && Ii[i] < 255)
        pointsVisible++;
  }
}

/**
 * Set the sensitiviy of the IR sensor
 */
void setSensitivity(uint8_t sens){
  uint8_t p0, p1, p2, p3;
  sensitivity = sens;
  if (sens > 4) sens = 4;
  p0 = 0xFF;
  p2 = 0x00;
  p3 = 0x00;
    
  if (sens == 0)      p1 = 0xFE;
  else if (sens == 1) p1 = 0x50;
  else if (sens == 2) p1 = 0x20;
  else if (sens == 3) p1 = 0x0E;
  else if (sens == 4) p1 = 0x0C;
  
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(0x00); Wire.write(p0); Wire.write(0x00); Wire.write(p1); Wire.endTransmission();
  delay(10);
  
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x1A); Wire.write(p2); Wire.write(p3);
  Wire.endTransmission();
  
  delay(10);
  
  Wire.beginTransmission(IR_ADDRESS);
  Wire.write(0x30); Wire.write(0x08);
  Wire.endTransmission();
  delay(10);
}

/**
 * Do things while waiting on receiving calibration points. Keeps the connection alive, and allows cancelling the calibration procedure
 */
bool calWait(){
  webSocket.loop();
  if (stopCal){
    if (DEBUG) Serial.println("Canceling calibration");
    return true;
  }
  if (millis()-pollingTimer > 1000) {
    webSocket.broadcastTXT("{\"V\":-1,\"M\":\"WAITING\"}");
    pollingTimer = millis();
  }
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');   
    if (data.indexOf("STOP")>=0){
      if (DEBUG) Serial.println("Canceling calibration");
      webSocket.broadcastTXT("{\"V\":-1,\"M\":\"CAL\",\"D\":-1}");
      return true;
    }
  }
  return false;
}

/**
 * Perform single-point calibration procedure
 */
void getCal(){
  if (DEBUG) Serial.println("STARTING CAL");
  webSocket.broadcastTXT("{\"V\":-1,\"M\":\"CAL\",\"D\":0}");
  homography = false;
  bool offsetOnOld = offsetOn;
  offsetOn = false;
  stopCal = false;
  
  readSensor();
  
  for (int i=0; i<4; i++){
    //Wait until a point is detected
    while ((Ix[0] == 1023) || (Iy[0] == 1023)) {
      readSensor();
      if (calWait()) return; 
    }
    //Register the point in the calibration array
    cal.setCalArray(i, 0, Ix[0]);
    cal.setCalArray(i, 1, Iy[0]);
    char msg[40];
    sprintf(msg,"{\"V\":-1,\"M\":\"CAL\",\"D\":%d}",i+1);
    if (DEBUG) Serial.println(msg);
    webSocket.broadcastTXT(msg);

   //Wait until no more point is detected
    while ((Ix[0] < 1023) && (Iy[0] < 1023)) {
      readSensor(); 
      if (millis()-pollingTimer > 1000) {
        webSocket.broadcastTXT("{\"V\":-1,\"M\":\"WAITING\"}");
        pollingTimer = millis();
      }
    }
    //Debounce delay
    delay(500);
  }
  //Order the calibration points and calculate the homography array
  cal.orderCalArray();
  homography = true;
  offsetOn = offsetOnOld;
}

/**
 * Perform multipoint calibration procedure
 */
void getCalMulti(){
  if (DEBUG) Serial.println("STARTING CAL MULTI");
  webSocket.broadcastTXT("{\"V\":-1,\"M\":\"MULTI\",\"D\":0}");
  homography = false;
  bool offsetOnOld = offsetOn;
  offsetOn = false;
  uint8_t calPointsOld = 0;
  
  readSensor();

  //Wait until all 4 points are visible
  while ((Ix[3] == 1023) || (Iy[3] == 1023)) {
    readSensor();
    uint8_t calPoints = 0;
    for (int i=0; i<4; i++){
      if (Ix[i] < 1023 || Iy[i] < 1023)
        calPoints++;
    }
    if (calPoints != calPointsOld){
      calPointsOld = calPoints;
      char msg[40];
      sprintf(msg,"{\"V\":-1,\"M\":\"OFFSET\",\"D\":%d}",calPoints);
      if (DEBUG) Serial.println(msg);
      webSocket.broadcastTXT(msg);
      delay(100);
    }
    if (calWait()) return; 
  }
  //Register the values in the calibration array
  for (int i=0; i<4; i++){
    cal.setCalArray(i, 0, Ix[i]);
    cal.setCalArray(i, 1, Iy[i]);
  }
  webSocket.broadcastTXT("{\"V\":-1,\"M\":\"MULTI\",\"D\":4}");
  //Order the calibration points and calculate the homography array
  cal.orderCalArray();
  homography = true;
  offsetOn = offsetOnOld;
}

void getOffset(){
  if (DEBUG) Serial.println("STARTING OFFSET");
  webSocket.broadcastTXT("{\"V\":-1,\"M\":\"OFFSET\",\"D\":0}");
  offsetOn = false;
  readSensor();

  for (int i=0; i<4; i++){
    //Wait until a point is detected
    while ((Ix[0] == 1023) || (Iy[0] == 1023)) {
      readSensor();
      if (calWait()) return; 
    }
    //Register the point in the calibration array
    offset.setCalArray(i, 0, Ix[0]);
    offset.setCalArray(i, 1, Iy[0]);
    char msg[40];
    sprintf(msg,"{\"V\":-1,\"M\":\"OFFSET\",\"D\":%d}",i+1);
    if (DEBUG) Serial.println(msg);
    webSocket.broadcastTXT(msg);

   //Wait until no more point is detected
    while ((Ix[0] < 1023) && (Iy[0] < 1023)) {
      readSensor(); 
      if (millis()-pollingTimer > 1000) {
        webSocket.broadcastTXT("{\"V\":-1,\"M\":\"WAITING\"}");
        pollingTimer = millis();
      }
    }
    //Debounce delay
    delay(500);
  }
  //Order the calibration points and calculate the homography array
  offset.orderCalArray();
  offsetOn = true;
}
