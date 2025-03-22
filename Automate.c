//
// Created by amabl on 20/02/2025.
//
#include <stdio.h>
#include "Automate.h"
#include "string.h"
#include "queue.h"
#include <string.h>

void Stockage_donnees_automate(automate *test, int num_automate) {

    char filename[100];
    /* Permet de créer le chemin du fichier contenant l'automate désirer en fonction du numéro choisis*/
    snprintf(filename, sizeof(filename), "C:\\Users\\Kimberley\\CLionProjects\\traitement-automates\\automate-test\\Automate%d.txt", num_automate);

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
    int init, term;
    int epsi_trouv = 0;


    int premier_lettre = 0;

    /*Affichage de l'alphabet de l'automate*/
    for (int i = 0; i < test.nb_symbole; i++)
    {
        if(premier_lettre == 0)
        {
            printf("%10c", alphabet[i]);
            premier_lettre =1;
        }
        else
        {
            printf("%6c", alphabet[i]);
        }
    }

    /* Détection de transition avec epsilon */
    for (int i = 0; i < test.nb_transition; i++)
    {
        if (strcmp(test.transition[i].alphabet, "ε") == 0 )
        {
            epsi_trouv = 1;
            break;
        }
    }

    /*Affichage colonne epsilon si il y a des transitions epsilon dans l'automate sinon non*/
    if (epsi_trouv == 1)
    {
        printf("    epsilon");
    }
    printf("\n");

    for (int i = 0; i < test.nb_etat; i++)
    {
        init = 0;
        term = 0;
        /*Vérification si l'etat étudié est un état initial*/
        for (int j = 0; j < test.nb_etat_initiaux; j++)
        {
            if (test.etats_initiaux[j] == i) {
                init = 1;
                break;
            }
        }
        /*Vérification si l'etat étudié est un état terminal*/
        for (int j = 0; j < test.nb_etats_terminaux; j++)
        {
            if (test.etats_terminaux[j] == i) {
                term = 1;
                break;
            }
        }

        /*Affichage caractéristique de l'etat en cours en fonction des résultats trouvé avant*/
        if (init && term)
        {
            printf("ES %2d", i);
        }
        else if (init)
        {
            printf("E  %2d", i);
        }
        else if (term)
        {
            printf("S  %2d", i);
        }
        else
        {
            printf("   %2d", i);
        }

        /* Affichage des transitions */
        for (int l = 0; l < test.nb_symbole; l++)
        {
            int trans_trouv = 0;
            int first = 1;
            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, (char[]) {alphabet[l], '\0'}) == 0) {
                    if (first == 1 )
                    {
                        printf("    ");
                    }
                    if (first ==0)
                    {
                        printf(",");
                    }

                    printf("%d", test.transition[k].etat_arrivee);
                    trans_trouv = 1;
                    first = 0;
                }
            }

            if (trans_trouv == 0)
            {
                printf("   -");
            }


            if (l != test.nb_symbole - 1)
            {
                printf("");
            }
        }

        /* Affichage des transitions avec epsilon */
        if (epsi_trouv) {
            int epsi = 0;
            int first_epsi = 1;

            for (int k = 0; k < test.nb_transition; k++)
            {

                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, "ε") == 0)
                {
                    if (first_epsi ==1)
                    {
                        printf("    ");
                    }

                    if (first_epsi ==0)
                    {
                        printf(",");
                    }

                    printf("%d", test.transition[k].etat_arrivee);
                    epsi = 1;
                    first_epsi = 0;
                }
            }


            if (epsi == 0) {
                printf("    -");
            }
        }

        printf("\n");
    }
}

int est_un_automate_deterministe(automate test)
{
    int nondet = 0;
    int i = 0;
    int j = 0;

    /*Verification si le nombre d'etats initiaux supérieur à 1*/
    if (test.nb_etat_initiaux > 1 )
    {
        nondet = 1;
        printf("L'automate n'est pas deterministe car il a plusieurs etats initiaux\n");
        return 0;
    }

    for (i = 0; i < test.nb_transition; i++)
    {
        /* Vérification des transitions epsilon*/
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
                nondet = 1;
                printf("L'automate n'est pas deterministe car l'etat %d a plusieurs transitions avec le symbole '%s' vers differents etats %d et %d \n",test.transition[i].etat_depart,test.transition[i].alphabet,test.transition[i].etat_arrivee,test.transition[j].etat_arrivee);
            }
        }
    }

    if (nondet == 0)
    {
        printf("L'automate est deterministe\n");
        return 1;

    }
    return 1;


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

    /* Vérification existance au moins une transition epsilon */
    int trouv_epsi = 0;
    for (int i = 0; i < test.nb_transition; i++)
    {
        if (strcmp(test.transition[i].alphabet, "ε") == 0)
        {
            trouv_epsi = 1;
            break;
        }
    }


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

            /* Ajout transition vers l'état poubelle */
            if (trans_trouvee == 0 )
            {
                res.transition[res.nb_transition].etat_depart = i;
                strcpy(res.transition[res.nb_transition].alphabet, (char[]) {alphabet[j], '\0'});
                res.transition[res.nb_transition].etat_arrivee = poubelle;
                res.nb_transition++;
            }
        }

        /* Ajouter les transitions epsilon si l'automate en avait déjà déjà */
        if (trouv_epsi)
        {
            int epsilon_trouvee = 0;
            for (int k = 0; k < res.nb_transition; k++) {
                if (strcmp(res.transition[k].alphabet, "ε") == 0 && res.transition[k].etat_depart == i) {
                    epsilon_trouvee = 1;
                    break;
                }
            }

            if (epsilon_trouvee == 0 )
            {
                res.transition[res.nb_transition].etat_depart = i;
                strcpy(res.transition[res.nb_transition].alphabet, "ε");
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
    /*Vérifaction qu'il n'existe pas de transition depuis d'autre état ver l'état initial*/
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

void determinisation(automate test){
    automate newAutomate;
    newAutomate.nb_etat_initiaux = 1;
    newAutomate.etats_initiaux[0] = 13;

    int *temp = test.etats_initiaux;

    p_queue etatsA = createQueue();
    p_queue etatsB = createQueue();

    for (int i = 0; i < test.nb_transition; i++){
        int curr = temp[i];
        if (strcmp(test.transition[i].alphabet, "a") == 0 && test.transition[i].etat_depart == curr) {
            enqueue(etatsA, test.transition[i].etat_arrivee);
        }
        else if (strcmp(test.transition[i].alphabet, "b") == 0 && test.transition[i].etat_depart == curr) {
            enqueue(etatsB, test.transition[i].etat_arrivee);
        }
    }

    displayQueue(etatsA);
    displayQueue(etatsB);
}