/*
//  Created by Bassoch & Palmieri on 22/03/2016.
//  Copyright (c) 2016. All rights reserved.
*/

#include <mutex>
#include "../headers/eqep.h"
#include "../headers/calculer_odometrie.h"
#include <time.h>
#include <cmath>
#include <chrono>


// Cr�ation des objets eQEP (muxage, p�riode, mode, position inclus)
eQEP eqep1(eQEP1, eQEP::eQEP_Mode_Absolute, 1);
eQEP eqep2(eQEP2, eQEP::eQEP_Mode_Absolute, 2);

//Constantes et variables
const float e=260.0;   //Ecartement des roues codeuses (en mm)
const float N1=1823;  //Nombre d'incréments par tour des codeurs
const float N2=1818;
/*
const float p1=0.0861423221*3/2; //Ajustes a la main. Pas du codeur 1, theoriquement p=0,034910948 mm/incrémement
const float p2=0.08635254365*3/2; //Pas du codeur 2

*/

// Nouvelles valeurs 2017
const float p1=0.151837230 *0.885; //Ajustes a la main. Pas du codeur 1, theoriquement p=0,034910948 mm/incrémement
const float p2=0.143864192 *0.885; //Pas du codeur 2


float n1, n2;          //Nombre d'increments sur chacune des roues produits depuis la dernière lecture
float dx, dy, dtheta, w1, w2, dtheta1, dtheta2;
std::mutex mutProtectionEcriture;
float total_increment_1=0;
float total_increment_2=0;


void calculer_odometrie(float tab[9], float Te)
{
	//tab = [x, y, alpha, thetag, wg, thetad, wd]

	//Lecture des increments produits depuis la derniere lecture
	n1 = eqep1.get_position(false); // droit
	n2 = eqep2.get_position(false);// gauche
	total_increment_1 +=n1;
	total_increment_2 +=n2;

	eqep1.set_position(0);           //Raz des registres contenant les nombres d'increments
	eqep2.set_position(0);

	//std::cout << "total_increment_1 : " << total_increment_1 << std::endl;
	//std::cout << "total_increment_2 : " << total_increment_2 << std::endl;

	//Position du robot
	dtheta = (p2*n2-p1*n1)/e;                     //Calcul de la variation d'orientation en rad
	dx = cosf(tab[2]+dtheta)*(p1*n1+p2*n2)/2000;  //Calcul de la variation de x en m
	dy = sinf(tab[2]+dtheta)*(p1*n1+p2*n2)/2000;  //Calcul de la variation de y en m


	//Positions angulaires des roues codeuses
	dtheta1 = n1*(2.0*M_PI/N1);// droit
	dtheta2 = n2*(2.0*M_PI/N2);// gauche


	//Vitesses des roues codeuses
       	w1 = dtheta1*(1000.0/Te);    // droit     //en rad/sec
       	w2 = dtheta2*(1000.0/Te);	// gauche


	//Mise a jour des variables
	mutProtectionEcriture.lock();    //Protection lors de l'�criture pour �viter d'eventuels conflits
	tab[0] -= dx;
	tab[1] -= dy;
	tab[2] += dtheta;                //orientation entre [-Pi, Pi[
	//if ((tab[2] - M_PI) > 0) (tab[2] += 2.0*M_PI);
	//if ((tab[2] + M_PI) <= 0) (tab[2] -= 2.0*M_PI);
	tab[3] += dtheta1;
	tab[4] = w1;
	tab[5] += dtheta2;
	tab[6] = w2;
	tab[7] = n1;
	tab[8] = n2;
	mutProtectionEcriture.unlock();

	///Debogage

	//std::cout << "x : " << tab[0] << std::endl;
	//std::cout << "y : " << tab[1] << std::endl;
	//std::cout << "alpha : " << tab[2] << std::endl;
	//std::cout << "w1 : " << w1 << std::endl;
	//std::cout << "w2 : " << w2 << std::endl;
	//std::cout << "theta1 : " << tab[3] << std::endl;
	//std::cout << "theta2 : " << tab[5] << std::endl;
	//std::cout << std::endl;

}


void valeur_increment()
{

std::cout <<" nb dincrement n1= "<<total_increment_1<<std::endl;

std::cout <<" nb dincrement n2= "<<total_increment_2<<std::endl;

}
