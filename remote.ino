#include <IRremote.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define BUTTON_MIN 1
#define BUTTON_MAX 24

unsigned int getCode(unsigned int pButton) {
  switch(pButton) {
    case 1: return 0xF700FF;
    case 2: return 0xF7807F;
    case 3: return 0xF740BF;
    case 4: return 0xF7C03F;
    case 5: return 0xF720DF;
    case 6: return 0xF7A05F;
    case 7: return 0xF7609F;
    case 8: return 0xF7E01F;
    case 9: return 0xF710EF;
    case 10: return 0xF7906F;
    case 11: return 0xF750AF;
    case 12: return 0xF7D02F;
    case 13: return 0xF730CF;
    case 14: return 0xF7B04F;
    case 15: return 0xF7708F;
    case 16: return 0xF7F00F;
    case 17: return 0xF708F7;
    case 18: return 0xF78877;
    case 19: return 0xF748B7;
    case 20: return 0xF7C837;
    case 21: return 0xF728D7;
    case 22: return 0xF7A857;
    case 23: return 0xF76897;
    case 24: return 0xF7E817;
  }
}

const uint64_t address = 0x44974DE85DLL;
RF24 radio(9, 10);

IRsend irsend;

void sendIR(unsigned int code) {
  for (int i=0; i<3; i++) {
    irsend.sendNEC(code, 32);
    delay(40);
  }
}

void setup() {
  // Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(32);
  radio.setChannel(0x43);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1, address);
  radio.startListening();
  // Serial.println("ready");
}

void loop() {
  while (!radio.available()) delay(10);
  char data[32];
  radio.read(&data, 32);
  int value = atoi(data);
  // Serial.println(value);
  if (value >= BUTTON_MIN && value <= BUTTON_MAX) {
    sendIR(getCode(value));
  }
}
