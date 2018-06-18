/**

  Exemple de code pour la bibliothèque VirtualWire – Serveur d'envoi de texte

*/



#include <VirtualWire.h>


int RF_RX_PIN = 2;

/**
   Exemple de code pour la bibliothèque VirtualWire – Serveur d'envoi de texte
*/

#include <VirtualWire.h>

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
  byte message[VW_MAX_MESSAGE_LEN];
  byte taille_message = VW_MAX_MESSAGE_LEN;
  // N.B. La constante VW_MAX_MESSAGE_LEN est fournie par la lib VirtualWire

  /*
    La variable "taille_message" doit impérativement être remise à
    la taille du buffer avant de pouvoir recevoir un message.
    Le plus simple est d'utiliser une variable locale pour ne pas
    avoir à réassigner la valeur à chaque début de loop().
  */

  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message(message, &taille_message)) {
    // On copie le message, qu'il soit corrompu ou non

    Serial.println((char*) message); // Affiche le message
  }
}
