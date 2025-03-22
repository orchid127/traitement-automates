#include "Automate_Reco.h"


// Fonction pour lire une ligne de mots
void lire_ligne(char *ligne) {
    printf("Entrez une ligne de mots : ");
    if (fgets(ligne, MAX_TAILLE_MOT, stdin) == NULL) {
        fprintf(stderr, "Erreur de lecture\n");
        exit(EXIT_FAILURE);
    }
    ligne[strcspn(ligne, "\n")] = 0;
}

// Fonction pour extraire les mots d'une ligne
int extraire_mots(char *ligne, char mots[MAX_MOTS][MAX_TAILLE_MOT]) {
    int i = 0;
    char *mot = strtok(ligne, " ");          // Sépare la ligne en mots avec un espace comme délimiteur
    while (mot != NULL && i < MAX_MOTS) {
        strcpy(mots[i], mot);                // Copie le mot extrait dans le tableau mot[]
        i++;
        mot = strtok(NULL, " ");
    }
    return i;
}

// Vérifie si un état est terminal
int est_terminal(automate_deterministe *A, int etat) {
    for (int i = 0; i < A->nb_etats_terminaux; i++) {       // Parcourt tous les états terminaux de l'automate
        for (int j = 0; j < A->taille_subset[i]; j++) {     // Parcourt les sous-ensembles d'états terminaux
            if (A->etats_terminaux[i][j] == etat) {
                return 1;  // L'état est terminal
            }
        }
    }
    return 0;
}

// Vérifie si un mot est accepté par l'automate
int reconnaitre_mot(automate_deterministe *A, char *mot) {
    int etat_courant = A->etat_initial[0];  // Un seul état initial (hypothèse)
    int i = 0;

    while (mot[i] != '\0') {
        int transition_trouvee = 0;

        // Parcours du tableau de transitions
        for (int j = 0; j < A->nb_transition; j++) {
            if (A->transition->etat_depart[j] == etat_courant &&
                A->transition->alphabet[j] == mot[i]) {
                etat_courant = A->transition->etat_arrivee[j];
                transition_trouvee = 1;
                break;
            }
        }

        if (!transition_trouvee) return 0; // Mot rejeté
        i++;
    }

    return est_terminal(A, etat_courant);  // Vérifie si on est dans un état terminal
}

// Boucle principale de reconnaissance
void boucle_reconnaissance(automate_deterministe *A) {
    char ligne[MAX_TAILLE_MOT];
    char mots[MAX_MOTS][MAX_TAILLE_MOT];

    while (1) {
        lire_ligne(ligne);
        int nb_mots = extraire_mots(ligne, mots);

        for (int i = 0; i < nb_mots; i++) {
            if (strcmp(mots[i], "fin") == 0) {
                return;
            }

            if (reconnaitre_mot(A, mots[i])) {
                printf("oui\n");  // Mot accepté
            } else {
                printf("non\n");  // Mot rejeté
            }
        }
    }
}
