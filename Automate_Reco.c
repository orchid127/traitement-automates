#include "Automate_Reco.h"

// Fonction pour lire une ligne complète de l'utilisateur
void lire_ligne(char *ligne) {
    printf("Entrez une ligne de mots : ");
    if (fgets(ligne, MAX_TAILLE_MOT, stdin) == NULL) {   // Sépare la ligne en mots en utilisant l'espace comme séparateur
        fprintf(stderr, "Erreur de lecture\n");          // Copie le mot extrait dans le tableau des mots
        exit(EXIT_FAILURE);
    }
}

// Fonction pour séparer une ligne en mots
int extraire_mots(char *ligne, char mots[MAX_MOTS][MAX_TAILLE_MOT]) {
    int i = 0;
    char *mot = strtok(ligne, " ");                      // Sépare la chaine en mots en utilisant l'espace comme séparateur
    while (mot != NULL && i < MAX_MOTS) {
        strcpy(mots[i], mot);                            // Copie le mot extrait dans le tableau mots
        i++;
        mot = strtok(NULL, " ");
    }
    return i;                                            // Retourne le nombre de mots extraits
}

// Fonction pour vérifier si un mot est accepté par l'automate
int reconnaitre_mot(automate *A, char *mot) {
    int etat_courant = A->etats_initiaux[0];  
    int i = 0;

    while (mot[i] != '\0') {                                    // Parcours chaque caractère du mot
        int transition_trouvee = 0;  
        
        for (int j = 0; j < A->nb_transition; j++) {            // Recherche une transition correspondant au caractère actuel
            if (A->transition[j].etat_depart == etat_courant &&
                strchr(A->transition[j].alphabet, mot[i]) != NULL) {
                etat_courant = A->transition[j].etat_arrivee; 
                transition_trouvee = 1;  
                break;  // Sortir de la boucle dès qu'une transition est trouvée
            }
        }
        if (!transition_trouvee) return 0;                      // Si aucune transition ne correspond, le mot est rejeté
        i++;
    }

    for (int i = 0; i < A->nb_etats_terminaux; i++) {               // Vérifie si l'état final atteint est un état terminal
        if (etat_courant == A->etats_terminaux[i]) return 1;        // Le mot est accepté
    }
    return 0;                                                       // Sinon, le mot est rejeté
}

// Fonction principale qui gère la reconnaissance des mots
void boucle_reconnaissance(automate *A) {
    char ligne[MAX_TAILLE_MOT];                    // Stocke la ligne entrée par l'utilisateur
    char mots[MAX_MOTS][MAX_TAILLE_MOT];           // Tableau pour stocker les mots extraits

    while (1) { 
        lire_ligne(ligne);                          // Demande une ligne à l'utilisateur
        int nb_mots = extraire_mots(ligne, mots);   // Sépare la ligne en mots

        for (int i = 0; i < nb_mots; i++) {         // Parcours tous les mots extraits
            if (strcmp(mots[i], "fin") == 0) {      // Vérifie si le mot est "fin"
                return; 
            }

            if (reconnaitre_mot(A, mots[i])) {      // Vérifie si le mot est accepté ou non par l'automate
                printf("oui\n");  
            } else {
                printf("non\n");  
            }
        }
    }
}
