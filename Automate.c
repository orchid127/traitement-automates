//
// Created by amabl on 20/02/2025.
//
#include <stdio.h>
#include "Automate.h"
#include "string.h"

void Stockagedonneesautomate(automate *test, int num_automate) {

    char filename[100];
    /* Permet de créer le chemin du fichier contenant l'automate désirer en fonction du numéro choisis*/
    snprintf(filename, sizeof(filename), "C:\\Users\\amabl\\CLionProjects\\Automatefini\\automate test\\Automate%d.txt", num_automate);

    FILE *file = fopen(filename, "r");

    /*Récupère sur la première ligne le nombre symbole utilisé*/
    fscanf(file, "%d", &test->nb_symbole);
    printf("Le nombre de symboles utilises est : %d\n", test->nb_symbole);

    /*Récupère sur la deuxième ligne le nombre d'état de l'automate*/
    fscanf(file, "%d", &test->nb_etat);
    printf("Le nombre d'etats utilises est : %d\n", test->nb_etat);

    /*Récupère sur la troisième ligne le nombre d'état initaux de l'automate et leurs numéros*/
    fscanf(file, "%d", &test->nb_etat_initiaux);
    printf("Le nombre d'etats initiaux est : %d\n", test->nb_etat_initiaux);
    printf("Les etats initiaux sont : ");
    for (int i = 0; i < test->nb_etat_initiaux; i++) {
        fscanf(file, "%d", &test->etats_initiaux[i]);
        printf("%d ", test->etats_initiaux[i]);
    }
    printf("\n");

    /*Récupère sur la quatrième ligne le nombre d'état finaux de l'automate et leurs numéros*/
    fscanf(file, "%d", &test->nb_etats_terminaux);
    printf("Le nombre d'etats terminaux est : %d\n", test->nb_etats_terminaux);
    printf("Les etats terminaux sont : ");
    for (int i = 0; i < test->nb_etats_terminaux; i++) {
        fscanf(file, "%d", &test->etats_terminaux[i]);
        printf("%d ", test->etats_terminaux[i]);
    }
    printf("\n");

    /*Récupère sur la cinquième ligne le nombre de transition de l'automate*/
    fscanf(file, "%d", &test->nb_transition);
    printf("\nLe nombre de transiton est %d\n", test->nb_transition);

    char buffer[100];
    int index =0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (index >= test->nb_transition)
        {
            break;
        }
        /* Si ligne vide on va à la prochaine**/
        if (buffer[0] == '\n' || buffer[0] == '\r') continue;


        int etat_depart, etat_arrivee;
        char symbole[50];

        /* Analyse de la ligne récupére pour extraire les information et verification d'extraire 3 données*/
        if (sscanf(buffer, "%d %s %d", &etat_depart, symbole, &etat_arrivee) == 3)
        {
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

    }

    /* Affichage des transitions */
    for (int i = 0; i < test->nb_transition; i++) {
        if (strcmp(test->transition[i].alphabet, "ε") == 0) {
            printf("Les transitions sont %d->epsilon->%d\n", test->transition[i].etat_depart, test->transition[i].etat_arrivee);
        } else
        {
            printf("Les transitions sont %d->%s->%d\n", test->transition[i].etat_depart, test->transition[i].alphabet, test->transition[i].etat_arrivee);
        }
    }


    fclose(file);
}


void affichage_automate(automate test) {
    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";
    int initial, terminal;
    int epsilon_existe = 0;

    /* Détection de transition avec ε */
    for (int i = 0; i < test.nb_transition; i++)
    {
        if (strcmp(test.transition[i].alphabet, "ε") == 0 )
        {
            epsilon_existe = 1;
            break;
        }
    }
    /*Affichage de l'alphabet de l'automate*/
    for (int i = 0; i < test.nb_symbole; i++)
    {
        printf("%7c", alphabet[i]);
    }
    /*Affichage colonne si il y a des transitions*/
    if (epsilon_existe == 1)
    {
        printf("    epsilon");
    }
    printf("\n");




    for (int i = 0; i < test.nb_etat; i++) {
        initial = 0;
        terminal = 0;


        for (int j = 0; j < test.nb_etat_initiaux; j++) {
            if (test.etats_initiaux[j] == i) {
                initial = 1;
                break;
            }
        }


        for (int j = 0; j < test.nb_etats_terminaux; j++) {
            if (test.etats_terminaux[j] == i) {
                terminal = 1;
                break;
            }
        }

        /*Affichage caractéristique de l'etat en cours*/
        if (initial && terminal) {
            printf("ES %2d", i);
        } else if (initial) {
            printf("E  %2d", i);
        } else if (terminal) {
            printf("S  %2d", i);
        } else {
            printf("   %2d", i);
        }

        /*Affichage des transitions*/
        for (int l = 0; l < test.nb_symbole; l++)
        {
            int transition_trouvee = 0;

            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, (char[]) {alphabet[l], '\0'}) == 0)
                {
                    printf("%5d", test.transition[k].etat_arrivee);
                    transition_trouvee = 1;
                }
            }
            /* Si une transition n'est pas trouvé on affiche -*/
            if (transition_trouvee == 0)
            {
                printf("    -");
            }
        }

        /* Affichage des transition avec ε */
        if (epsilon_existe)
        {
            int epsilon_trouve = 0;
            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && (strcmp(test.transition[k].alphabet, "ε") == 0 ))
                {
                    printf("%5d", test.transition[k].etat_arrivee);
                    epsilon_trouve = 1;
                }
            }

            if (epsilon_trouve == 0)
            {
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
        nondet =1;
        printf("L'automate n'est pas deterministe car il a plusieurs états initiaux\n");
    }

    while(nondet == 0 && i < test.nb_transition)
    {
        j = i+1;
        while(j<test.nb_transition)
        {
            if (test.transition[i].etat_depart == test.transition[j].etat_depart && test.transition[i].etat_arrivee != test.transition[j].etat_arrivee && test.transition[i].alphabet == test.transition[j].alphabet)
            {
                nondet = 1;
                printf("L'automate n'est pas deterministe car un etats a plusieurs chemin avec un meme symbole\n");

            }
            if (test.transition[i].etat_depart == i &&(strcmp(test.transition[i].alphabet, "ε") == 0 ||strcmp(test.transition[i].alphabet, "epsilon") == 0))
            {
                nondet = 1;
                printf("L'automate n'est pas deterministe car il possede des transitions avec des epsilon\n");
                break;
            }
            j++;
        }
        i++;
    }

    if (nondet == 0)
    {
        printf("L'automate est deterministe\n");
        return 1;

    }
    return 0;
}

int est_un_automate_complet(automate test)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";


    /* Cette boucle permet de déterminer si une transition est trouvé ou pas */
    for (int i = 0; i < test.nb_etat; i++)
    {
        for (int l = 0; l < test.nb_symbole; l++)
        {
            int trans_trouvee = 0;

            for (int k = 0; k < test.nb_transition; k++)
            {
                if (test.transition[k].etat_depart == i && strcmp(test.transition[k].alphabet, (char[]) {alphabet[l], '\0'}) == 0)
                {
                    trans_trouvee = 1;
                }
            }

            /* Si une transition n'est pas trouvé alors l'automate n'est pas complet*/
            if (trans_trouvee == 0)
            {
                printf("\nL'automate n'est pas complet\n");
                printf("\nTous les etats n'ont pas de transition vers un autre etat\n");
                return 0;
            }
        }
    }
    return 1;
}
int completion(automate *test)
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int poubelle = -1;

    /* Boucle pour trouver ou sont les transitions manquantes*/
    for (int i = 0; i < test->nb_etat; i++)
    {
        for (int l = 0; l < test->nb_symbole; l++)
        {
            int trans_trouvee = 0;
            char symbole = alphabet[l];


            for (int k = 0; k < test->nb_transition; k++)
            {
                if (test->transition[k].etat_depart == i && strcmp(test->transition[k].alphabet, (char[]){symbole, '\0'}) == 0)
                {
                    trans_trouvee = 1;
                    break;
                }
            }
            /*Création transition vers état poubelle*/
            if (trans_trouvee == 0)
            {
                test->transition[test->nb_transition].etat_depart = i;
                strcpy(test->transition[test->nb_transition].alphabet, (char[]){symbole, '\0'});
                test->transition[test->nb_transition].etat_arrivee = poubelle;
                test->nb_transition++;
            }
        }

        /*Trouve les transitions qui sont avec des espsilon*/
        int epsilon_trouvee = 0;
        for (int k = 0; k < test->nb_transition; k++)
        {
            if (strcmp(test->transition[k].alphabet, "ε") == 0 && test->transition[k].etat_depart == i) {
                epsilon_trouvee = 1;
                break;
            }
        }

        /* Création des transitions vers etat poubelle dans le cas de d'absence d'un espsilon*/
        if (epsilon_trouvee == 0)
        {
            test->transition[test->nb_transition].etat_depart = i;
            strcpy(test->transition[test->nb_transition].alphabet, "ε");
            test->transition[test->nb_transition].etat_arrivee = poubelle;
            test->nb_transition++;
        }
    }

    return 1;
}

int est_standard(automate test)
{
    if (test.nb_etat_initiaux > 1)
    {
        printf("L'automate n'est pas standard car il possède plusieurs états initiaux : %d", test.nb_etat_initiaux);

    }
    int retour_vers_etat_init = 0;
    for (int i = 0; i < test.nb_transition; i++)
    {

        for(int j =0; j < test.nb_etat_initiaux;j++)
        {
            if(test.transition[i].etat_arrivee == test.etats_initiaux[j])
            {
                printf("L'automate n'est pas standard car il possede une transition vers un etat initial :  %d ->  %d\n",test.transition[i].etat_depart, test.transition[i].etat_arrivee);
                retour_vers_etat_init = 1;
            }
        }
    }
    if(retour_vers_etat_init == 0)
    {
        printf("L'automate est standard\n");
    }
    return 1;
}