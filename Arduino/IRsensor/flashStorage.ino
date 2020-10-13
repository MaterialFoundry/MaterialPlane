#define CAL_EN_ADDR         0
#define OFFSET_EN_ADDR      1
#define MIRROR_X_ADDR       2
#define MIRROR_Y_ADDR       3
#define ROTATION_ADDR       4
#define SENSITIVITY_ADDR    5
#define CAL_ADDR            6 //8 * uint16_t = 16 bytes
#define OFFSET_ADDR         22  //8 * uint16_t = 16 bytes
#define COMPX_ADDR          38
#define COMPY_ADDR          39

uint16_t readEEPROM(uint8_t addr){
  return EEPROM.read(addr) | EEPROM.read(addr+1)<<8;
}
void writeEEPROM(uint8_t addr, uint16_t data){
  EEPROM.write(addr,data&255);
  EEPROM.write(addr+1,(data>>8)&255);
}

void storeCal(){
  for (int i=0; i<2; i++)
    for (int j=0; j<4; j++)
      writeEEPROM(CAL_ADDR+2*j+8*i, cal.getCalArray(j,i));
  EEPROM.commit();
}
void readCal(){
  for (int i=0; i<2; i++)
    for (int j=0; j<4; j++)
      cal.setCalArray(j,i,readEEPROM(CAL_ADDR+2*j+8*i));
}
void storeOffset(){
  for (int i=0; i<2; i++)
    for (int j=0; j<4; j++)
      writeEEPROM(OFFSET_ADDR+2*j+8*i, offset.getCalArray(j,i));
  EEPROM.commit();
}
void readOffset(){
  for (int i=0; i<2; i++)
    for (int j=0; j<4; j++)
      offset.setCalArray(j,i,readEEPROM(OFFSET_ADDR+2*j+8*i));
}

void storeCalEn() {
  EEPROM.write(CAL_EN_ADDR,homography);
  EEPROM.commit();
}
void storeOffsetEn() {
  EEPROM.write(OFFSET_EN_ADDR,offsetOn);
  EEPROM.commit();
}
void storeMirrorX() {
  EEPROM.write(MIRROR_X_ADDR,mirrorX);
  EEPROM.commit();
}
void storeMirrorY() {
  EEPROM.write(MIRROR_Y_ADDR,mirrorY);
  EEPROM.commit();
}
void storeRotation() {
  EEPROM.write(ROTATION_ADDR,rotation);
  EEPROM.commit();
}
void storeSensitivity() {
  EEPROM.write(SENSITIVITY_ADDR,sensitivity);
  EEPROM.commit();
}
void storeCompX(){
  EEPROM.write(COMPX_ADDR,compX);
  EEPROM.commit();
}
void storeCompY(){
  EEPROM.write(COMPY_ADDR,compY);
  EEPROM.commit();
}

void startupEEPROM(){
  if (EEPROM.read(CAL_EN_ADDR) == 255) {
    storeCalEn();
    storeOffsetEn();
    storeMirrorX();
    storeMirrorY();
    storeRotation();
    storeSensitivity();
    storeCompX();
    storeCompY();
    return;
  }
  readCal();
  cal.calculateHomographyMatrix();
  readOffset();
  offset.calculateHomographyMatrix();
  homography = EEPROM.read(CAL_EN_ADDR);
  offsetOn = EEPROM.read(OFFSET_EN_ADDR);
  mirrorX = EEPROM.read(MIRROR_X_ADDR);
  mirrorY = EEPROM.read(MIRROR_Y_ADDR);
  rotation = EEPROM.read(ROTATION_ADDR);
  sensitivity = EEPROM.read(SENSITIVITY_ADDR);
  compX = EEPROM.read(COMPX_ADDR);
  compY = EEPROM.read(COMPY_ADDR);
}
