//
//  Created by Bassoch & Palmieri on 22/03/2016.
//  Copyright (c) 2016. All rights reserved.
//

#include "../headers/protocole_com_serie.h"
#include "../headers/serialib.h"
#include <unistd.h>
#include <string>
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

// mise en place d'un mutex limitant l'acces en écriture au port série a une tache à la fois
mutex mut_serie;

//cablage port série numéro 1: port 9, tx:pin24, rx:pin 26
serialib serial (1, 115200);

/*!
 \brief  Initialise la communication série. A faire avant toute autre fonction!
 \return 1 succes
 \return -1 erreur dans la communication
 \return -2 confirmation d'initalisation non reçu
 */

int protocole_com_serie_init()
{
    mut_serie.lock();
    // vidage du buffer avant de commencer à communiquer
    serial.FlushReceiver();

    //envoi du message d'initalisation
    const char initialisation[]={'o','k'};
    char reponse[2];
    if (serial.Write(initialisation, sizeof(initialisation))!=1) {
        mut_serie.unlock();
        return -1;
    }
    //attente et vérification de la réponse
    if (serial.Read(reponse, 2,10)!=1) {
        mut_serie.unlock();
        return -1;
    }
    if ((reponse[0]!=initialisation[0])||(reponse[1]!=initialisation[1])) {
        mut_serie.unlock();
        return -2;
    }
    mut_serie.unlock();
    return 1;
}


//GPIOS:

/*!
 \brief  mets la sortie "numero de port" à 1
 \return 1 success
 \return -1 problème envoi message série
 */
int GPIO_on (char numero_de_port){
    mut_serie.lock();
    const char message[]={'a',numero_de_port};
    if (serial.Write(message,sizeof(message))!=1) {
        mut_serie.unlock();
        return -1;
    }
    mut_serie.unlock();
    return 1;
}

/*!
 \brief  mets la sortie "numero de port" à 0
 \return 1 success
 \return -1 problème envoi message série
 */
int GPIO_off (char numero_de_port){
    mut_serie.lock();
    const char message[]={'b',numero_de_port};
    if (serial.Write(message,sizeof(message))==1){
        mut_serie.unlock();
        return -1;
    }
    mut_serie.unlock();
    return 1;
}

/*!
 \brief  mets la sortie "numero de port" à la PWM demandée (entre 0 et 255 pour un rapport cyclique en sortie entre 0 et 100%);
 \return 1 success
 \return -1 problème envoi message série
 */
int PWM(char numero_de_port,char rapport_cyclique){
    mut_serie.lock();
    const char message[]={'c',rapport_cyclique,numero_de_port};
    if (serial.Write(message,sizeof(message))==1) {
        mut_serie.unlock();
        return -1;
    }
    mut_serie.unlock();
    return 1;
}

/*!
 \brief  Commande le servo numéro 'numero_de_servo' à l'angle demandée. Attention à bien avoir initialisé le servo en question sur l'arduino.
 \return 1 success
 \return -1 problème envoi message série
 */
int servo (char numero_de_servo, char angle){
    mut_serie.lock();
    const char message[]={'i',numero_de_servo,angle};
    if (serial.Write(message,sizeof(message))==1) {
        mut_serie.unlock();
        return -1;
    }
    mut_serie.unlock();
    return 1;
}

/*!
 \brief  Lit et traite les informations recu de l'arduino.
 \param un tableau de caractères reprenant l'état des capteurs.
 Attention: Les trois premières cases du tableau sont réservées à la detection du robot adverse:
 [0] angle lors de la dernière detection, [2] capt arrière, [1] capt avant

 Fonction à lancer dans un thread. Devra être modifiée pour s'adapter à la structure multitache du programme.
 */

int receptionserie(int val_capteurs[]){
    char reception[4]={0,0,0,0};
       while (serial.ReadCharInstant(reception)==1){
        switch (reception[0]) {
            //cas changement d'état du capteur
            case 'k':
                serial.Read(reception+1, 2,10);
                val_capteurs[reception[1]+1]=reception[2];
                cout << "valeur "<<(int) reception[2]<<" du capteur " <<(int) reception[1]+1<<endl;
                break;
            //cas détection du robot adverse
            case 'l':
                serial.Read(reception+1, 3,100);
                val_capteurs[0]=reception[1];
                val_capteurs[1]=reception[2];
                val_capteurs[2]=reception[3];
                cout << "robot detecte "<<(int) reception[1]<<" "<<(int) reception[2]<<" "<< (int) reception[3]<<endl;
                break;
            default:
                cout<<"commande non reconnue "<<reception[0]<<endl;
                break;

        }
           return 1;
    }
    return 0;
}
