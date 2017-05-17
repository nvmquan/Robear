//
//  Created by Bassoch & Palmieri on 22/03/2016.
//  Copyright (c) 2016. All rights reserved.
//

#include "../headers/comMoteur.h"
#include "../headers/protocole_com_serie.h"
#include <iostream>

// Commande des différents moteurs (fonctionnent de la même manière)
// prend un commande entre -255 et 255 pour une commande entre la tension min et la tension max
// Limite à cette plage sinon.

//MAJ 8/05/15: adaptation des pin, renommage des fonctions et création d'une fonction pour l'ascenseur.
//MAJ 24/02/16: mise à jour pour la CFR 2016 (Clément)


bool comMotDroit(int val){
    bool reussite=false;
    unsigned char valeurenvoye;
    // adaptation de la valeur à envoyé
    if (val>0)
    {
        if (val>255) valeurenvoye=255;
        else {
            valeurenvoye=val;
        }
        if (GPIO_off(32)) if (PWM(2,valeurenvoye)) reussite=true;
    }
    else
    {
        if (val<-255) valeurenvoye=255;
        else {
            valeurenvoye=255+val;
        }
        if (GPIO_on(32)) if (PWM(2,valeurenvoye)) reussite=true;
    }
    // envoi des données
    return reussite;
}

bool comMotGauche(int val){
    bool reussite=false;
    unsigned char valeurenvoye;
    // adaptation de la valeur à envoyé
    if (val>0)
    {
        if (val>255) valeurenvoye=255;
        else {
            valeurenvoye=val;
        }
        if (GPIO_off(34)) if (PWM(3,valeurenvoye)) reussite=true;
    }
    else
    {
        if (val<-255) valeurenvoye=255;
        else {
            valeurenvoye=255+val;
        }
        if (GPIO_on(34)) if (PWM(3,valeurenvoye)) reussite=true;
    }
    // envoi des données
    return reussite;
}

bool comPouPlaque(int val){
    bool reussite=false;
    unsigned char valeurenvoye;
    // adaptation de la valeur à envoyé
    if (val>0)
    {
        if (val>255) valeurenvoye=255;
        else {
            valeurenvoye=val;
        }
        if (GPIO_off(38)) if (PWM(5,valeurenvoye)) reussite=true;
    }
    else
    {
        if (val<-255) valeurenvoye=255;
        else {
            valeurenvoye=255+val;
        }
        if (GPIO_on(38)) if (PWM(5,valeurenvoye)) reussite=true;
    }
    // envoi des données
    return reussite;
}


bool comPouPince(int val){
    bool reussite=false;
    unsigned char valeurenvoye;
    // adaptation de la valeur à envoyé
    if (val>0)
    {
        if (val>255) valeurenvoye=255;
        else {
            valeurenvoye=val;
        }
        if (GPIO_off(36)) if (PWM(4,valeurenvoye)) reussite=true;
    }
    else
    {
        if (val<-255) valeurenvoye=255;
        else {
            valeurenvoye=255+val;
        }
        if (GPIO_on(36)) if (PWM(4,valeurenvoye)) reussite=true;
    }
    // envoi des données
    return reussite;
}
