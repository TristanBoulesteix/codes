#include <VirtualWire.h>

int RF_TX_PIN = 2;

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

messageHeader getHeader(byte* message, messageHeader head) {
  head.checksum = calcCheckSum(String((char*) message));

  return head;
}

void setup() {
  Serial.begin(9600);
  vw_set_tx_pin(RF_TX_PIN);

  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);

  Serial.println("Go !");
}

void loop() {
  byte message[VW_MAX_MESSAGE_LEN];
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
  messageHeader head;

  // Lit un message de maximum 26 caractères depuis le port série
  int len = Serial.readBytesUntil('\n', (char*) message, VW_MAX_MESSAGE_LEN - 1);
  if (!len) {
    return; // Pas de message
  }

  head = getHeader(message, head);

  String finalMessage = String(head.id) + String((char*) message) + String(head.checksum);

  finalMessage = finalMessage + '\0'; // Ferme la chaine de caractères

  for (int i = 0; i < finalMessage.length(); i++) {
    message[i] = finalMessage.charAt(i);
  }

  vw_send(message, finalMessage.length() + 1); // On envoie le message
  vw_wait_tx(); // On attend la fin de l'envoi
}
