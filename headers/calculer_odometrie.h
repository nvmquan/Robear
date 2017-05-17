
#ifndef CALCULER_ODOMETRIE_H
#define CALCULER_ODOMETRIE_H

/**
\brief Met a jour la position et l'orientation du robot, et les vitesses et les positions angulaire des roues codeuses.
\param tab[7] Tableau de float [x(m), y(m), orientation(rad), position roue 1(rad), vitesse roue 1(rad/s), position roue 2(rad), vitesse roue 2(rad/s)].
\param Te Periode d'échantillonnage (en ms).
*/
void calculer_odometrie(float tab[9], float Te);
void valeur_increment();

#endif


//EXEMPLE D'UTILISATION
/*
    //Initialisation et declaration
    extern eQEP eqep1;
    extern eQEP eqep2;
    using chrono::system_clock;

    system_clock::time_point now = system_clock::now();

    while (1){
        calculer_odometrie(tab_odometrie, Te);                             //MAJ des donnes odometriques
        this_thread::sleep_until(now+chrono::milliseconds((int)(Te)));     //Pause pour moyenner la vitesse, liberer le thread, etc
        now = system_clock::now();
    }
*/
