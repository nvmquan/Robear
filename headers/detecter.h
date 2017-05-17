
// Fonction détecter qui va mettre en place le protocole de detection
// Code par Benoit Ornat le 28/04/2015

#ifndef detecter_H
#define detecter_H

/* INCLURE CI DESSOUS TOUS LES HEADERS A FOURNIR*/

#include "comMoteur.h"
#include "protocole_com_serie.h"
#include "get_file_name.h"
#include "serial_com.h"
#include "serialib.h"
#include "commandes_actionneurs.h"




/* FIN DES HEADERS */

// DEFINITIONS DE CONSTANTES //

#define tempstourelle 10
#define pi 3.14

void detecter (int * sensrobot, int val_capteurs [],float tab_odometrie[]);

#endif // detecter_H