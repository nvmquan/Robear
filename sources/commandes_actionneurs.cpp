#include <iostream>
#include <vector>
#include <thread>
#include <math.h>
#include <fstream>
#include "../headers/comMoteur.h"
#include "../headers/protocole_com_serie.h"
#include "../headers/calculer_odometrie.h"
#include "../headers/commandes_actionneurs.h"


using namespace std;

/*////////////// FONCTIONS PRIMAIRES ////////////////////*/

void descendre_pince (int tab_capteurs[12]) // OK
{

    // Prévue  pour utiliser lorsque pince haut
    int compteur_secu_descente = 0;
      cout << "\n Je commence à descendre la pince."<< endl;
  receptionserie(tab_capteurs);

  // Mi ouverture
  servo(1,60) ;

  // Descendre pince
  comPouPince(-250);		// On commande le moteur tant qu'on est pas en but�e


  while((tab_capteurs[4]==0) && (compteur_secu_descente < 150))
  {
    receptionserie(tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(20)));
    compteur_secu_descente += 1;
  }
// // Attendre 3.6s
//   std::this_thread::sleep_for(std::chrono::milliseconds((int)(3600))); //Pause pour liberer thread avant de re-tester

// Arrêt
  if (compteur_secu_descente >= 150)
  {
    fermer_pince();
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(150)));
    servo(1,70) ;
  }
  comPouPince(0);

  cout << "J'ai fini de descendre la pince."<< endl;
}





void monter_pince (int tab_capteurs[12]) // OK
{
		cout << "\n Je commence à monter la pince."<< endl;
  int compteur_secu_montee = 0;
	receptionserie(tab_capteurs); // Ned valeur avant de rentrer dans la boucle while

  servo(1,150) ; // Serrer pince

  std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000)));

	comPouPince(200);		// On commande le moteur tant qu'on est pas en but�e

	while ( (tab_capteurs[3] == 0) && (compteur_secu_montee < 150))
	{
			receptionserie(tab_capteurs);
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester
      compteur_secu_montee += 1;
      if (compteur_secu_montee >= 150)
        {
          cout << "\n - Force Break : capteur au dessus de 150 ms."<<endl;
          break;
        }
	}

comPouPince(0);

cout << "J'ai fini de monter la pince."<< endl;
}



void monter_pince_init (int tab_capteurs[12]) // OK
{
		cout << "\n Je commence à monter la pince."<< endl;
	receptionserie(tab_capteurs); // Ned valeur avant de rentrer dans la boucle while
  servo(1,150) ; // Serrer pince

  std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000)));

	comPouPince(90);		// On commande le moteur tant qu'on est pas en but�e

	while ( tab_capteurs[3] == 0)
	{
			receptionserie(tab_capteurs);
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester
	}
comPouPince(0);
cout << "J'ai fini de monter la pince."<< endl;
}


void descendre_plaque (int tab_capteurs[12])
{
		cout << "\n Je commence à descendre la plaque."<< endl;
		receptionserie(tab_capteurs);
		comPouPlaque(-90);		// On commande le moteur tant qu'on est pas en but�e

		 while ( (tab_capteurs[6] == 0))
		 {
		 	receptionserie(tab_capteurs);
		 	std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester
		 }

    std::this_thread::sleep_for(std::chrono::milliseconds((int)(2000))); //Pause pour liberer thread avant de re-tester
		comPouPlaque(0);
		cout << "J'ai fini de descendre la plaque."<< endl;
}




void monter_plaque (int tab_capteurs[12]) // OK
{
	cout << "\n Je commence à monter la plaque."<< endl;
  receptionserie(tab_capteurs);
  comPouPlaque(100);

  while ( (tab_capteurs[5] == 0))
  {
     receptionserie(tab_capteurs);
     std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester
  }

  comPouPlaque(0);

  cout << "J'ai fini de descendre la plaque."<< endl;
}

void ouvrir_pince ()
{
		servo(1, 0);
}

void fermer_pince () // OK
{
		servo(1, 150);
}

void basculer_cylindre_bas ()
{
	 servo(3, 100);
}

void redresser_bascule_bas ()
{
	servo(3, 10);
}

void redresser_bascule_haut()
{
  servo(2, 40);
}

void basculer_cylindre_haut ()
{
    for(int i = 1; i < 11; i++){
      servo(2, 40+6*i);
      std::this_thread::sleep_for(std::chrono::milliseconds((int)(50)));

    }
}

/*fonction principales */

void deposer_cylindre ()
{
		basculer_cylindre_bas ();
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(500)));
		redresser_bascule_bas ();
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(500)));
}

void recuperer_boules (int tab_capteurs[12])
{
		descendre_plaque (tab_capteurs);
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(250)));
		monter_plaque (tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(250)));
}

void funnyAction2017 ()
{

		servo(6, 120);

}

void initialiser_actionneurs(int tab_capteurs[12])
{
	cout << "Initialisation des bras en cours."<< endl;

  fermer_pince ();
	monter_pince_init (tab_capteurs);
	monter_plaque (tab_capteurs);
	redresser_bascule_bas ();

	this_thread::sleep_for(chrono::milliseconds(500));  //Temps que les actionneurs se mettent en place

	cout << "\n Initialisation des bras terminée."<< endl;
}

/*//////////////////////////////////////////////////////////////////
//////////////// Fonction année dernière /////////////////////////
//////////////////////////////////////////////////////////////////

void sortir_bras_coquillage_gauche ()
{
	servo(1, 45);// a faire mettre la bon valeur d'angle
}

void rentrer_bras_coquillage_gauche ()
{
	servo(1, 124);// a faire mettre la bon valeur d'angle
}

void sortir_bras_coquillage_droit ()
{
	servo(2, 160);// a faire mettre la bon valeur d'angle
}

void rentrer_bras_coquillage_droit ()
{
	servo(2, 72);// a faire mettre la bon valeur d'angle
}

void sortir_les_bras_coquillage ()
{
	sortir_bras_coquillage_gauche();
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(500)));
	sortir_bras_coquillage_droit();
}

void rentrer_les_bras_coquillage ()
{
	rentrer_bras_coquillage_droit();
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(500)));
	rentrer_bras_coquillage_gauche();
}
///////////////////////////////////////////////////////////////////

void ouvrir_bras_poisson_gauche ()
{
cout<<"j ouvre ma pince gauche"<<endl;
	servo(3, 120);// a faire mettre la bon valeur d'angle
}

void fermer_bras_poisson_gauche ()
{
	servo(3, 90);// a faire mettre la bon valeur d'angle
}

void ouvrir_bras_poisson_droit ()
{
cout<<"j ouvre ma pince droite"<<endl;
	servo(4, 120);// a faire mettre la bon valeur d'angle
}

void fermer_bras_poisson_droit ()
{
	servo(4, 95);// a faire mettre la bon valeur d'angle
}
///////////////////////////////////////////////////////////////
void sortir_support_parasol ()
{
	servo(5, 70);// a faire mettre la bon valeur d'angle
}

void rentrer_support_parasol ()
{
	servo(5, 10);// a faire mettre la bon valeur d'angle
}

void fermer_parasol ()
{
	servo(6, 75);// a faire mettre la bon valeur d'angle
}

void ouvrir_parasol ()
{
	servo(6, 130);// a faire mettre la bon valeur d'angle
}

void funny_action ()
{
	sortir_support_parasol ();
  	std::this_thread::sleep_for(std::chrono::milliseconds((int)(500)));
	ouvrir_parasol ();
}
//////////////////////////////////////////////////////////////////////////
void sortir_bras_poisson_gauche(int tab_capteurs[12])
{
  //[3] capteur bras poisson bas
// chrono::system_clock::time_point end;
//  end=chrono::system_clock::now();
//  end=end+chrono::seconds(1);
      cout << "\n Je commence à sortir le bras à poisson gauche."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasGauche(255);		// On commande le moteur tant qu'on est pas en but�e

  while ( (tab_capteurs[4] == 0))
  {
    //cout << "\n je suis dans le while"<< endl;
    receptionserie(tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester

  }

  comMotBrasGauche(0);

  cout << "J'ai fini de sortir le bras à poisson gauche."<< endl;
}



void rentrer_bras_poisson_gauche (int tab_capteurs[12])
{
  //[2] capteur bras poisson haut
  chrono::system_clock::time_point end;
  end=chrono::system_clock::now();
  end=end+chrono::seconds(1);
      cout << "\n Je commence à rentrer le bras à poisson gauche."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasGauche(-90);		// On commande le moteur tant qu'on est pas en but�e

  while ((tab_capteurs[3] == 0))
  {
    //cout << "\n je suis dans le while"<< endl;
    receptionserie(tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester

  }

  comMotBrasGauche(0);

  cout << "J'ai fini de rentrer le bras à poisson gauche."<< endl;
}

///////////////////////////////////////////////////////////////////////////
void sortir_bras_poisson_droit(int tab_capteurs[12])
{
  //[3] capteur bras poisson bas
  chrono::system_clock::time_point end;
  end=chrono::system_clock::now();
  end=end+chrono::seconds(1);
      cout << "\n Je commence à sortir le bras à poisson droit."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasDroit(255);		// On commande le moteur tant qu'on est pas en but�e

  while ((tab_capteurs[6] == 0))
  {
    //cout << "\n je suis dans le while"<< endl;
    receptionserie(tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester

  }

  comMotBrasDroit(0);

  cout << "J'ai fini de sortir le bras à poisson droit."<< endl;
}



void rentrer_bras_poisson_droit (int tab_capteurs[12])
{
  //[2] capteur bras poisson haut
  chrono::system_clock::time_point end;
  end=chrono::system_clock::now();
  end=end+chrono::seconds(1);
      cout << "\n Je commence à rentrer le bras à poisson droit."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasDroit(-90);		// On commande le moteur tant qu'on est pas en but�e

  while ((tab_capteurs[5] == 0))
  {
    //cout << "\n je suis dans le while"<< endl;
    receptionserie(tab_capteurs);
    std::this_thread::sleep_for(std::chrono::milliseconds((int)(20))); //Pause pour liberer thread avant de re-tester

  }

  comMotBrasDroit(0);

  cout << "J'ai fini de rentrer le bras à poisson droit."<< endl;
}



void rentrer_bras_poisson_droit_mi_course (int tab_capteurs[12])
{
  //[2] capteur bras poisson haut
  chrono::system_clock::time_point end;
      cout << "\n Je commence à rentrer le bras chargé de poissons."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasDroit(-90);
	this_thread::sleep_for(chrono::milliseconds(1500));
  comMotBrasDroit(0);

  cout << "J'ai les poissons suspendus à mon bras."<< endl;
}

void rentrer_bras_poisson_gauche_mi_course (int tab_capteurs[12])
{
  //[2] capteur bras poisson haut
  chrono::system_clock::time_point end;
      cout << "\n Je commence à rentrer le bras chargé de poissons."<< endl;
  receptionserie(tab_capteurs);
  comMotBrasGauche(-90);
	this_thread::sleep_for(chrono::seconds(1));
  comMotBrasGauche(0);

  cout << "J'ai les poissons suspendus à mon bras."<< endl;
}
/***************************************************/
