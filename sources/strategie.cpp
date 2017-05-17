//
//  Created by Bassoch & Palmieri on 22/03/2016.
//  Copyright (c) 2016. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <ratio>
#include <ctime>
#include <mutex>
#include <math.h>


#include "../headers/strategie.h"
#include "../headers/calculer_odometrie.h"
#include "../headers/protocole_com_serie.h"
#include "../headers/eqep.h"
#include "../headers/comMoteur.h"
#include "../headers/commandes_actionneurs.h"
#include "../headers/deplacement.h"


// fonction stratégie pour homologation

using namespace std;

void strategie(int valCapteur[7]){
    int vitesseDeplacement(150),vitesseApproche(100);
    float tabOdometrie[]={0,0,0,0,0,0,0};
    const float angle1=M_PI/4;
    int sleeping_time = 250;
    cout<<"début du déplacement"<<endl;

    tabOdometrie[0]=0;
    tabOdometrie[1]=0;
    tabOdometrie[2]=0;

    if ( valCapteur[8]==0){ //////// violet - NOUS : jaune /////////////

//Positionnement du robot pour récupérer cyindre de la tour
cout<<"First phase\n"<<endl;
    asserTourner(-37, 0.4, 1, tabOdometrie, valCapteur);            //Rotation -37°
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.242, 0.4, 1, tabOdometrie, valCapteur, 1);          //Reculer 242 mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    asserTourner(37, 0.4, 1, tabOdometrie, valCapteur);            //Rotation 37°
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of first phase\n"<<endl;

//Récupérer et stockage 1e cylindre de la tour
cout<<"Second phase\n"<<endl;
    descendre_pince();                                            //Descendre et ouvrir la pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.05, 0.2, -1, tabOdometrie, valCapteur, 1);         //Avancer 50mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    fermer_pince();                                                //Serrer Pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.05, 0.2, 1, tabOdometrie, valCapteur, 1);         //Reculer 50mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(100*sleeping_time)); //faut attendre que la pince soit descendu suffisamentre
    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.05, 0.2, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of second phase\n"<<endl;

//Récupérer et stockage  2e et 3e cylindre de la tour
cout<<"Third phase\n"<<endl;
for(int i = 0; i < 2; i++){

    fermer_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.05, 0.2, 1, tabOdometrie, valCapteur, 1);         //reculer 50mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //petit angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(100*sleeping_time));
    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.05, 0.2, 1, tabOdometrie, valCapteur, 1);         //avancer 50mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    cout<< i+1 <<"e cylindre stocké \n"endl;
}
cout<<"End of third phase\n"<<endl;

//Récupération et stockage ede la 4e cylindre
cout<<"Fourth phase\n"<<endl;
    fermer_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.358, 0.2, 1, tabOdometrie, valCapteur, 1);         //reculer 358mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                               //petit angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(100*sleeping_time)); //attend que la pince sorte du robot
    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince();                                                 //monter pince afin de se déplacer
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of fourth phase\n"<<endl;

//Déplacement vers les rails latérale et dépot du premier cylindre et le deuxieme
cout<<"Fifth phase\n"<<endl;
    asserTourner(-90, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(1.56, 0.4, -1, tabOdometrie, valCapteur, 1);            //Avancer 1560mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(90, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // basculer_cylindre_bas();                                        //dépot 1er cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

    ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);            //Reculer 100 mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 2e cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

    asserTourner(-30, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of fifth phase\n"<<endl;

//Récupération du CS1
cout<<"Sixth phase\n"<<endl;
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));    //attendre 1s et ouvre pince
    ouvrir_pince();                                                   //grand angle
    this_thread::sleep_for(chrono::milliseconds(6*sleeping_time));

    fermer_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ouvrir_pince();                                                   //petit angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of sixth phase\n"<<endl;

//Dépot du 2e 3e 4e cylindre
cout<<"Seventh phase\n"<<endl;
    asserTourner(30, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 2e cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

    ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 3e cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

    ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 4e cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

cout<<"End of sevnth phase\n"<<endl;

//Positionnement du robot pour récupérer les boules de la zone du coin
cout<<"Eighth phase\n"<<endl;
    ligneDroite(0.216, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 216mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(27, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.042, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 42mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Récupération boules grand emplacement

    // descendre_plaque();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // monter_plaque();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    recuperer_boules();

//Positionnement du robot pour déposer les boules

    ligneDroite(0.108, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(159, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.725, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Racler les boules sur le bord

    descendre_plaque();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.19, 0.4, -1 tabOdometrie, valCapteur, 1);        //avancer de 190mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_plaque();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of eighth phase\n"<<endl;

// Récupération boules petit emplacement et ldépot
cout<<"Nineth phase\n"<<endl;
    asserTourner(66, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.075, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // descendre_plaque();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // monter_plaque();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    recuperer_boules();

//Positionnemenr du robot pour déposer les boules

    ligneDroite(0.075, 0.4, -1, tabOdometrie, valCapteur, 1);
    his_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(-66, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.190, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Dépot des boules et début positionement du robot

    descendre_plaque();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.725, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_plaque();
    tthis_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of nineth phase\n"<<endl;

//Positionnement pur récupérer le CS2 et cylindre plateau puis les déposer dans les rails du centre
cout<<"Tenth phase\n"<<endl;
    asserTourner(-42, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.367, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Récupération cylindre plateau
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));
    ouvrir_pince();                                                 //une fois sorti du robot, grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    fermer_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                                 //petit angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince();
    this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Positionnement du robot pour déposer les cylindres dans les rails du centre

    asserTourner(-9.5, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.2875, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(10, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 1er cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

    ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // basculer_cylindre_bas();                                        //dépot 2e cylindre
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // redresser_bascule_bas();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();

cout<<"End of tenth phase\n"<<endl;
    }
    else{ //////////////////////////// vert - NOUS : bleu ////////////////



    }

}
