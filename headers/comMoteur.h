//
//  comMoteur.h
//  communicationserie
//
//  Created by Sylvain Richard on 25/02/2015.
//  Copyright (c) 2015 Sylvain Richard. All rights reserved.
//

// Package qui permet de controler facilement les deux moteurs de déplacement de notre robot à partir des hacheurs en H
// Brochage necessaire: PWM moteur 1: port 3 sens moteur port 23 PWM moteur 2: port 4 sens moteur port 22

#ifndef __communicationserie__comMoteur__
#define __communicationserie__comMoteur__

// Commande des différents moteurs (fonctionnent de la même manière)
// prend un commande entre -255 et 255 pour une commande entre la tension min et la tension max
// Limite à cette plage sinon.
bool comMotDroit(int val);
bool comMotGauche(int val);
bool comMotBrasGauche(int val);
bool comMotBrasDroit(int val);
#endif /* defined(__communicationserie__comMoteur__) */
