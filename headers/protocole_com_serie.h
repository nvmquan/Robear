//
//  protocole_com_serie.h
//  
//
//  Created by Sylvain Richard on 13/02/2015.
//  Update by Sylvain Richard on 27/03/2015

//  Protocole de communication complet disponible sur le drive.
//
//  Configuration préalable:
//  Attention: les tensions logiques sont différentes entre la beagle et l'arduino, il faut passer par un convertisseur
//  Brancher le tx1 de la carte cible au port 9 pin 26, et le rx1 au port 9 pin 24

// Attention: copier les fichier suivants dans /lib/firmware/ si ils n'y sont pas encore:
//  http://s3.armhf.com/boards/bbb/dt/ttyO1_armhf.com-00A0.dtbo
//  http://s3.armhf.com/boards/bbb/dt/ttyO2_armhf.com-00A0.dtbo
//  http://s3.armhf.com/boards/bbb/dt/ttyO4_armhf.com-00A0.dtbo
//  http://s3.armhf.com/boards/bbb/dt/ttyO5_armhf.com-00A0.dtbo



#ifndef ____protocole_com_serie__
#define ____protocole_com_serie__

// initialisation (aucune commande ne sera prise en compte avant que cette fonction ne soit exécutée)

int protocole_com_serie_init();

//mets une sortie à 1:
int GPIO_on (char numero_de_port);

//met une sortie à 0:
int GPIO_off (char numero_de_port);

//met une PWM à la valeur demandée (entre 0 et 255)
int PWM(char numero_de_port,char rapport_cyclique);

// Mets le servo moteur dans la position demandée
int servo(char numero_de_servo,char angle);

// Fonction a lancer en tant que thread pour récupérer les informations capteurs de l'arduino.
int receptionserie(int val_capteurs[]);

#endif /* defined(____protocole_com_serie__) */