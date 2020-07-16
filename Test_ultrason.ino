// Editeur : Marie BODIN
// Commencé le 15/07/2020


#include <hcsr04.h>


#define TRIG_PIN 6
#define ECHO_PIN 7

#define SECRET_APP_EUI "Votre EUI" // TTN
#define SECRET_APP_KEY "Votre APP KEY" // TTN



/******************************************************************************

Module LoRa Arduino MKR WAN 1300 - https://www.arduino.cc/en/Tutorial/MKRWANFirstConfiguration

*******************************************************************************/

#include <MKRWAN.h>

LoRaModem modem;

String msg; 

float distance;

bool sent;



HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);



//---------------------------------------------------------------

void setup()

{

    Serial.begin(115200);   // ouvre le port série USB à 115200 baud    



// Setup LoRa    

    // Vérification du démarrage du module LoRa.

    if (!modem.begin(EU868)) {

      Serial.println("Echec du démarrage du module");

      while (1) {}

    };

   

    // Affichage de la version du firmware de l'Arduino MKR WAN 1300

    Serial.print("La version du firmware de l'Arduino MKR WAN 1300 est: ");

    Serial.println(modem.version());

    // Affichage de l'EUI (End-device Unique Identifier)

    Serial.print("L'EUI (End-device Unique Identifier) est: ");

    Serial.println(modem.deviceEUI());


    // Connexion au réseau LoRa en mode OTAA

    int connected = modem.joinOTAA(SECRET_APP_EUI, SECRET_APP_KEY);

    if (!connected) {

      Serial.println("Un problème est survenu; êtes vous à l'intérieur? Déplacez-vous près d'une fenêtre et réessayez");

      while (1) {}

  }

  Serial.println("Vous avez réussi à vous connecter au réseau LoRa !");
  modem.setADR(true);
  modem.dataRate(1);

}



//---------------------------------------------------------------





//---------------------------------------------------------------



//---------------------------------------------------------------

void sendInfo()

{

// Cette fonction envoie les mesures vers un réseau LoRa



  // Mise en forme du message

  msg= distance ;



  // Envoi du message vers le port série

  Serial.println();

  Serial.print("Envoi: " + msg + " - ");

  // Conversion hexadecimale

  for (unsigned int i = 0; i < msg.length(); i++) {

    Serial.print(msg[i] >> 4, HEX);

    Serial.print(msg[i] & 0xF, HEX);

    Serial.print(" ");

  }

  Serial.println();



  // Envoi du message vers le réseau LoRa

  int err;

  modem.beginPacket();

  modem.write(msg); // anciennement modem.print

  err = modem.endPacket(false);

  // Vérification

  if (err > 0) {

    Serial.println("Message bien envoyé :-)");
    Serial.println();
  } 
  
  else {

    Serial.println("Erreur lors de l'envoi du message :-(");

    Serial.println();

  }

}



//---------------------------------------------------------------

void loop()

{

// Programme principal
    
  Serial.print("Distance : ");
    
  int duree = hcsr04.echoInMicroseconds();

  distance = (duree / 2) * 0.344; //0.344 vitesse du son (340 / 1000)



  Serial.print(distance);

  // Serial.print(hcsr04.distanceInMillimeters());

  Serial.print(" mm");


  delay(1000);

    // Envoie les données sur le réseau LoRa

    sendInfo();


    // Pause de X millisecondes

    delay(120000); // mesure toutes les 2 min

}
