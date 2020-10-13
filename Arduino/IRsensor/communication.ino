/**
 * Read the data from the serial port, and send to analyzeData function
 */
bool checkSerial(){
  String data = Serial.readStringUntil('\n');    
  return analyzeData(data);
}

/**
 * Analyze the incoming data from either the serial port or the websocket
 */
bool analyzeData(String received) {
  String received2[6] = {"","","","","",""};                                            //Stores the read string as individual words
  uint8_t counter = 0;                                                                  //Word counter
  for (int i=0; i<(received.length()-1); i++) {                                         //Check each individual character in the received string
    if (received[i] == ' ')                                                             //If the character is a space, increment the word counter
      counter++;
    else                                                                            //If the character is no space, add the character to the current word
      received2[counter] += received[i];
  }

  if (DEBUG) Serial.print("Rec1: ");
  if (DEBUG) Serial.print(received2[0]);
  if (DEBUG) Serial.print("\tRec2: ");
  if (DEBUG) Serial.print(received2[1]);
  if (DEBUG) Serial.print("\tRec3: ");
  if (DEBUG) Serial.println(received2[2]);

  if (received2[0] == "SENS"){
    setSensitivity(received2[1].toInt());
    storeSensitivity();
    return 1;
  }
  if (received2[0] == "COMP"){
    if (received2[1] == "X"){
      compX = received2[2].toInt();
      storeCompX();
    }
    else if (received2[1] == "Y"){
      compY = received2[2].toInt();
      storeCompY();
    }
    else if (received2[1] == "GET"){
      printf("COMPX: %d\tCOMPY: %d\n",compX,compY);
    }
  }
  else if (received2[0] == "CAL"){
    if (received2[1] == "SINGLE") {
      getCal();
      storeCalEn();
      storeCal();
      return 1;
    }
    else if (received2[1] == "MULTI") {
      getCalMulti();
      storeCalEn();
      storeCal();
      return 1;
    }
    else if (received2[1] == "EN"){
      if (received2[2] == "1") homography = true;
      else if (received2[2] == "0") homography = false;
      else return 0;
      storeCalEn();
      return 1;
    }
    else if (received2[1] == "GET"){
      printf("CALEN: %d\t",homography);
      for (int i=0; i<4; i++) printf("CALX%d: %d\tCALY%d: %d\t",i,cal.getCalArray(i,0),i,cal.getCalArray(i,1));
      Serial.println();
    }
    else return 0;
  }
  else if (received2[0] == "OFFSET") {
    if (received2[1] == "EN"){
      if (received2[2] == "1") offsetOn = true;
      else if (received2[2] == "0") offsetOn = false;
      else return 0;
      storeOffsetEn();
      return 1;
    }
    else if (received2[1] == "GET"){
      printf("OFFSETEN: %d\t",homography);
      for (int i=0; i<4; i++) printf("OFFSETX%d: %.3f\tOFFSETY%d: %.3f\t",i,offset.getCalArray(i,0),i,offset.getCalArray(i,1));
      Serial.println();
    }
    else {
      getOffset();
      storeOffset();
      storeOffsetEn();
      return 1;
    }
  }
  else if (received2[0] == "MIR"){
    bool val;
    if (received2[2] == "1") val = true;
    else if (received2[2] == "0") val = false;
    else return 0;
    if (received2[1] == "X") {
      mirrorX = val;
      storeMirrorX();
    }
    else if (received2[1] == "Y") {
      mirrorY = val;
      storeMirrorY();
    }
    else return 0;
    sendData();
    return 1;
  }
  else if (received2[0] == "ROT"){
    if (received2[1] == "1") rotation = true;
    else if (received2[1] == "0") rotation = false;
    else return 0;
    storeRotation();
    sendData();
    return 1;
  }
  else return 0;
}

/**
 * Send data over the webSocket and serial port (if DEBUG is on)
 */
void sendData() {
  if (rotation){
    for (int i=0; i<4; i++){
      uint16_t valTemp[2] = {Ix[i],Iy[i]};
      Ix[i] = valTemp[1];
      Iy[i] = valTemp[0];
    }
  }
  if (mirrorX) 
    for (int i=0; i<4; i++)
      Ix[i] = 1023 - Ix[i];
  if (mirrorY) 
    for (int i=0; i<4; i++)
      Iy[i] = 1023 - Iy[i];

  for (int i=0; i<4; i++){
    Ix[i] += compX;
    Iy[i] += compY;
    if (Ix[i] < 0) Ix[i] = 0;
    else if (Ix[i] > 1022) Ix[i] = 1022;
    if (Iy[i] < 0) Iy[i] = 0;
    else if (Iy[i] > 1022) Iy[i] = 1022;
  }
  char msg[200];
  sprintf(msg,"{\"V\":%d,\"H\":%d,\"O\":%d,\"MX\":%d,\"MY\":%d,\"R\":%d,\"S\":%d,\"CX\":%d,\"CY\":%d",pointsVisible,homography,offsetOn,mirrorX,mirrorY,rotation,sensitivity,compX,compY);
  #ifdef FULL_SENSOR
    sprintf(msg+strlen(msg),",\"B\":%.2f,\"LB\":%d",tp.GetBatteryVoltage(),lowBattery);
  #else
    sprintf(msg+strlen(msg),",\"B\":0,\"LB\":0");
  #endif
  
  for(int i=0; i<4; i++)
        if (pointsVisible > i) 
          sprintf(msg+strlen(msg),",\"X%d\":%d,\"Y%d\":%d,\"I%d\":%d",i,Ix[i],i,Iy[i],i,Ii[i]);     
  sprintf(msg+strlen(msg),"}");
  if (DEBUG) Serial.println(msg);
  webSocket.broadcastTXT(msg);
}
