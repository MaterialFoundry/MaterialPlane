int checkSerial(){
  data = Serial.readStringUntil('\n');    
  analyzeData(data);
}

int analyzeData(String received) {
  

  String received2[6] = {"","","","","",""};                                            //Stores the read string as individual words
  int counter = 0;                                                                  //Word counter
  for (int i=0; i<(received.length()-1); i++) {                                         //Check each individual character in the received string
    if (received[i] == ' ')                                                             //If the character is a space, increment the word counter
      counter++;
    else                                                                            //If the character is no space, add the character to the current word
      received2[counter] += received[i];
  }

  Serial.print("Rec1: ");
  Serial.print(received2[0]);
  Serial.print("\tRec2: ");
  Serial.print(received2[1]);
  Serial.print("\tRec3: ");
  Serial.println(received2[2]);

  if (received2[0] == "SENS"){
    setSensitivity(received2[1].toInt());
    storeSensitivity();
    return 1;
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
      for (int i=0; i<4; i++) printf("CALX%d: %d\tCALY%d: %d\t",i,cal[0][i],i,cal[1][i]);
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
      for (int i=0; i<4; i++) printf("OFFSETX%d: %.3f\tOFFSETY%d: %.3f\t",i,offset[0][i],i,offset[1][i]);
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
//sprintf(msg, "{\"C\":%d%d%d%d%d,\"S\":%d,\"X0\":%d,\"Y0\":%d,\"I0\":%d,\"x\":%d,\"y\":%d}",homography,offset,mirrorX,mirrorY,rotation,255-sensitivity,Ix[0],Iy[0],Ii[0],Iold[0],Iold[1]);
//    Serial.println(msg);
 //   webSocket.broadcastTXT(msg);


//pinMode(battPin,INPUT);
   // pinMode(battState, INPUT);
 
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

  char msg[200];
  sprintf(msg,"{\"V\":%d,\"H\":%d,\"O\":%d,\"MX\":%d,\"MY\":%d,\"R\":%d,\"S\":%d",pointsVisible,homography,offsetOn,mirrorX,mirrorY,rotation,sensitivity);
  #ifdef COMPLETE_SENSOR
    sprintf(msg+strlen(msg),",\"B\":%.2f,\"BS\":%d",tp.GetBatteryVoltage(),batteryState);
  #endif
  for(i=0; i<4; i++)
        if (pointsVisible > i) {
          sprintf(msg+strlen(msg),",\"X%d\":%d,\"Y%d\":%d,\"I%d\":%d",i,Ix[i],i,Iy[i],i,Ii[i]);
        }
  sprintf(msg+strlen(msg),"}");
  if (DEBUG) Serial.println(msg);
  webSocket.broadcastTXT(msg);
}
