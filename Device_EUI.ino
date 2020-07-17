#include <MKRWAN.h>
LoRaModem modem;

void setup() {


    Serial.begin(115200);   // ouvre le port série USB à 9600 baud    

// Setup LoRa    

    // Vérification du démarrage du module LoRa.

    if (!modem.begin(EU868)) {

      Serial.println("Echec du démarrage du module");}
    else {
      Serial.println(" J'ai réussi à me connecter");
    }

    Serial.println("voici la version :"); 
    Serial.println(modem.version());
    Serial.print("L'EUI (End-device Unique Identifier) est: ");
    
    Serial.println(modem.deviceEUI());

}

void loop (){};
