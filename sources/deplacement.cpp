//
//  Created by Bassoch & Palmieri on 22/03/2016.
//  Copyright (c) 2016. All rights reserved.
//


#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <fstream>
#include "../headers/comMoteur.h"
#include "../headers/protocole_com_serie.h"
#include "../headers/deplacement.h"
#include "../headers/calculer_odometrie.h"
#include "../headers/detecter.h"
#include "../headers/eqep.h"

using namespace std;

#define rapportDeRampeRotation 10
#define conditionArretRotation 3
#define Te 20
const float R_Roue_codeuse=(5/2)*0.01;

int cmd_moteur_gauche=0;
int cmd_moteur_droit=0;
float erreurGauche=0;
float erreurDroite=0;
float erreurd_maitre_esclave=0;

void calculerAngleEtdistance(float tab_odometrie [],float xDesire,float yDesire,float* d,float* angle){
    float x=tab_odometrie[0],y=tab_odometrie[1];
    float deltaX=(xDesire-x),deltaY=(yDesire-y);
    cout<<" x = "<<x<<" xDesire =  "<<xDesire<<" DeltaX = "<<deltaX<<"\ny = "<<y<<" yDesire = "<<yDesire<<" Delta Y = "<<deltaY<<endl;
    *d=sqrtf(deltaX*deltaX+deltaY*deltaY);
    cout<<" distance = "<<*d<<endl;
    if(deltaX<0.1)
    {
deltaX=0;
    }
    else{}
  if(deltaY<0.1)
{
  deltaY=0;
}
else{}

    if (abs((-acosf(deltaX/ *d)*180/M_PI))<2)
     {
      *angle=0;
      }
    else{
          if (deltaX>0 && deltaY>0)
          {
            *angle=-acosf(deltaY/ *d)-(13*(M_PI/180));
            cout<<" angle "<<*angle*(180/M_PI)<<endl;
          }
          if(deltaX<0 && deltaY>0)
          {
            *angle=+acosf(deltaY/ *d)+(13*(M_PI/180));
            cout<<" angle "<<*angle*(180/M_PI)<<endl;
          }
          if(deltaX>0 && deltaY<0)
          {
	   *angle=-acosf(deltaX/ *d)-(13*(M_PI/180));
            cout<<" angle "<<*angle*(180/M_PI)<<endl;
          }
          if(deltaX<0 && deltaY<0)
          {
            *angle=+(M_PI/2)+acosf(deltaX/ *d)+(13*(M_PI/180));
            cout<<" angle "<<*angle*(180/M_PI)<<endl;
          }

        }
  }

  void asserTourner (float angleDemande, float vitesseDemande, int sens, float tab_odometrie [], int val_capteurs[])
  {

    float variation_erreur=0;
    float vitesseGauche, vitesseDroite, erreurGauche, erreurDroite,somme_erreurs_droite,somme_erreurs_gauche, erreurd_maitre_esclave, somme_erreurs_maitre_esclave, variation_erreur_gauche,variation_erreur_droite;
    int Kpg, Kig, Kdg, Kpd, Kid, Kdd;

    float coefficient_rampe_decroissant = vitesseDemande/((1.0/3.0)*angleDemande);
    float coefficient_rampe_croissant=(vitesseDemande-0.3)/((1.0/3.0)*angleDemande);
    extern eQEP eqep1;
    extern eQEP eqep2;
    eqep1.set_position(0);           //Raz des registres contenant les nombres d'increments
    eqep2.set_position(0);

    Kpg=250;
    Kig=500;
    Kdg=0;

    Kpd=200;
    Kid=3000;
    Kdd=0;

    somme_erreurs_droite=0;
    somme_erreurs_gauche=0;



    float position_n_moins_1_roue2 = tab_odometrie[5];
    float position_n_moins_1_roue1 = tab_odometrie[3];
    float orientation_initiale=tab_odometrie[2];


   float consigneVitesseGauche, consigneVitesseDroite,consigneVitesse;
    consigneVitesseGauche = -vitesseDemande;
    consigneVitesseDroite = vitesseDemande;

    float AngleParcouru=0;
    float erreur_precedente[2]={0,0};

    if(angleDemande>0)
    {
    while(abs(AngleParcouru-angleDemande)>2)
    {
      if(AngleParcouru<((1.0/3.0)*angleDemande))
      {
        consigneVitesse = coefficient_rampe_croissant*AngleParcouru+0.3;
      }
      else if ((AngleParcouru>((1.0/3.0)*angleDemande)) && (AngleParcouru < ((2.0/3.0)*angleDemande)))
      {
        consigneVitesse = vitesseDemande;
      }
      else
      {
        consigneVitesse=coefficient_rampe_decroissant*(angleDemande-AngleParcouru);
      }

        consigneVitesseGauche = -consigneVitesse;
        consigneVitesseDroite = consigneVitesse;




      // moteur gauche maitre, moteur droit esclave
      vitesseGauche = -1000*(tab_odometrie[5]-position_n_moins_1_roue2)*R_Roue_codeuse/Te;
      vitesseDroite = -1000*(tab_odometrie[3]-position_n_moins_1_roue1)*R_Roue_codeuse/Te;


      erreurGauche =consigneVitesseGauche-vitesseGauche;
      erreurDroite = consigneVitesseDroite-vitesseDroite;
//	cout<<"ErreurGauche"<<erreurGauche<<endl;
//	cout<<"erreur droite"<<erreurDroite<<endl;
	cout<<"position_angulaire"<<tab_odometrie[2]<<endl;
      somme_erreurs_droite +=erreurDroite*Te*0.001;
      somme_erreurs_gauche +=erreurGauche*Te*0.001;

      erreurd_maitre_esclave = vitesseDroite +  vitesseGauche;
//	cout<<"erreur maitre esclave"<<erreurd_maitre_esclave<<endl;
      somme_erreurs_maitre_esclave += erreurd_maitre_esclave*Te*0.001;

      variation_erreur_gauche=erreurGauche + erreur_precedente[0];
      variation_erreur_droite=erreurDroite + erreur_precedente[1];


      cmd_moteur_gauche=ceil(Kpg*erreurGauche+Kig*(somme_erreurs_gauche)+Kdg*variation_erreur_gauche);

      cmd_moteur_droit=ceil(-cmd_moteur_gauche-(Kpd*erreurd_maitre_esclave+Kid*(somme_erreurs_maitre_esclave)+Kdd*variation_erreur_droite));
      cout<<"cmd_mot_droit"<<cmd_moteur_droit<<endl;
     cout <<"cmd mot gauche"<<cmd_moteur_gauche<<endl;

      erreur_precedente[0]=erreurGauche;
      erreur_precedente[1]=erreurDroite;

      AngleParcouru=(180/M_PI)*(tab_odometrie[2]-orientation_initiale);

      cout<<"Angle Parcouru"<<AngleParcouru<<endl;
      cout<<"Angle à parcourir"<<angleDemande-AngleParcouru<<endl;
position_n_moins_1_roue1=tab_odometrie[3];
position_n_moins_1_roue2=tab_odometrie[5];

      comMotDroit(cmd_moteur_droit);
      comMotGauche(cmd_moteur_gauche);

      calculer_odometrie(tab_odometrie, Te);

      receptionserie(val_capteurs);
      //detecter(&sens, val_capteurs, tab_odometrie);
        this_thread::sleep_for(chrono::milliseconds(Te));
    }

    }
    else
    { cout<<tab_odometrie[2]<<endl;
 	while(abs(AngleParcouru-angleDemande)>2)
      {/*
        if(AngleParcouru>((1.0/3.0)*angleDemande))
        {
          consigneVitesse =-coefficient_rampe_croissant*(AngleParcouru)+0.3;
        }
        else if ((AngleParcouru<((1.0/3.0)*angleDemande)) && (AngleParcouru >((2.0/3.0)*angleDemande)))
        {
          consigneVitesse = vitesseDemande;
        }
        else
        {
          consigneVitesse=3*vitesseDemande*(angleDemande-AngleParcouru);
        }
              */
consigneVitesse=vitesseDemande;
          consigneVitesseGauche = consigneVitesse;
          consigneVitesseDroite = -consigneVitesse;
             cout<<"consignevitesse"<<consigneVitesse<<endl;
        // moteur gauche maitre, moteur droit esclave
        vitesseGauche = -1000*(tab_odometrie[5]-position_n_moins_1_roue2)*R_Roue_codeuse/Te;
        vitesseDroite = -1000*(tab_odometrie[3]-position_n_moins_1_roue1)*R_Roue_codeuse/Te;


        erreurGauche =consigneVitesseGauche-vitesseGauche;
        erreurDroite = consigneVitesseDroite-vitesseDroite;
  //	cout<<"ErreurGauche"<<erreurGauche<<endl;
  //	cout<<"erreur droite"<<erreurDroite<<endl;
  	cout<<"position_angulaire"<<tab_odometrie[2]<<endl;
        somme_erreurs_droite +=erreurDroite*Te*0.001;
        somme_erreurs_gauche +=erreurGauche*Te*0.001;

        erreurd_maitre_esclave = vitesseDroite +  vitesseGauche;
  //	cout<<"erreur maitre esclave"<<erreurd_maitre_esclave<<endl;
        somme_erreurs_maitre_esclave += erreurd_maitre_esclave*Te*0.001;

        variation_erreur_gauche=erreurGauche + erreur_precedente[0];
        variation_erreur_droite=erreurDroite + erreur_precedente[1];


        cmd_moteur_gauche=ceil(Kpg*erreurGauche+Kig*(somme_erreurs_gauche)+Kdg*variation_erreur_gauche);

        cmd_moteur_droit=ceil(-cmd_moteur_gauche-(Kpd*erreurd_maitre_esclave+Kid*(somme_erreurs_maitre_esclave)-Kdd*variation_erreur_droite));

        erreur_precedente[0]=erreurGauche;
        erreur_precedente[1]=erreurDroite;

        AngleParcouru=(180/M_PI)*(tab_odometrie[2]-orientation_initiale);

        cout<<"Angle Parcouru"<<AngleParcouru<<endl;
        cout<<"Angle à parcourir"<<angleDemande-AngleParcouru<<endl;
  position_n_moins_1_roue1=tab_odometrie[3];
  position_n_moins_1_roue2=tab_odometrie[5];

        comMotDroit(cmd_moteur_droit);
        comMotGauche(cmd_moteur_gauche);

        calculer_odometrie(tab_odometrie, Te);

        receptionserie(val_capteurs);
        //detecter(&sens, val_capteurs, tab_odometrie);
          this_thread::sleep_for(chrono::milliseconds(Te));
      }

    }

    comMotDroit(0);
    comMotGauche(0);


  }


  void deplacement_robot(float xDesire,float yDesire, int val_capteurs[],float tab_odometrie[],int vitesseNominal,int sens){
      int vitesseRotationActuelle=0,intAsservissement[3];
      float te=Te,asservissement[5],distanceDemande,angleDemande;
      float somme_erreurs_maitre_esclave=0, somme_erreurs_droite=0, somme_erreurs_gauche=0;
      using std::chrono::system_clock;
      system_clock::time_point now = system_clock::now(); //prise de la date pour periode d'échantiollonage
      system_clock::time_point end;
      extern eQEP eqep1;
      extern eQEP eqep2;
      eqep1.set_position(0);           //Raz des registres contenant les nombres d'increments
    	eqep2.set_position(0);
      //calcul de la trajectoire a avoir:

      calculer_odometrie(tab_odometrie, te);
      calculerAngleEtdistance(tab_odometrie, xDesire, yDesire,&distanceDemande,&angleDemande);


   cout<<"angle à effectuer:"<<angleDemande*(180/M_PI)<<endl;
  asserTourner (angleDemande, 0.5, sens, tab_odometrie, val_capteurs);

  	this_thread::sleep_for(chrono::milliseconds(500));
      ligneDroite(distanceDemande, 0.5,  sens, tab_odometrie, val_capteurs,1);

  	this_thread::sleep_for(chrono::milliseconds(500));



      cout<<"fin déplacement"<<endl;

  }



void ligneDroite(float distance_demande, float vitesseDemande, int sens, float tab_odometrie [], int val_capteurs[], int detection)
{
  float distanceParcourue = 0;
  float variation_erreur=0;
  float vitesseGauche, vitesseDroite, erreurGauche, erreurDroite,somme_erreurs_droite,somme_erreurs_gauche, erreurd_maitre_esclave, somme_erreurs_maitre_esclave, variation_erreur_gauche=erreurGauche,variation_erreur_droite;
  int Kpg, Kig, Kdg, Kpd, Kid, Kdd;
  float erreur_precedente[2]={0,0};
  float consigneVitesse;
  extern eQEP eqep1;
  extern eQEP eqep2;
  eqep1.set_position(0);           //Raz des registres contenant les nombres d'increments
  eqep2.set_position(0);

  Kpg=250;
  Kig=500;
  Kdg=0;

  Kpd=200;
  Kid=3000;
  Kdd=0;

  somme_erreurs_droite=0;
  somme_erreurs_gauche=0;

  float coefficient_rampe_decroissant = vitesseDemande/((1.0/3.0)*distance_demande);
  float coefficient_rampe_croissant=(vitesseDemande-0.3)/((1.0/3.0)*distance_demande);
  float position_n_moins_1_roue2 = tab_odometrie[5];
  float position_n_moins_1_roue1 = tab_odometrie[3];
  float x_initial = tab_odometrie[0];
  float y_initial = tab_odometrie[1];

  while(distanceParcourue<distance_demande)
  {
    if(distanceParcourue<((1.0/3.0)*distance_demande))
    {
      consigneVitesse = coefficient_rampe_croissant*distanceParcourue+0.3;
    }
    else if ((distanceParcourue>((1.0/3.0)*distance_demande)) && (distanceParcourue < ((2.0/3.0)*distance_demande)))
    {
      consigneVitesse = vitesseDemande;
    }
    else
    {
      consigneVitesse=coefficient_rampe_decroissant*(distance_demande-distanceParcourue);
    }

    if(sens==-1)
    {
    consigneVitesse = -consigneVitesse;
    }
    cout<<consigneVitesse<<endl;
    // moteur gauche maitre, moteur droit esclave
    vitesseGauche = -1000*(tab_odometrie[5]-position_n_moins_1_roue2)*R_Roue_codeuse/Te;
    vitesseDroite = -1000*(tab_odometrie[3]-position_n_moins_1_roue1)*R_Roue_codeuse/Te;

    position_n_moins_1_roue2 = tab_odometrie[5];
    position_n_moins_1_roue1 = tab_odometrie[3];

    erreurGauche =consigneVitesse-vitesseGauche;
    erreurDroite = consigneVitesse-vitesseDroite;

    somme_erreurs_droite +=erreurDroite*Te*0.001;
    somme_erreurs_gauche +=erreurGauche*Te*0.001;

    erreurd_maitre_esclave = vitesseDroite - vitesseGauche;
    somme_erreurs_maitre_esclave += erreurd_maitre_esclave*Te*0.001;

    variation_erreur_gauche=erreurGauche + erreur_precedente[0];
    variation_erreur_droite=erreurDroite + erreur_precedente[1];


    cmd_moteur_gauche=ceil(Kpg*erreurGauche+Kig*(somme_erreurs_gauche)+Kdg*variation_erreur_gauche);

    cmd_moteur_droit=ceil(cmd_moteur_gauche-(Kpd*erreurd_maitre_esclave+Kid*(somme_erreurs_maitre_esclave)+Kdd*variation_erreur_droite));

    erreur_precedente[0]=erreurGauche;
    erreur_precedente[1]=erreurDroite;

    distanceParcourue= sqrt((tab_odometrie[0]-x_initial)*(tab_odometrie[0]-x_initial)+(tab_odometrie[1]-y_initial)*(tab_odometrie[1]-y_initial));

    comMotDroit(cmd_moteur_droit);
    comMotGauche(cmd_moteur_gauche);

    calculer_odometrie(tab_odometrie, Te);
    receptionserie(val_capteurs);
    if (detection == 1)
    {
      detecter(&sens, val_capteurs, tab_odometrie);
    }


      this_thread::sleep_for(chrono::milliseconds(Te));
  }

  comMotDroit(0);
  comMotGauche(0);


}


void ligneDroite_fin_course(float distance_demande, float vitesseDemande, int sens, float tab_odometrie [], int val_capteurs[], int detection)
{
  float distanceParcourue = 0;
  float variation_erreur=0;
  float vitesseGauche, vitesseDroite, erreurGauche, erreurDroite,somme_erreurs_droite,somme_erreurs_gauche, erreurd_maitre_esclave, somme_erreurs_maitre_esclave, variation_erreur_gauche=erreurGauche,variation_erreur_droite;
  int Kpg, Kig, Kdg, Kpd, Kid, Kdd;
  float erreur_precedente[2]={0,0};
  float consigneVitesse;
  extern eQEP eqep1;
  extern eQEP eqep2;
  eqep1.set_position(0);           //Raz des registres contenant les nombres d'increments
  eqep2.set_position(0);

  Kpg=250;
  Kig=500;
  Kdg=0;

  Kpd=200;
  Kid=3000;
  Kdd=0;

  somme_erreurs_droite=0;
  somme_erreurs_gauche=0;

  float coefficient_rampe_decroissant = vitesseDemande/((1.0/3.0)*distance_demande);
  float coefficient_rampe_croissant=(vitesseDemande-0.3)/((1.0/3.0)*distance_demande);
  float position_n_moins_1_roue2 = tab_odometrie[5];
  float position_n_moins_1_roue1 = tab_odometrie[3];
  float x_initial = tab_odometrie[0];
  float y_initial = tab_odometrie[1];

  while(distanceParcourue<distance_demande || val_capteurs[14]==0 || val_capteurs[15]==0)
  {
    if(distanceParcourue<((1.0/3.0)*distance_demande))
    {
      consigneVitesse = coefficient_rampe_croissant*distanceParcourue+0.3;
    }
    else if ((distanceParcourue>((1.0/3.0)*distance_demande)) && (distanceParcourue < ((2.0/3.0)*distance_demande)))
    {
      consigneVitesse = vitesseDemande;
    }
    else
    {
      consigneVitesse=coefficient_rampe_decroissant*(distance_demande-distanceParcourue);
    }

    if(sens==-1)
    {
    consigneVitesse = -consigneVitesse;
    }
    cout<<consigneVitesse<<endl;
    // moteur gauche maitre, moteur droit esclave
    vitesseGauche = -1000*(tab_odometrie[5]-position_n_moins_1_roue2)*R_Roue_codeuse/Te;
    vitesseDroite = -1000*(tab_odometrie[3]-position_n_moins_1_roue1)*R_Roue_codeuse/Te;

    position_n_moins_1_roue2 = tab_odometrie[5];
    position_n_moins_1_roue1 = tab_odometrie[3];

    erreurGauche =consigneVitesse-vitesseGauche;
    erreurDroite = consigneVitesse-vitesseDroite;

    somme_erreurs_droite +=erreurDroite*Te*0.001;
    somme_erreurs_gauche +=erreurGauche*Te*0.001;

    erreurd_maitre_esclave = vitesseDroite - vitesseGauche;
    somme_erreurs_maitre_esclave += erreurd_maitre_esclave*Te*0.001;

    variation_erreur_gauche=erreurGauche + erreur_precedente[0];
    variation_erreur_droite=erreurDroite + erreur_precedente[1];


    cmd_moteur_gauche=ceil(Kpg*erreurGauche+Kig*(somme_erreurs_gauche)+Kdg*variation_erreur_gauche);

    cmd_moteur_droit=ceil(cmd_moteur_gauche-(Kpd*erreurd_maitre_esclave+Kid*(somme_erreurs_maitre_esclave)+Kdd*variation_erreur_droite));

    erreur_precedente[0]=erreurGauche;
    erreur_precedente[1]=erreurDroite;

    distanceParcourue= sqrt((tab_odometrie[0]-x_initial)*(tab_odometrie[0]-x_initial)+(tab_odometrie[1]-y_initial)*(tab_odometrie[1]-y_initial));

    comMotDroit(cmd_moteur_droit);
    comMotGauche(cmd_moteur_gauche);

    calculer_odometrie(tab_odometrie, Te);
    receptionserie(val_capteurs);
    if (detection == 1)
    {
      detecter(&sens, val_capteurs, tab_odometrie);
    }


      this_thread::sleep_for(chrono::milliseconds(Te));
  }

  comMotDroit(0);
  comMotGauche(0);


}
