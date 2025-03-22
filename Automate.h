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
    int nb_etat_initiaux;
    int nb_etats_terminaux;
    int nb_transition;
    transition_deterministe transition[100];
    /*Tableau ou il y a les sous ensembles (les nouveaux etats créer)*/
    int etats_determines[100][100];
    /* Tableau contenant la tailles des sous ensembles*/
    int taille_subset[100];
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

/**
 * @brief Fonction qui permet d'effectuer la déterminisation
 * @param *automate : structure automate
 * @param *automate_deterministe : structure automate_deterministe
 * @return
 */
void determiniser(automate *non_det, automate_deterministe *det);


/**
 * @brief Fonction qui d'afficher un automate déterministe
 * @param *automate : structure automate
 * @param *automate_deterministe : structure automate_deterministe
 * @return
 */
void afficher_automate_deterministe(automate_deterministe *det , automate  automate_inital);

/**
 * @brief Fonction pour complémentariser l'automate et donc avoir son langague complémentaire
 * @param automate : structure automate
 * @return  automate
*/
automate_deterministe automate_complementaire(automate_deterministe A);





#endif //AUTOMATEFINI_AUTOMATE_H
