void readSensor(){
  //IR sensor read
  Wire.beginTransmission(slaveAddress);
  Wire.write(0x36);
  Wire.endTransmission();

  Wire.requestFrom(slaveAddress, MSGSIZE);        // Request the 2 byte heading (MSB comes first)
  for (i=0;i<MSGSIZE;i++) { data_buf[i]=0; }
  i=0;
  while(Wire.available() && i < MSGSIZE) {
      data_buf[i] = Wire.read();
      i++;
  }
  pointsVisible = 0;
  Ix[0] = ((data_buf[3]>>4)&3) << 8 | data_buf[1];
  Iy[0] = ((data_buf[3]>>6)&3) << 8 | data_buf[2];

  if (Ix[0] < 1023 && Iy[0] < 1023){
    for (int i=0; i<4; i++) {
      Ix[i] = ((data_buf[3+9*i]>>4)&3) << 8 | data_buf[1+9*i];
      Iy[i] = ((data_buf[3+9*i]>>6)&3) << 8 | data_buf[2+9*i];
      Ii[i] = data_buf[9+9*i];
    }
    if (homography){
    for (int i=0; i<4; i++){
      mtx_type TP[3] = {Ix[i],Iy[i],1};
      mtx_type outputTemp[3];
      Matrix.Multiply((mtx_type*)TP, (mtx_type*)H, 1, 3, 3, (mtx_type*)outputTemp);
      outputTemp[0] /= outputTemp[2];
      outputTemp[1] /= outputTemp[2];
      Ix[i] = round(outputTemp[0]);
      Iy[i] = round(outputTemp[1]);
    }
    if (offsetOn){
      for (int i=0; i<4; i++){
        mtx_type TP[3] = {Ix[i],Iy[i],1};
        mtx_type outputTemp[3];
        Matrix.Multiply((mtx_type*)TP, (mtx_type*)HO, 1, 3, 3, (mtx_type*)outputTemp);
        outputTemp[0] /= outputTemp[2];
        outputTemp[1] /= outputTemp[2];
        Ix[i] = round(outputTemp[0]);
        Iy[i] = round(outputTemp[1]);
      }
    }
    for (int i=0; i<4; i++)
      if (Ix[i] < 0 || Ix[i] > 1022 || Iy[i] < 0 || Iy[i] > 1022){
        Ix[i] = 1023;
        Iy[i] = 1023;
        Ii[i] = 255;
      }
    }
      for(i=0; i<4; i++)
        if (Ix[i] < 1023 && Iy[i] < 1023 && Ii[i] < 255)
          pointsVisible++;
    
  }
  else pointsVisible = 0;
}

uint8_t findMax(uint16_t ARRAY[]){
  uint16_t maxValue = ARRAY[0];
  uint8_t maxPos = 0;
  for (int i=1; i<4; i++){
    if (ARRAY[i] > maxValue){
      maxValue = ARRAY[i];
      maxPos = i;
    }
  }
  return maxPos;
}

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
    data = Serial.readStringUntil('\n');   
    if (data.indexOf("STOP")>=0){
      if (DEBUG) Serial.println("Canceling calibration");
      webSocket.broadcastTXT("{\"V\":-1,\"M\":\"CAL\",\"D\":-1}");
      return true;
    }
  }
  
  return false;
}

void getCal(){
  if (DEBUG) Serial.println("STARTING CAL");
  webSocket.broadcastTXT("{\"V\":-1,\"M\":\"CAL\",\"D\":0}");
  uint16_t calTempX[4], calTempY[4];
  homography = false;
  bool offsetOnOld = offsetOn;
  offsetOn = false;
  stopCal = false;
  readSensor();
  
  for (int i=0; i<4; i++){
    char msg[40];
    while ((Ix[0] == 1023) || (Iy[0] == 1023)) {
      readSensor();
      if (calWait()) {
        
        return;
      }
    }
    calTempX[i] = Ix[0];
    calTempY[i] = Iy[0]; 
    sprintf(msg,"{\"V\":-1,\"M\":\"CAL\",\"D\":%d}",i+1);
    if (DEBUG) Serial.println(msg);
    webSocket.broadcastTXT(msg);
   
    while ((Ix[0] < 1023) && (Iy[0] < 1023)) {
      readSensor(); 
      if (millis()-pollingTimer > 1000) {
        webSocket.broadcastTXT("{\"V\":-1,\"M\":\"WAITING\"}");
        pollingTimer = millis();
      }
    }
    delay(500);
  }
  
  //Order calibration points
  for (int i=0; i<4; i++){
    cal[0][i] = calTempX[i];
    cal[1][i] = calTempY[i];
  }
  uint8_t maxPos;
  for (int i=0; i< 4; i++) {
    maxPos = findMax(calTempX);
    cal[0][i] = calTempX[maxPos];
    cal[1][i] = calTempY[maxPos];
    calTempX[maxPos] = 0;
    maxPos = findMax(calTempX);
  }
  for (int i=0; i<4; i++){
    calTempX[i] = cal[0][i];
    calTempY[i] = cal[1][i];
  }
  if (cal[1][1] > cal[1][0]) {
    cal[0][0] = calTempX[1];
    cal[1][0] = calTempY[1];
    cal[0][1] = calTempX[0];
    cal[1][1] = calTempY[0];
  }
  if (cal[1][3] < cal[1][2]) {
    cal[0][2] = calTempX[3];
    cal[1][2] = calTempY[3];
    cal[0][3] = calTempX[2];
    cal[1][3] = calTempY[2];
  }
  for (int i=0; i<4; i++) printf("CALX%d: %d\tCALY%d: %d\n",i,cal[0][i],i,cal[1][i]);
  if (DEBUG) Serial.println();
  homographyTransform(cal,false);
  offsetOn = offsetOnOld;
}

void getCalMulti(){
  if (DEBUG) Serial.println("STARTING CAL MULTI");
  uint16_t calTempX[4], calTempY[4];
  homography = false;
  bool offsetOnOld = offsetOn;
  offsetOn = false;
  readSensor();
  while ((Ix[3] == 1023) || (Iy[3] == 1023)) readSensor();
  for (int i=0; i<4; i++){
    calTempX[i] = Ix[i];
    calTempY[i] = Iy[i]; 
  }
  
  //Order calibration points
  for (int i=0; i<4; i++){
    cal[0][i] = calTempX[i];
    cal[1][i] = calTempY[i];
  }
  uint8_t maxPos;
  for (int i=0; i< 4; i++) {
    maxPos = findMax(calTempX);
    cal[0][i] = calTempX[maxPos];
    cal[1][i] = calTempY[maxPos];
    calTempX[maxPos] = 0;
    maxPos = findMax(calTempX);
  }
  for (int i=0; i<4; i++){
    calTempX[i] = cal[0][i];
    calTempY[i] = cal[1][i];
  }
  if (cal[1][1] > cal[1][0]) {
    cal[0][0] = calTempX[1];
    cal[1][0] = calTempY[1];
    cal[0][1] = calTempX[0];
    cal[1][1] = calTempY[0];
  }
  if (cal[1][3] < cal[1][2]) {
    cal[0][2] = calTempX[3];
    cal[1][2] = calTempY[3];
    cal[0][3] = calTempX[2];
    cal[1][3] = calTempY[2];
  }
  for (int i=0; i<4; i++) printf("CALX%d: %d\tCALY%d: %d\n",i,cal[0][i],i,cal[1][i]);
  if (DEBUG) Serial.println();
  homographyTransform(cal,false);
  offsetOn = offsetOnOld;
}

void homographyTransform(uint16_t cal[2][4], bool offset){
  homography = true;
 
  mtx_type A[8][8];
  mtx_type AT[8][8];
  mtx_type B[8][8];
  mtx_type C[8] ={bounds[0][0],bounds[1][0],
                  bounds[0][1],bounds[1][1],
                  bounds[0][2],bounds[1][2],
                  bounds[0][3],bounds[1][3]};
  mtx_type D[8];
  mtx_type E[8];
  
  for (int i=0; i<4; i++){
    A[0][i*2] = cal[0][i];
    A[0][i*2+1] = 0;
    A[1][i*2] = cal[1][i];
    A[1][i*2+1] = 0;
    A[2][i*2] = 1;
    A[2][i*2+1] = 0;
    A[3][i*2] = 0;
    A[3][i*2+1] = cal[0][i];
    A[4][i*2] = 0;
    A[4][i*2+1] = cal[1][i];
    A[5][i*2] = 0;
    A[5][i*2+1] = 1;
    A[6][i*2] = (float)-bounds[0][i]*cal[0][i];
    A[6][i*2+1] = (float)-bounds[1][i]*cal[0][i];
    A[7][i*2] = (float)-bounds[0][i]*cal[1][i];
    A[7][i*2+1] = (float)-bounds[1][i]*cal[1][i];
  }
  
  Matrix.Transpose((mtx_type*)A, 8, 8, (mtx_type*)AT);
  Matrix.Multiply((mtx_type*)A, (mtx_type*)AT, 8, 8, 8, (mtx_type*)B);
  Matrix.Invert((mtx_type*)B, 8);
  Matrix.Multiply((mtx_type*)C, (mtx_type*)AT, 8, 8, 8, (mtx_type*)D);
  Matrix.Multiply((mtx_type*)D, (mtx_type*)B, 8, 8, 8, (mtx_type*)E);
  
  if (offset){
    for (int i=0; i<3; i++) {
      HO[i][0] = E[i];
      HO[i][1] = E[i+3];
      HO[i][2] = E[i+6];
    }
    HO[2][2] = 1;
  }
  else {
    for (int i=0; i<3; i++) {
      H[i][0] = E[i];
      H[i][1] = E[i+3];
      H[i][2] = E[i+6];
    }
    H[2][2] = 1;
  }
}

void getOffset(){
  if (DEBUG) Serial.println("STARTING OFFSET");
  uint16_t offsetTempX[4], offsetTempY[4];
  offsetOn = false;
  readSensor();
  for (int i=0; i<4; i++){
    while ((Ix[0] == 1023) || (Iy[0] == 1023)) readSensor();
    offsetTempX[i] = Ix[0];
    offsetTempY[i] = Iy[0]; 
    printf("OFFSET %d OK\n",i+1);
    while ((Ix[0] < 1023) && (Iy[0] < 1023)) readSensor(); 
    delay(500);
  }
  
  //Order calibration points
  for (int i=0; i<4; i++){
    offset[0][i] = offsetTempX[i];
    offset[1][i] = offsetTempY[i];
  }
  uint8_t maxPos;
  for (int i=0; i<4; i++) {
    maxPos = findMax(offsetTempX);
    offset[0][i] = offsetTempX[maxPos];
    offset[1][i] = offsetTempY[maxPos];
    offsetTempX[maxPos] = 0;
    maxPos = findMax(offsetTempX);
  }
  for (int i=0; i<4; i++){
    offsetTempX[i] = offset[0][i];
    offsetTempY[i] = offset[1][i];
  }
  if (offset[1][1] > offset[1][0]) {
    offset[0][0] = offsetTempX[1];
    offset[1][0] = offsetTempY[1];
    offset[0][1] = offsetTempX[0];
    offset[1][1] = offsetTempY[0];
  }
  if (offset[1][3] < offset[1][2]) {
    offset[0][2] = offsetTempX[3];
    offset[1][2] = offsetTempY[3];
    offset[0][3] = offsetTempX[2];
    offset[1][3] = offsetTempY[2];
  }
  for (int i=0; i<4; i++){
    offsetTempX[i] = offset[0][i];
    offsetTempY[i] = offset[1][i];
  }
  for (int i=0; i<4; i++) printf("OFFSETX%d: %d\tOFFSETY%d: %d\n",i,offset[0][i],i,offset[1][i]);
  if (DEBUG) Serial.println();
  offsetOn = true;
  homographyTransform(offset,true);
}

void setSensitivity(uint8_t sens){
  int p0, p1, p2, p3;
  sensitivity = sens;
  sens = 255-sens;
  if (sens == 0) sens++;
  p1 = sens;
  p2 = sens-1;
  if (sens > 192) {
    p0 = 0xFF;
    p3 = 0x00;
  }
  else if (sens > 127) {
    p0 = 0x96;
    p3 = 0x04;
  }
  else if (sens > 64) {
    p0 = 0xC8;
    p3 = 0x03;
  }
  else {
    p0 = 0x72;
    p3 = 0x03;
  }
    
   // Wire.write(0x00); Wire.write(0x02); Wire.write(0x00); Wire.write(0x00); Wire.write(0x71); Wire.write(0x01); Wire.write(0x00); Wire.write(p0);

  Wire.beginTransmission(slaveAddress);
  Wire.write(0x00); Wire.write(0x02); Wire.write(0x00); Wire.write(0x00); Wire.write(0x71); Wire.write(0x01); Wire.write(0x00); Wire.write(p0);  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(slaveAddress);
  Wire.write(0x07); Wire.write(0x00); Wire.write(p1);
  Wire.endTransmission();
  delay(10);
  Wire.beginTransmission(slaveAddress);
  Wire.write(0x1A); Wire.write(p2); Wire.write(p3);
  Wire.endTransmission();
  delay(10);
  Write_2bytes(0x30,0x08); delay(10);
  
}
