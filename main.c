#include <stdio.h>
#include "Automate.h"
#include "stdlib.h"
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
                printf("Automate Deterministe et complet : \n");
                affichage_automate(AF);
            }
            else
            {
                AF = completion(AF);
                printf("Automate Deterministe et complet : \n");
                affichage_automate(AF);

            }
        }
        else
        {
            determiniser(&AF,&AFDC);
            afficher_automate_deterministe(&AFDC);

        }

        /*Marche pas avec tous les automates*/
        /*printf("Voulez vous l'automate complementaire de celui etudie precedamment : (Oui : 1) (Non : 0)");
        scanf("%d",&choix_complementaire);
        if(choix_complementaire == 1 )
        {
            AFDCC = automate_complementaire(AFDC);
            afficher_automate_deterministe(&AFDCC);
        }*/


        printf("Voulez vous faire un autre automate\n");
        scanf("%d",&nombre_automate);



    }
    printf("Sortie du programme");
    return 0;
}