//
// Created by amabl on 20/02/2025.
//
#include <stdio.h>
#include "Automate.h"
#include "string.h"
#include <stdbool.h>
#include "Automate_Reco.h"

void Stockage_donnees_automate(automate *test, int num_automate)
{

    char filename[100];
    /* Permet de créer le chemin du fichier contenant l'automate désirer en fonction du numéro choisis*/
    snprintf(filename, sizeof(filename), "C:\\Users\\amabl\\CLionProjects\\Automatefini\\automate test\\Automate%d.txt", num_automate);

    /*Ouverture du fichier .txt choisis*/
    FILE *file = fopen(filename, "r");

    /*Récupère sur la première ligne le nombre symbole utilisé*/
    fscanf(file, "%d", &test->nb_symbole);
    printf("Le nombre de symboles utilises est : %d\n", test->nb_symbole);

    /*Récupère sur la deuxième ligne le nombre d'état de l'automate*/
    fscanf(file, "%d", &test->nb_etat);
    printf("Le nombre d'etats utilises est : %d\n", test->nb_etat);

    /*Récupère sur la troisième ligne le nombre d'état initaux de l'automate et leurs numéros*/
    fscanf(file, "%d", &test->nb_etat_initiaux);
    printf("Le nombre d'etat(s) initiaux est : %d\n", test->nb_etat_initiaux);
    printf("Les etats initiaux sont : ");
    for (int i = 0; i < test->nb_etat_initiaux; i++)
    {
        fscanf(file, "%d", &test->etats_initiaux[i]);
        printf("%d ", test->etats_initiaux[i]);
    }
    printf("\n");

    /*Récupere sur la quatrième ligne le nombre d'états finaux de l'automate et leurs numéros*/
    fscanf(file, "%d", &test->nb_etats_terminaux);
    printf("Le nombre d'etats terminaux est : %d\n", test->nb_etats_terminaux);
    printf("Les etats terminaux sont : ");
    for (int i = 0; i < test->nb_etats_terminaux; i++)
    {
        fscanf(file, "%d", &test->etats_terminaux[i]);
        printf("%d ", test->etats_terminaux[i]);
    }
    printf("\n");

    /*Récupère sur la cinquième ligne le nombre de transition de l'automate*/

    fscanf(file, "%d", &test->nb_transition);
    printf("\nLe nombre de transiton est %d\n", test->nb_transition);

    char Ligne_lue[100];
    int index = 0;

    while (fgets(Ligne_lue, sizeof(Ligne_lue), file) != NULL && index < test->nb_transition)
    {

        /* Si ligne vide on va à la prochaine**/
        if (Ligne_lue[0] == '\n' || Ligne_lue[0] == '\r')
        {
            continue;
        }


        int etat_depart, etat_arrivee;
        char symbole[50];

        /* Analyse de la ligne récupére pour extraire les informations*/
        sscanf(Ligne_lue, "%d%s%d", &etat_depart, symbole, &etat_arrivee);

        /*Stockage des données*/
        test->transition[index].etat_depart = etat_depart;
        test->transition[index].etat_arrivee = etat_arrivee;

        /*détection de ε si trouvé alors on le copie dans l'alphabet sinon on copie simplement le symbole*/
        if (strcmp(symbole, "ε") == 0 )
        {
            strcpy(test->transition[index].alphabet, "ε");
        }
        else
        {
            strcpy(test->transition[index].alphabet, symbole);
        }

        index++;
    }

    /* Affichage des transitions */
    for (int i = 0; i < test->nb_transition; i++)
    {
        if (strcmp(test->transition[i].alphabet, "ε") == 0)
        {
            printf("Les transitions sont %d->epsilon->%d\n", test->transition[i].etat_depart, test->transition[i].etat_arrivee);
        }
        else
        {
            printf("Les transitions sont %d->%s->%d\n", test->transition[i].etat_depart, test->transition[i].alphabet, test->transition[i].etat_arrivee);
        }
    }
    fclose(file);
}


void affichage_automate(automate test)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int larg_col = 8;
    int epsi_trouv = 0;

    /*Vérification de l'existence de transition en epsilon*/
    for (int i = 0; i < test.nb_transition; i++)
    {
        /*On compare si retourne zéro veut dire que des epsilon existe*/
        if (strcmp(test.transition[i].alphabet, "ε") == 0)
        {
            epsi_trouv = 1;
            break;
        }
    }


    printf("        ");
    /*Affichage alphabet de l'automate sur une ligne grâce à un formatage spécial en c*/
    for (int i = 0; i < test.nb_symbole; i++)
    {
        printf("%-*c", larg_col, alphabet[i]);
    }
    /*Ajout colonne epsilon si on a detecter des transition epsilon auparavant*/
    if (epsi_trouv == 1)
    {
        printf("%-*s", larg_col, "epsilon");
    }
    printf("\n");

    for (int i = 0; i < test.nb_etat; i++)
    {
        int init = 0, term = 0;
        /*Verifie si etat observé est un état initiaux*/
        for (int j = 0; j < test.nb_etat_initiaux; j++)
        {
            if (test.etats_initiaux[j] == i)
            {
                init = 1;
            }
        }
        /*Verifie si etat observé est un état final*/
        for (int j = 0; j < test.nb_etats_terminaux; j++)
        {
            if (test.etats_terminaux[j] == i)
            {
                term = 1;
            }
        }

        /*En fonction des carcatéristiques déterminé avant  on affiche les caractéristiques correspondantes*/
        if ((init && term)==1)
        {
            printf("ES %-2d   ", i);
        }
        else if (init)
        {
            printf("E  %-2d   ", i);
        }
        else if (term)
        {
            printf("S  %-2d   ", i);
        }
        else
        {
            printf("   %-2d   ", i);
        }

        /*Affichage transitions*/

        for (int l = 0; l < test.nb_symbole; l++)
        {
            char transitions[50] = "";
            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && test.transition[k].alphabet[0] == alphabet[l])
                {
                    char buffer[10];
                    sprintf(buffer, "%d,", test.transition[k].etat_arrivee);
                    strcat(transitions, buffer);
                }
            }

            if (strlen(transitions) > 0)
            {
                transitions[strlen(transitions) - 1] = '\0';
                printf("%-*s", larg_col, transitions);
            }
            else
            {
                printf("%-*s", larg_col, "-");
            }
        }

        /*Affichage transition des epsilon si on en a*/

        if (epsi_trouv == 1)
        {
            char epsilon_trans[50] = "";
            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, "ε") == 0)
                {
                    char buffer[10];
                    sprintf(buffer, "%d,", test.transition[k].etat_arrivee);
                    strcat(epsilon_trans, buffer);
                }
            }

            if (strlen(epsilon_trans) > 0)
            {
                epsilon_trans[strlen(epsilon_trans) - 1] = '\0';
                printf("%-*s", larg_col, epsilon_trans);
            }
            else
            {
                printf("%-*s", larg_col, "-");
            }
        }

        printf("\n");
    }
}


int est_un_automate_deterministe(automate test)
{
    int nondet = 1;
    int i = 0;
    int j = 0;

    /*Verification si le nombre d'etats initiaux supérieur à 1*/
    if (test.nb_etat_initiaux > 1 )
    {
        nondet = 0;
        printf("L'automate n'est pas deterministe car il a plusieurs etats initiaux\n");
        return 0;
    }

    for (i = 0; i < test.nb_transition; i++)
    {
        /* Vérification existence des transitions epsilon*/
        if (strcmp(test.transition[i].alphabet, "ε") == 0)
        {
            printf("L'automate n'est pas deterministe car il y a des transitions epsilon\n");
            return 0;
        }

        /* Vérification si sur un état donné avec un même symbole on va vers plusieurs états diffèrents*/
        for (j = i + 1; j < test.nb_transition; j++)
        {
            if (test.transition[i].etat_depart == test.transition[j].etat_depart &&strcmp(test.transition[i].alphabet, test.transition[j].alphabet) == 0 && test.transition[i].etat_arrivee != test.transition[j].etat_arrivee)
            {
                nondet = 0;
                printf("L'automate n'est pas deterministe car l'etat %d a plusieurs transitions avec le symbole '%s' vers differents etats %d et %d \n",test.transition[i].etat_depart,test.transition[i].alphabet,test.transition[i].etat_arrivee,test.transition[j].etat_arrivee);
                return 0;
            }
        }
    }

    if (nondet == 1)
    {
        printf("L'automate est deterministe\n");
        return 1;

    }

}

int est_un_automate_complet(automate test)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    /* Cette boucle permet de déterminer si une transition est trouvé ou pas */
    for (int i = 0; i < test.nb_etat; i++)
    {
        for (int j = 0; j < test.nb_symbole; j++)
        {
            int trans_trouv = 0;

            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, (char[]) {alphabet[j], '\0'}) == 0)
                {
                    trans_trouv = 1;
                }
            }

            /* Si une transition n'est pas trouvé alors l'automate n'est pas complet*/
            if (trans_trouv == 0)
            {
                printf("L'automate n'est pas complet\n");
                printf("Tous les etats n'ont pas de transition vers un autre etat\n");
                return 0;
            }
        }
    }
    printf("L'automate est complet\n");
    return 1;
}

automate completion(automate test)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    automate res;
    res = test;
    int poubelle = -1;

    /* On cherche les transitions qui n'existe pas*/
    for (int i = 0; i < res.nb_etat; i++)
    {
        for (int j = 0; j < res.nb_symbole; j++)
        {
            int trans_trouvee = 0;
            for (int k = 0; k < res.nb_transition; k++)
            {
                if (res.transition[k].etat_depart == i && strcmp(res.transition[k].alphabet, (char[]) {alphabet[j], '\0'}) == 0)
                {
                    trans_trouvee = 1;
                    break;
                }
            }

            /* Si une transition eciste pas ajout transition vers l'état poubelle */
            if (trans_trouvee == 0 )
            {
                res.transition[res.nb_transition].etat_depart = i;
                strcpy(res.transition[res.nb_transition].alphabet, (char[]) {alphabet[j], '\0'});
                res.transition[res.nb_transition].etat_arrivee = poubelle;
                res.nb_transition++;
            }
        }
    }
    return res;
}

int est_standard(automate test)
{
    int non_std = 0;
    /*Vérifaction que le nombre d'états initiaux n'est pas supérieur à 1*/
    if (test.nb_etat_initiaux > 1)
    {
        non_std = 1;
        printf("L'automate n'est pas standard car il possede plusieurs etats initiaux : %d \n", test.nb_etat_initiaux);

    }
    /*Vérifaction qu'il n'existe pas de transition depuis d'autre état vers l'état initial*/
    for (int i = 0; i < test.nb_transition; i++)
    {

        for(int j =0; j < test.nb_etat_initiaux;j++)
        {
            if(test.transition[i].etat_arrivee == test.etats_initiaux[j])
            {
                non_std = 1;
                printf("L'automate n'est pas standard car il possede une transition %d ->  %d vers un etat initial :  %d \n",test.transition[i].etat_depart, test.transition[i].etat_arrivee, test.transition[i].etat_arrivee);

            }
        }
    }

    if(non_std == 0)
    {
        printf("L'automate est standard\n");
        return 1;
    }
    else
    {
        return 0;
    }

}

automate standardisation(automate test)
{
    automate res;
    /*Dans le nouvelle automate on lui rajoute un état*/
    res.nb_etat = test.nb_etat + 1;
    res.nb_symbole = test.nb_symbole;
    /* On définit le nombre d'état initiaux à 1 car dans un automate standard il n'y a en qu'un*/
    res.nb_etat_initiaux = 1;
    /*On conserve pour l'instant le même nombre d'état initiaux si l'etat initial est un état termianl on le rajouteras plus tard*/
    res.nb_etats_terminaux = test.nb_etats_terminaux;
    res.nb_transition = 0;

    /*On définit l'unique etat initial comme le dernier état ajouté*/
    res.etats_initiaux[0] = test.nb_etat;

    /*Les états terminaux sont copier dans le nouveaux automate standard en construction*/
    for (int i = 0; i < test.nb_etats_terminaux; i++)
    {
        res.etats_terminaux[i] = test.etats_terminaux[i];
    }

    /*Vérification si l'état initial est aussi un état termianl selon la condition suivante : (i est terminal ssi au moins un des
états initiaux de C est terminal*/
    int term = 0;
    for (int i = 0; i < test.nb_etat_initiaux; i++)
    {
        for (int j = 0; j < test.nb_etats_terminaux; j++)
        {
            if (test.etats_initiaux[i] == test.etats_terminaux[j])
            {
                term = 1;
                break;
            }
        }
    }

    /* Si termianl on l'ajoute au tableau des états terminaux et on oublie pas d'incrémenter le nombre d'états termianl*/
    if (term == 1 )
    {
        res.etats_terminaux[res.nb_etats_terminaux] = test.nb_etat; // L'état i est terminal
        res.nb_etats_terminaux++;
    }

    /*Création des transitions depuis le nouveau unique état initiaux*/
    for (int i = 0; i < test.nb_etat_initiaux; i++)
    {
        int etat_init = test.etats_initiaux[i];

        for (int j = 0; j < test.nb_transition; j++)
        {
            if (test.transition[j].etat_depart == etat_init)
            {
                res.transition[res.nb_transition] = test.transition[j];
                res.transition[res.nb_transition].etat_depart = test.nb_etat;
                res.nb_transition++;
            }
        }
    }
    /*Ajout des transitions restantes de l'automate*/
    for (int i = 0; i < test.nb_transition; i++)
    {
        if (test.transition[i].etat_depart != test.nb_etat)
        {
            res.transition[res.nb_transition] = test.transition[i];
            res.nb_transition++;
        }
    }

    return res;
}



/*Fonction permettant de verifier si un sous ensemble existe déjà ou pas dans etats determinisé */
int trouver_sous_ensemble(int *sous_ensemble, int nb_etats_sous_ensemble,int etats_determines[100][100], int *taille_subset, int nb_sous_ensembles)
{
    /*On parcourt les ensembles*/
    for (int i = 0; i < nb_sous_ensembles; i++)
    {
        /* Si les tailles sont diffèrentes c'est pas le même sous ensemble*/
        if (taille_subset[i] != nb_etats_sous_ensemble)
        {
            continue;
        }
        bool identique = true;
        /*Verifie si elmts sous_ensembles sont identique*/
        for (int j = 0; j < nb_etats_sous_ensemble; j++)
        {
            /*Si on trouve etats diffèrents sous ensemble forcement diffèrents*/
            if (etats_determines[i][j] != sous_ensemble[j])
            {
                identique = false;
                break;
            }
        }
        /*Si deja existant on retourne son index */
        if (identique)
        {
            return i;
        }

    }
    /* Sinon on retourne -1*/
    return -1;
}
 /* Fonction pour determiner si un sous esemble contient un état terminal de l'automate non déterministe */
 /*Si il en contient 1 alors ce sous ensemble doit être terminal*/
int est_sous_ensemble_terminaux(int *sous_ensemble, int nb_etats_sous_ensemble,int etats_terminaux[100], int nb_etats_terminaux)

{
    for (int i = 0; i < nb_etats_sous_ensemble; i++)
    {
        for (int j = 0; j < nb_etats_terminaux; j++)
        {
            /*On compare si les états dans le sous ensemble coresspond aux à un des etats terminaux de l'automae déterministe*/
            if (sous_ensemble[i] == etats_terminaux[j])
            {
                return 1;
            }
        }
    }
    return 0;
}


void determiniser(automate *non_det, automate_deterministe *det) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int nb_sous_ensembles = 0;
    int queue_sous_ensembles[100];
    int taille_file = 0;

    /*Le nombre de symbole utilisé dans l'automate non déterministe est le même que dans un automate déterministe*/
    det->nb_symbole = non_det->nb_symbole;

    int sous_ensemble_initial[100];
    int nb_etats_sous_ensemble = 0;

    /*Création du sous ensemble initial*/
    for (int i = 0; i < non_det->nb_etat_initiaux; i++) {
        sous_ensemble_initial[nb_etats_sous_ensemble++] = non_det->etats_initiaux[i];
    }

    /*Sous ensemble initial ajouté dans nouveau états créer*/
    memcpy(det->etats_determines[nb_sous_ensembles], sous_ensemble_initial, sizeof(int) * nb_etats_sous_ensemble);
    /*On met la taille ce sous ensemble dans notre tablea réservé à ça*/
    det->taille_subset[nb_sous_ensembles] = nb_etats_sous_ensemble;
    queue_sous_ensembles[taille_file++] = nb_sous_ensembles;
    nb_sous_ensembles++;

    /*Initialisation de l'automate déterministe*/

    det->nb_etat = nb_sous_ensembles; /* Sera égal a un pour l'instant car on a créer que l'etat initail pour l'instant*/
    det->etat_initial[0] = 0;  /*Le zéro correspond à l'indice ou est stocké l'etat initial dans le tableau etats_déteminé*/
    det->nb_etats_terminaux = 0;
    det->nb_transition = 0;

    /*On détermine si l'etat initial est aussi termianl*/
    if (est_sous_ensemble_terminaux(sous_ensemble_initial, nb_etats_sous_ensemble, non_det->etats_terminaux,
                                    non_det->nb_etats_terminaux) == 1) {
        det->etats_terminaux[det->nb_etats_terminaux][0] = 0;
        det->nb_etats_terminaux++;
    }

    /*On va maintenant s'occuper des états autre que l'etat initial*/
    while (taille_file > 0) {
        int index_sous_ensemble = queue_sous_ensembles[--taille_file];
        int *current_subset = det->etats_determines[index_sous_ensemble];
        int taille_current = det->taille_subset[index_sous_ensemble];

        /*On parcourt notre alphabet*/
        for (int i = 0; i < non_det->nb_symbole; i++) {
            char symbole = alphabet[i];
            /* Va servir a stocker les nv états avec ce symbole*/
            int new_subset[100];
            int nb_new_subset = 0;

            /*On determine transitions pour chaque état du sous ensemble avec la lettre de l'alpahebt actuelle*/
            for (int j = 0; j < taille_current; j++) {
                int etat = current_subset[j];
                for (int k = 0; k < non_det->nb_transition; k++) {
                    if (non_det->transition[k].etat_depart == etat && non_det->transition[k].alphabet[0] == symbole) {
                        /*Si des transitions sont trouvé avec ce symbole on rècupère état d'arrivée pour fabrication du nouveau sous ensemble*/
                        new_subset[nb_new_subset++] = non_det->transition[k].etat_arrivee;;
                    }
                }
            }


            if (nb_new_subset > 0) {
                /*On regarde si ce sous ensemble déja créer */
                int found = trouver_sous_ensemble(new_subset, nb_new_subset, det->etats_determines, det->taille_subset,
                                                  nb_sous_ensembles);
                int destination;
                /* Si n'existe pas le nouveau sous ensemble n'existe pas*/
                if (found == -1) {
                    /*On ajoute au nouveaux états déterminisé*/
                    memcpy(det->etats_determines[nb_sous_ensembles], new_subset, sizeof(int) * nb_new_subset);
                    det->taille_subset[nb_sous_ensembles] = nb_new_subset;
                    /*Index qui lui est associé*/
                    destination = nb_sous_ensembles;

                    /*On ajoute dans la file pour que cet état soit traiter par la suite*/
                    queue_sous_ensembles[taille_file++] = nb_sous_ensembles;
                    nb_sous_ensembles++;

                    /*On regarde si le nouveau sous ensemble est terminal*/
                    if (est_sous_ensemble_terminaux(new_subset, nb_new_subset, non_det->etats_terminaux,
                                                    non_det->nb_etats_terminaux)) {
                        det->etats_terminaux[det->nb_etats_terminaux][0] = destination;
                        det->nb_etats_terminaux++;
                    }
                }
                    /* S'il existe déjà alors on récupère juste son index */
                else {
                    destination = found;
                }

                /* Pour ce symbole on ajoute la transition correspondante*/
                /* Index du sous ensemble de départ ex le sous ensemble 1,3 est representé par l'indice 0*/
                det->transition[det->nb_transition].etat_depart[0] = index_sous_ensemble;
                det->transition[det->nb_transition].alphabet[0] = symbole;
                det->transition[det->nb_transition].etat_arrivee[0] = destination;
                det->nb_transition++;
            } else {
                /* Si transition n'est pas trouvé alors on ajouter une transitions vers l'etat poubelle représenté par -1*/
                det->transition[det->nb_transition].etat_depart[0] = index_sous_ensemble;
                det->transition[det->nb_transition].alphabet[0] = symbole;
                det->transition[det->nb_transition].etat_arrivee[0] = -1;
                det->nb_transition++;
            }
        }
    }

    det->nb_etat = nb_sous_ensembles;
    /*//Affichage temporaire ;

    for (int i = 0; i < det->nb_transition; i++) {

        printf("{");
        int first = 1;
        for (int j = 0; j < det->taille_subset[det->transition[i].etat_depart[0]]; j++) {
            if (first == 0) {
                printf(", ");
            } else {
                first = 0;
            }
            printf("%d", det->etats_determines[det->transition[i].etat_depart[0]][j]);
        }
        printf("} -> %c -> ", det->transition[i].alphabet[0]);


        if (det->transition[i].etat_arrivee[0] == -1) {
            printf("-1");
        } else {
            first = 1;
            printf("{");
            for (int j = 0; j < det->taille_subset[det->transition[i].etat_arrivee[0]]; j++) {
                if (!first) {
                    printf(", ");
                } else {
                    first = 0;
                }
                printf("%d", det->etats_determines[det->transition[i].etat_arrivee[0]][j]);
            }
            printf("}");
        }
        printf("\n");
    }*/
}


void afficher_automate_deterministe(automate_deterministe *det , automate  automate_inital) {
    printf("\n");
    int larg_col = 15;
    int cpt = 0;


    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    printf("%-*s", larg_col, " ");
    printf("%-*s", larg_col, " ");

    //affichage des lettres en haut
    for (int i = 0; i < det->nb_symbole; i++) {
        printf("%-*c", larg_col, alphabet[i]);
    }
    printf("\n");

    //affichage de E/S
    for (int i = 0; i < det->nb_etat; i++) {

        if (i == 0) {
            printf("E");
        }

        if (est_sous_ensemble_terminaux(det->etats_determines[i], det->taille_subset[i],
                                        automate_inital.etats_terminaux, det->nb_etats_terminaux) == 1) {
            if (i == 0) {
                printf("/S");
                for (int h = 0; h < (larg_col - 3); h++) {
                    printf(" ");
                }
            } else {
                printf("S");
                for (int h = 0; h < (larg_col - 1); h++) {
                    printf(" ");
                }
            }
        } else {
            if (i == 0) {
                for (int h = 0; h < (larg_col - 1); h++) {
                    printf(" ");
                }
            } else {
                for (int h = 0; h < (larg_col); h++) {
                    printf(" ");
                }
            }

        }



        //Affichage etat determiniÃ©

        for (int k = 0; k < det->taille_subset[i]; k++) {
            printf("%d", det->etats_determines[i][k]);
            if (k != det->taille_subset[i] - 1) {
                printf(",");
            }
        }
        for (int h = 0; h < (larg_col - (det->taille_subset[i] + (det->taille_subset[i] - 1))); h++) {
            printf(" ");
        }


        for (int j = 0; j < det->nb_symbole; j++) {

            if (det->transition[cpt].etat_arrivee[0] == -1) {
                printf("p");
                for (int h = 0; h < (larg_col - 1); h++) {
                    printf(" ");
                }
            } else {

                for (int k = 0; k < det->taille_subset[det->transition[cpt].etat_arrivee[0]]; k++) {
                    printf("%d", det->etats_determines[det->transition[cpt].etat_arrivee[0]][k]);
                    if (k != det->taille_subset[det->transition[cpt].etat_arrivee[0]] - 1) {
                        printf(",");
                    }
                }

                for (int h = 0; h < (larg_col - (det->taille_subset[det->transition[cpt].etat_arrivee[0]] +
                                                 (det->taille_subset[det->transition[cpt].etat_arrivee[0]] -
                                                  1))); h++) {
                    printf(" ");
                }

            }
            cpt++;

        }


        printf("\n");
    }
}


automate_deterministe automate_complementaire(automate_deterministe A)
{
    /*Tableau pour stocker les nv états terminaux*/
    int nouveaux_etats_terminaux[100] = {0};
    int nb_nouveaux_etats_terminaux = 0;

    /* Parcours les états de l'automates*/
    for (int i = 0; i < A.nb_etat; i++)
    {
        int trouve = 0;
        /* On regarde si l'etat actuel se retrouve dans le tableau des états terminaux si oui il est un etat terminal*/
        for (int j = 0; j < A.nb_etats_terminaux; j++)
        {
            if (A.etats_terminaux[j][0] == i)
            {
                trouve = 1;
                break;
            }
        }

        /* S'il n'est pas terminal cela veut dire qu'il doit le devenir*/
        if (trouve == 0)
        {
            nouveaux_etats_terminaux[nb_nouveaux_etats_terminaux++] = i;
        }
    }

    /*On copie les nouveaux etats terminaux dans l'automate_déterministe*/
    A.nb_etats_terminaux = nb_nouveaux_etats_terminaux;
    for (int i = 0; i < nb_nouveaux_etats_terminaux; i++)
    {
        A.etats_terminaux[i][0] = nouveaux_etats_terminaux[i];
    }

    return A;
}

