#include <VirtualWire.h>

//Integer
int RF_RX_PIN = 2;

// String
String instruction = " ";


//Structure
typedef struct header {
  int id;
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
  vw_set_rx_pin(RF_RX_PIN);
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // On peut maintenant recevoir des messages
  Serial.println("Go !");
}

void loop() {
  messageHeader comparatif;
  String header="6900|DROITE|3654";
  byte taille_message = VW_MAX_MESSAGE_LEN;
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
  // On attend de recevoir un message
  //vw_wait_rx();
  if (vw_get_message((byte*)&header, &taille_message)) {
    Serial.println("Message recu");
    for( int i=0; i<header.length();i++){
      int a=0;
      if (header.charAt(i)== '|'){
        a++;
        i++;
      }
      if (a==0){
        comparatif.id+=header.charAt(i);
      }else if (a==1){
        instruction+= header.charAt(i);
      }else if (a==2){
        comparatif.checksum+=header.charAt(i);
      }
      Serial.println(comparatif.id);
      Serial.println(instruction);
      Serial.println(comparatif.checksum);
    }
  }else {
    Serial.println("Message corrompu"); // Affiche le message
  }
}
