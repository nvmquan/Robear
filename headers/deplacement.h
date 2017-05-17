//
//  thread_ligne_droite.h
//  test_asservissement
//
//  Created by Sylvain Richard on 05/05/2015.
//  Copyright (c) 2015 Sylvain Richard. All rights reserved.
//

#ifndef __test_asservissement__thread_ligne_droite__
#define __test_asservissement__thread_ligne_droite__




void calculerAngleEtdistance(float tab_odometrie [],float xDesire,float yDesire,float* d,float* angle);

void  asserTourner (float angleDemande, float vitesseDemande, int sens, float tab_odometrie[], int val_capteurs[]);

void calculerAngleEtdistance(float tab_odometrie [],float xDesire,float yDesire,float* d,float* angle);

void tourner(float tab_odometrie[],int val_capteurs,float angle);

void avancer (float tab_odometrie[], int val_capteurs[],float distanceDemande,int vitesseNominal, int sens);

void deplacement_robot(float xDesire,float yDesire, int val_capteurs[],float tab_odometrie[],int vitesseNominal,int sens);

void ligneDroite(float distance_demande, float vitesseDemande, int sens, float tab_odometrie [], int val_capteurs[], int detection);

void ligneDroite_fin_course(float distance_demande, float vitesseDemande, int sens, float tab_odometrie [], int val_capteurs[], int detection);

#endif /* defined(__test_asservissement__thread_ligne_droite__) */
