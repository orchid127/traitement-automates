//
// Created by amabl on 20/02/2025.
//

#ifndef AUTOMATEFINI_AUTOMATE_H
#define AUTOMATEFINI_AUTOMATE_H



typedef struct {
    int etat_depart;
    char alphabet[50];
    int etat_arrivee;
}transitionst;

typedef struct
{
    int nb_symbole;
    int nb_etat;
    int nb_etat_initiaux;
    int nb_etats_terminaux;
    int etats_initiaux[100];
    int etats_terminaux[100];
    int nb_transition;
    transitionst transition[100];
}automate;


void Stockagedonneesautomate(automate *,int);
void affichage_automate(automate test);
int est_un_automate_deterministe(automate test);
int est_un_automate_complet(automate test);
automate completion(automate test);
int est_standard(automate test);
automate standardisation(automate test);
#endif //AUTOMATEFINI_AUTOMATE_H
