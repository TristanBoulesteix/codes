#include <VirtualWire.h>

const int RF_TX_PIN = 2;

char inputBuffer[10];

typedef struct header {
  int id = 6500;
  int checksum;
} messageHeader;

int calcCheckSum(String message) {
  int checkSum;
  for (int i = 0; i < message.length(); i++) {
    checkSum = checkSum + (((int) message.charAt(i)) * i);
  }
  return checkSum;
}

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);
}

void loop() {
  String message;

  while (true) {
    if (Serial.available() > 0) {
      Serial.readBytes(inputBuffer, 10);

      delay(5000);
    }
  }

  vw_send((byte *) &message, sizeof(message));
  vw_wait_tx();
}
