void hexdump(const void *mem, uint32_t len, uint8_t cols = 16) {
  const uint8_t* src = (const uint8_t*) mem;
  if (DEBUG) Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
  for(uint32_t i = 0; i < len; i++) {
    if(i % cols == 0) {
      if (DEBUG) Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
    }
    if (DEBUG) Serial.printf("%02X ", *src);
    src++;
  }
  if (DEBUG) Serial.printf("\n");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            if (DEBUG) Serial.printf("[%u] Disconnected!\n", num);
            stopCal = false;
            #ifdef FULL_SENSOR
              if (webSocket.connectedClients() > 0) setRightLED(true);
              else                                  setRightLED(false);
            #endif
            break;
        case WStype_CONNECTED:
            {
                IPAddress ip = webSocket.remoteIP(num);
                if (DEBUG) Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
                #ifdef FULL_SENSOR
                  stopCal = false;
                  setRightLED(true);
                #endif
                // send message to client
                webSocket.sendTXT(num, "Connected");
            }
            break;
        case WStype_TEXT:
            {
              if (DEBUG) Serial.printf("[%u] get Text: %s\n", num, payload);
              String pl = "";
              for (int i=0; i<length; i++) pl += char(payload[i]);
              pl += '\n';
              if (pl.indexOf("STOP")>=0) stopCal = true;
              else analyzeData(pl);
            }
            break;
        case WStype_BIN:
            if (DEBUG) Serial.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    case WStype_ERROR:      
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    }

}
