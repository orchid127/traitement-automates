#ifndef TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H
#define TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H

#include <stdio.h>
#include "stdlib.h"
#include "Automate.h"
#include <string.h>

#define MAX_MOTS 100
#define MAX_TAILLE_MOT 100

void lire_ligne(char *ligne);
int extraire_mots(char *ligne, char mots[MAX_MOTS][MAX_TAILLE_MOT]);
int reconnaitre_mot(automate *A, char *mot);
void boucle_reconnaissance(automate *A);

#endif //TRAITEMENT_AUTOMATES_AUTOMATE_RECO_H
