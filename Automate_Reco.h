#ifndef TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H
#define TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H

#include <stdio.h>
#include "stdlib.h"
#include "Automate.h"
#include <string.h>

#define MAX_MOTS 50
#define MAX_TAILLE_MOT 256
#define MAX_ETATS 100
#define MAX_TRANSITIONS 100

void lire_ligne(char *ligne);
int extraire_mots(char *ligne, char mots[MAX_MOTS][MAX_TAILLE_MOT]);
int est_terminal(automate_deterministe *A, int etat);
int reconnaitre_mot(automate_deterministe *A, char *mot);
void boucle_reconnaissance(automate_deterministe *A);


#endif //TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H
