//
// Created by amabl on 20/02/2025.
//

#ifndef AUTOMATEFINI_AUTOMATE_H
#define AUTOMATEFINI_AUTOMATE_H



typedef struct
{
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

typedef struct {
    int etat_depart[100];
    char alphabet[100];
    int etat_arrivee[100];
} transition_deterministe;

typedef struct {
    int nb_etat;
    int nb_symbole;
    int etat_initial[100];
    int etats_terminaux[100][100];
    int nb_etats_terminaux;
    int nb_transition;
    transition_deterministe transition[100];   // Les transitions du DFA
    int etats_determines[100][100];  // Tableau pour les sous-ensembles d'états
    int taille_subset[100];           // Taille réelle de chaque sous-ensemble
} automate_deterministe;

/**
 * @brief Fonction pour stocker les données dans un automate
 * @param automate *  : pointeur sur un automate
 * @param int: Numéro de l'automate utilisé
 * @return  none
 */
void Stockage_donnees_automate(automate *,int);

/**
 * @brief Fonction pour afficher l'automate sous forme de tableau
 * @param automate : structure automate
 * @return  none
 */
void affichage_automate(automate test);


/**
 * @brief Fonction pour déterminer si l'automate est déterministe ou pas
 * @param automate : structure automate
 * @return  int
 */
int est_un_automate_deterministe(automate test);

/**
 * @brief Fonction pour déterminer si l'automate est complet ou pas
 * @param automate : structure automate
 * @return  int
 */
int est_un_automate_complet(automate test);


automate completion(automate test);

/**
 * @brief Fonction pour completer l'automate
 * @param automate : structure automate
 * @return  automate
 */
automate completion(automate test);


/**
 * @brief Fonction pour déterminer si l'automate est standard ou pas
 * @param automate : structure automate
 * @return  int
 */
int est_standard(automate test);


/**
 * @brief Fonction pour standardiser l'automate
 * @param automate : structure automate
 * @return  automate
 */
automate standardisation(automate test);



void determiniser(automate *non_det, automate_deterministe *det);

void afficher_automate_deterministe(automate_deterministe *det);

/**
 * @brief Fonction pour complémentariser l'automate
 * @param automate : structure automate
 * @return  automate
*/
automate_deterministe automate_complementaire(automate_deterministe A);


void copier_automate_non_deterministe_vers_deterministe(automate *non_det, automate_deterministe *det);
#endif //AUTOMATEFINI_AUTOMATE_H
