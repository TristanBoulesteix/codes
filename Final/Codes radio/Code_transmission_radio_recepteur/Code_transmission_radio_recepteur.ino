#include <VirtualWire.h>

//Integer
int RF_RX_PIN = 2;
int check;


//Structure
typedef struct header {
  String id;
  String instruction;
  String checksum;
} messageHeader;

//Variable
messageHeader comparatif;
String msg;

int calcCheckSum(String message) {
  int checkSum;
  for (int s = 0; s < message.length(); s++) {
    checkSum = checkSum + (((int) message.charAt(s)) * (s+1));
  }
  Serial.println(checkSum);
  return checkSum;
}


void setup() {
  Serial.begin(9600);
  vw_set_rx_pin(RF_RX_PIN);
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(255);
  vw_rx_start(); // On peut maintenant recevoir des messages
  Serial.println("Go !");
}

void loop() {
  byte header[VW_MAX_MESSAGE_LEN];
  byte taille_message = VW_MAX_MESSAGE_LEN;
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire
  // On attend de recevoir un message
  vw_wait_rx();
  if (vw_get_message(header, &taille_message)) {
    Serial.println("Message recu");
    msg=String((char*)header);
    Serial.println(msg);
    int a=0;
        for( int i=0; i<msg.length();i++){
          if (msg.charAt(i)== '|'){
            a++;
            i++;
          }
          if (a==0){
            comparatif.id+=msg.charAt(i);
          }else if (a==1){
            comparatif.instruction+= msg.charAt(i);
          }else if (a==2){
            comparatif.checksum+=msg.charAt(i);
          }
        }
        check = calcCheckSum(comparatif.instruction);
        if (comparatif.id == String(6500)){
          if (comparatif.checksum==String(check))
          {
            Serial.println("Message Correct");
            Serial.println(comparatif.instruction);
          }else{
            Serial.println("Error different checksum");
            Serial.println(comparatif.checksum);
    
          }
        }else{
          Serial.println("Error different ID");
          Serial.println(comparatif.id);
        }
      }else {
        Serial.println("Message corrompu"); // Affiche le message
  }
  comparatif.id="";
  comparatif.checksum="";
  comparatif.instruction="";
  
}
