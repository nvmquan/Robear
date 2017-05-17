
// Fonction d�tecter qui va mettre en place le protocole de detection
// Code par Benoit Ornat le 28/04/2015


/* INCLURE CI DESSOUS TOUS LES HEADERS A FOURNIR*/
#include <thread>
#include <iostream>

#include "../headers/comMoteur.h"
#include "../headers/protocole_com_serie.h"
#include "../headers/get_file_name.h"
#include "../headers/serial_com.h"
#include "../headers/serialib.h"
#include "../headers/commandes_actionneurs.h"
#include "../headers/calculer_odometrie.h"

using namespace std;
using chrono::system_clock;

/* FIN DES HEADERS */

// DEFINITIONS DE CONSTANTES //

#define tempstourelle 10
#define dureeApresDetection 2000

// Cr�ation de la fonction detecter, qui ne ressort rien
// sensrobot determine dans quel sens le robot va.La valeur vaut 1 pour marche avant, 0 pour marche arriere
// angledetect est l'angle que fait le servomoteur au moment ou le capteur detecte quelque chose.
// Valeuravant est la valeur de detection du capteur avant du robot
// Valeurarriere est la valeur de detection du capteur avant du robot



void detecter (int * sensrobot, int val_capteurs [],float tab_odometrie[])
{
    //cout<<"sens robot"<<*sensrobot<<endl;
    switch (*sensrobot){
        case 1 : // Dans le cas ou notre robot part en marche avant
            if (val_capteurs[1]==0)
            {
                cout<<"robot adverse pris en compte"<<endl;
                comMotDroit(0);
                comMotGauche(0); // Arret des moteurs

                while(val_capteurs[1]==0){
			cout<<"coucou je suis dans la 1ere"<<endl;
                    this_thread::sleep_for(chrono::milliseconds(10));
                    calculer_odometrie(tab_odometrie, 10);
                    receptionserie(val_capteurs);

                }
                int i=0;
                system_clock::time_point now = system_clock::now();
                system_clock::time_point fin = now+std::chrono::milliseconds(dureeApresDetection);
                while (system_clock::now()<fin)
                {
			cout<<"coucou je suis dans le deuxieme "<<endl;
                    calculer_odometrie(tab_odometrie, 10);
                    receptionserie(val_capteurs);
                    if(val_capteurs[1]==0)// ici  clem
                    {
                        i++; // On incr�mente 6 fois pour etre sur d'avoir bien vu l'adversaire mdr
                        while(val_capteurs[1]==0){
				cout<<"coucou je suis dans le troisieme "<<endl;
                            calculer_odometrie(tab_odometrie, 10);
                            receptionserie(val_capteurs);
                            this_thread::sleep_for(chrono::milliseconds(10));
                        }
                        fin = system_clock::now()+std::chrono::milliseconds(dureeApresDetection);
                    }
                }
            }
            break;
            case -1 : // Dans le cas ou notre robot part en marche avant
                if (val_capteurs[2]==0)
                {

                    comMotDroit(0);
                    comMotGauche(0); // Arret des moteurs

                    while(val_capteurs[2]==0){
                        this_thread::sleep_for(chrono::milliseconds(10));
                        calculer_odometrie(tab_odometrie, 10);
                        receptionserie(val_capteurs);

                    }
                    int i=0;
                    system_clock::time_point now = system_clock::now();
                    system_clock::time_point fin = now+std::chrono::milliseconds(dureeApresDetection);
                    while (system_clock::now()<fin)
                    {
                        calculer_odometrie(tab_odometrie, 10);
                        receptionserie(val_capteurs);
                        if(val_capteurs[2]==0)
                        {
                            i++; // On incr�mente 6 fois pour etre sur d'avoir bien vu l'adversaire mdr
                            while(val_capteurs[2]==0){
                                calculer_odometrie(tab_odometrie, 10);
                                receptionserie(val_capteurs);
                                this_thread::sleep_for(chrono::milliseconds(10));
                            }
                            fin = system_clock::now()+std::chrono::milliseconds(dureeApresDetection);
                        }
                    }
                    break;
                }
            }
}
