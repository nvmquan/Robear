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

    //ligneDroite(1, 0.4, -1, tabOdometrie, valCapteur, 1);          //Reculer 242 mm
    //this_thread::sleep_for(chrono::milliseconds(sleeping_time));



    if ( valCapteur[8]==0){ //////// violet - NOUS : jaune /////////////


// TEST 1
// asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner2(90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner2(-90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner2(90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// asserTourner2(-90, 0.3, 1, tabOdometrie, valCapteur);
// this_thread::sleep_for(chrono::milliseconds(sleeping_time));


// TEST 2

/*asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));


// TEST 3

asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));


// TEST 4

asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));*/


// TEST 5
/*
ligneDroite(0.50, 0.3, 1, tabOdometrie, valCapteur, 0);
this_thread::sleep_for(chrono::milliseconds(sleeping_time));
ligneDroite(0.50, 0.3, 1, tabOdometrie, valCapteur, 0);
this_thread::sleep_for(chrono::milliseconds(sleeping_time))
ligneDroite(0.50, 0.3, 1, tabOdometrie, valCapteur, 0);
this_thread::sleep_for(chrono::milliseconds(sleeping_time))
ligneDroite(0.50, 0.3, 1, tabOdometrie, valCapteur, 0);
this_thread::sleep_for(chrono::milliseconds(sleeping_time))
*/





//Positionnement du robot pour récupérer cyindre de la tour
cout<<"First phase\n"<<endl;
    asserTourner(-55, 0.3, 1, tabOdometrie, valCapteur);            //Rotation -55°
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.36, 0.3, 1, tabOdometrie, valCapteur, 1);          //Reculer 360 mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    asserTourner(54, 0.3, 1, tabOdometrie, valCapteur);            //Rotation 55°
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

cout<<"End of first phase\n"<<endl;



//Récupérer et stockage 1e cylindre de la tour
cout<<"Second phase\n"<<endl;
    descendre_pince(valCapteur);                //Descendre et ouvrir la pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // On chope le 1er
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.058, 0.2, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    fermer_pince();                                                //Serrer Pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.10, 0.2, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    descendre_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));


    // On chope le 2eme
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.11, 0.2, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    fermer_pince();                                                //Serrer Pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.1, 0.2, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    descendre_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));


    // On chope le 3eme
    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.11, 0.2, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    fermer_pince();                                                //Serrer Pince
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ligneDroite(0.1, 0.2, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    ouvrir_pince();                                               //grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    descendre_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // On chope le 4eme
    // ouvrir_pince();                                               //grand angle
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // ligneDroite(0.1, 0.4, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // fermer_pince();                                                //Serrer Pince
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    ligneDroite(0.3, 0.2, 1, tabOdometrie, valCapteur, 1);     //Reculer 350mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // monter_pince(valCapteur);
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // ouvrir_pince();                                               //grand angle
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));


// DEPOSR LES CLINDRES DANS ZONE DE DEPART

    TournerGaucheBO(80,1080);           //Rotation -37°
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    deposer_cylindre();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    // descendre_pince(valCapteur);
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament
    //
    // basculer_cylindre_haut();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // redresser_bascule_haut();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // deposer_cylindre();
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));

cout<<"End of second phase\n"<<endl;


//
//
// //Déplacement vers les rails latérale et dépot du premier cylindre et le deuxieme
// cout<<"Fifth phase\n"<<endl;
//
//     TournerGaucheBO(-80,730);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     ligneDroite(0.8, 0.4, -1, tabOdometrie, valCapteur, 0);            //Avancer 800mm
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     TournerGaucheBO(-80,730);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // asserTourner(80, 0.4, 1, tabOdometrie, valCapteur);
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // ligneDroite(0.8, 0.4, 1, tabOdometrie, valCapteur, 0);            //Avancer 1560mm
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // asserTourner(-80, 0.4, 1, tabOdometrie, valCapteur);
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // basculer_cylindre_bas();                                        //dépot 1er cylindre
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // redresser_bascule_bas();
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     deposer_cylindre();
//
//     ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);            //Reculer 100 mm
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     deposer_cylindre();                                                //dépot 2e cylindre


/// RECUPERER CYLINDRE A COTE
//     asserTourner(-30, 0.4, 1, tabOdometrie, valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// cout<<"End of fifth phase\n"<<endl;
//
// //Récupération du CS1
// cout<<"Sixth phase\n"<<endl;
//     descendre_pince(valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));    //attendre 1s et ouvre pince
//     ouvrir_pince();                                                   //grand angle
//     this_thread::sleep_for(chrono::milliseconds(6*sleeping_time));
//
//     fermer_pince();
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     monter_pince(valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     ouvrir_pince();                                                   //petit angle
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     descendre_pince(valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     basculer_cylindre_haut();
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     redresser_bascule_haut();
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     monter_pince(valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
// cout<<"End of sixth phase\n"<<endl;
//
// //Dépot du 2e 3e 4e cylindre
// cout<<"Seventh phase\n"<<endl;
//     asserTourner(30, 0.4, 1, tabOdometrie, valCapteur);
//     this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//
//     // basculer_cylindre_bas();                                        //dépot 2e cylindre
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
//     // redresser_bascule_bas();
//     // this_thread::sleep_for(chrono::milliseconds(sleeping_time));


    // ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 100mm
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // deposer_cylindre();                                        //dépot 3e cylindre
    //
    // ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);         //reculer de 100mm
    // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // // basculer_cylindre_bas();                                        //dépot 4e cylindre
    // // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    // // redresser_bascule_bas();
    // // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    //
    // deposer_cylindre();

cout<<"End of sevnth phase\n"<<endl;











/*
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

    recuperer_boules(valCapteur);

//Positionnement du robot pour déposer les boules

    ligneDroite(0.108, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(159, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.725, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Racler les boules sur le bord

    descendre_plaque(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.19, 0.4, -1, tabOdometrie, valCapteur, 1);        //avancer de 190mm
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_plaque(valCapteur);
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

    recuperer_boules(valCapteur);

//Positionnemenr du robot pour déposer les boules

    ligneDroite(0.075, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    asserTourner(-66, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.190, 0.4, 1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Dépot des boules et début positionement du robot

    descendre_plaque(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.725, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_plaque(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
cout<<"End of nineth phase\n"<<endl;

//Positionnement pur récupérer le CS2 et cylindre plateau puis les déposer dans les rails du centre
cout<<"Tenth phase\n"<<endl;
    asserTourner(-42, 0.4, 1, tabOdometrie, valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ligneDroite(0.367, 0.4, -1, tabOdometrie, valCapteur, 1);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

//Récupération cylindre plateau
    descendre_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));
    ouvrir_pince();                                                 //une fois sorti du robot, grand angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    fermer_pince();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    monter_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    ouvrir_pince();                                                 //petit angle
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    descendre_pince(valCapteur);
    this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));

    basculer_cylindre_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));
    redresser_bascule_haut();
    this_thread::sleep_for(chrono::milliseconds(sleeping_time));

    monter_pince(valCapteur);
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

*/
    }
    else{ //////////////////////////// vert - NOUS : bleu ////////////////
      //Positionnement du robot pour récupérer cyindre de la tour
      cout<<"First phase\n"<<endl;
          asserTourner(40, 0.3, 1, tabOdometrie, valCapteur);            //Rotation -55°
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.26, 0.3, 1, tabOdometrie, valCapteur, 0);          //Reculer 360 mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          asserTourner(-41, 0.3, 1, tabOdometrie, valCapteur);            //Rotation 55°
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

      cout<<"End of first phase\n"<<endl;



      //Récupérer et stockage 1e cylindre de la tour
      cout<<"Second phase\n"<<endl;
          descendre_pince(valCapteur);                //Descendre et ouvrir la pince
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          // On chope le 1er
          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.06, 0.4, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          fermer_pince();                                                //Serrer Pince
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.10, 0.4, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

          basculer_cylindre_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          redresser_bascule_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));


          // On chope le 2eme
          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.1, 0.4, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          fermer_pince();                                                //Serrer Pince
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

          basculer_cylindre_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          redresser_bascule_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));


          // On chope le 3eme
          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.1, 0.4, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          fermer_pince();                                                //Serrer Pince
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.1, 0.4, 1, tabOdometrie, valCapteur, 1);     //Reculer 100mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ouvrir_pince();                                               //grand angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

          basculer_cylindre_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          redresser_bascule_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          // On chope le 4eme
          // ouvrir_pince();                                               //grand angle
          // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          //
          // ligneDroite(0.1, 0.4, -1, tabOdometrie, valCapteur, 0);         //Avancer 100mm
          // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          //
          // fermer_pince();                                                //Serrer Pince
          // this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          //
          ligneDroite(0.3, 0.4, 1, tabOdometrie, valCapteur, 1);     //Reculer 350mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          // ouvrir_pince();                                               //grand angle
          // this_thread::sleep_for(chrono::milliseconds(sleeping_time));


      // DEPOSR LES CLINDRES DANS ZONE DE DEPART
          /*asserTourner(-37, 0.3, 1, tabOdometrie, valCapteur);            //Rotation -37°
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ligneDroite(0.30, 0.3, 1, tabOdometrie, valCapteur, 0);          //Reculer 242 mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          asserTourner(-90, 0.3, 1, tabOdometrie, valCapteur);            //Rotation -37°
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          deposer_cylindre();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          deposer_cylindre();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          deposer_cylindre();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          deposer_cylindre();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time)); //faut attendre que la pince soit descendu suffisament

          basculer_cylindre_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          redresser_bascule_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          deposer_cylindre();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

      cout<<"End of second phase\n"<<endl;

      */



      //Déplacement vers les rails latérale et dépot du premier cylindre et le deuxieme
      cout<<"Fifth phase\n"<<endl;
          asserTourner2(-80, 0.4, 1, tabOdometrie, valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          ligneDroite(0.8, 0.4, 1, tabOdometrie, valCapteur, 0);            //Avancer 1560mm
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          asserTourner2(80, 0.4, 1, tabOdometrie, valCapteur);
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

          asserTourner(30, 0.4, 1, tabOdometrie, valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
      cout<<"End of fifth phase\n"<<endl;

      //Récupération du CS1
      cout<<"Sixth phase\n"<<endl;
          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(4*sleeping_time));    //attendre 1s et ouvre pince
          ouvrir_pince();                                                   //grand angle
          this_thread::sleep_for(chrono::milliseconds(6*sleeping_time));

          fermer_pince();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          ouvrir_pince();                                                   //petit angle
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          descendre_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          basculer_cylindre_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
          redresser_bascule_haut();
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));

          monter_pince(valCapteur);
          this_thread::sleep_for(chrono::milliseconds(sleeping_time));
      cout<<"End of sixth phase\n"<<endl;

      //Dépot du 2e 3e 4e cylindre
      cout<<"Seventh phase\n"<<endl;
          asserTourner(-30, 0.4, 1, tabOdometrie, valCapteur);
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
    }

}
