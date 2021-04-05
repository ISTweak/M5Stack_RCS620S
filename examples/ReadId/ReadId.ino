#include <M5Stack.h>
#include <RCS620S.h>

#define POLLING_INTERVAL 500

RCS620S rcs620s;

void setup() {
  M5.begin();
  int ret;
  ret = rcs620s.initDevice(22, 21);
  Serial.println("Init RCS620s ");
  if (!ret) {
    while(1);
  }
  Serial.println("Connect RCS620S");
}

void loop()
{
  uint8_t size, type = PICC_UNKNOWN;
  uint8_t buf[20];
  bool found = false;
  
  if (rcs620s.polling() || rcs620s.polling_felica() || rcs620s.polling_typeA() || rcs620s.polling_typeB()) {
    Serial.print("ID: ");
    for (int i = 0; i < rcs620s.idLength; i++) {
      Serial.print(rcs620s.idm[i], HEX);
    }
    type = rcs620s.piccType;
    if (type == PICC_ISO_IEC14443_TypeA_MIFARE) {
        Serial.print("(ISO/IEC14443 Type A MIFARE)\r\n");                
    } else if (type == PICC_ISO_IEC14443_TypeA_MIFAREUL) {
        Serial.print("(ISO/IEC14443 Type A MIFARE Ultralight)\r\n");                
    } else if (type == PICC_ISO_IEC14443_TypeB) {
        Serial.print("(ISO/IEC14443 Type B)\r\n");
    } else if (type == PICC_FELICA) {
        Serial.print("(FeliCa)\r\n");
    } else {
        Serial.print("(Unknown PICC Type)\r\n");                
    }
  }

  delay(POLLING_INTERVAL);
}
