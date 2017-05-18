#ifndef COMMANDES_ACTIONNEURS_H
#define COMMANDES_ACTIONNEURS_H

/*//// 2017 !!! /////////////////////////////*/
void initialiser_actionneurs(int tab_capteurs[12]);

void descendre_pince(int tab_capteurs[12]);
void monter_pince(int tab_capteurs[12]);

void descendre_plaque(int tab_capteurs[12]);
void monter_plaque(int tab_capteurs[12]);

void basculer_cylindre_bas ();
void redresser_bascule_bas ();

void basculer_cylindre_haut ();
void redresser_bascule_haut();

void deposer_cylindre ();
void recuperer_boules (int tab_capteurs[12]);

void funnyAction2017 ();

void ouvrir_pince ();
void fermer_pince();


/*///// ANNEE DERNIERE //////////////////////

void sortir_bras_coquillage_gauche ();
void rentrer_bras_coquillage_gauche ();
void sortir_bras_coquillage_droit ();
void rentrer_bras_coquillage_droit ();
void sortir_les_bras_coquillage ();
void rentrer_les_bras_coquillage ();
void ouvrir_bras_poisson_gauche ();
void fermer_bras_poisson_gauche ();
void ouvrir_bras_poisson_droit ();
void fermer_bras_poisson_droit ();
void sortir_support_parasol ();
void rentrer_support_parasol ();
void fermer_parasol ();
void ouvrir_parasol ();
void funny_action ();
void sortir_bras_poisson_gauche(int tab_capteurs[12]);
void rentrer_bras_poisson_gauche (int tab_capteurs[12]);
void sortir_bras_poisson_droit(int tab_capteurs[12]);
void rentrer_bras_poisson_droit (int tab_capteurs[12]);
void initialiser_actionneurs(int tab_capteurs[12]);
void rentrer_bras_poisson_droit_mi_course(int tab_capteurs[12]);
void rentrer_bras_poisson_gauche_mi_course(int tab_capteurs[12]);

*/
#endif // COMMANDES_ACTIONNEURS_H
