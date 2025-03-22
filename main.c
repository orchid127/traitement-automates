#include <stdio.h>
#include "Automate.h"
#include "stdlib.h"
#include "Automate_Reco.h"
#include "Automate_Reco.c"
int main()
{
    int nombre_automate = 1;
    int choix_complementaire;
    automate_deterministe AFDCC;
    automate AF;
    automate_deterministe AFDC;
    automate SFA;
    int rep_standard = 0;

    while (nombre_automate == 1) {
        int choix_automate;
        printf("Quel automate voulez-vous  utiliser ?\n");
        scanf("%d", &choix_automate);


        Stockage_donnees_automate(&AF, choix_automate);
        affichage_automate(AF);

        if (est_standard(AF) == 0) {
            printf("Voulez-vous standardiser l'automate ? (0:Non , 1:Oui)\n");
            scanf("%d", &rep_standard);

            if (rep_standard == 1)
            {
                printf("Voici l'automate standardisé\n");
                SFA = standardisation(AF);
                affichage_automate(SFA);
            }
            else
            {
                printf("L'automate ne sera pas standardiser.\n");
            }

        }
        if (est_un_automate_deterministe(AF)==1)
        {
            if (est_un_automate_complet(AF)==1)
            {
                /*Déterminisation ne sert a rien ici mais permet le caste en structure automate déterministe*/
                determiniser(&AF,&AFDC);
            }
            else
            {
                /*Déterminiser ici permet la completion et le caste en structure automate déterministe*/
                determiniser(&AF,&AFDC);
            }
        }
        else
        {
            determiniser(&AF,&AFDC);
        }
        printf("Voici l'automate determinise et complet :\n");
        afficher_automate_deterministe(&AFDC,AF);


        printf("Voulez vous l'automate complementaire de celui etudie precedamment : (Oui : 1) (Non : 0)");
        scanf("%d",&choix_complementaire);
        if(choix_complementaire == 1 )
        {
            AFDCC = automate_complementaire(AFDC);
            printf("L'automate complementaire est le suivant\n");
            afficher_automate_deterministe(&AFDCC,AF);
        }


        char mots[100];
        int res_mots;
        lire_ligne(mots);
        while(strcmp(mots, "Fin") != 0)
        {
            res_mots = reconnaitre_mot(&AFDC,mots);
            if (res_mots == 1)
            {
                printf("Mots reconnu par l'automate");
            }
            else
            {
                printf("Mots non reconnu par l'automate");
            }
            lire_ligne(mots);
        }



        printf("\n");
        printf("Voulez vous faire un autre automate\n");
        scanf("%d",&nombre_automate);

    }
    printf("Sortie du programme");
    return 0;
}
