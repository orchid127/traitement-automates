#include <stdio.h>
#include "Automate.h"
#include "stdlib.h"
int main()
{
    int nombre_automate = 1;
    while (nombre_automate == 1) {
        int choix_automate;
        printf("Quel automate voulez-vous  utiliser ?\n");
        scanf("%d", &choix_automate);
        automate AF;
        automate AFDC;
        automate SFA;

        Stockage_donnees_automate(&AF, choix_automate);
        affichage_automate(AF);

        if (est_standard(AF) == 0) {
            int rep = 0;
            printf("Voulez-vous standardiser l'automate ? (0:Non , 1:Oui)\n");
            scanf("%d", &rep);
            if (rep == 1) {
                SFA = standardisation(AF);
                affichage_automate(SFA);
            } else {
                printf("L'automate ne sera pas standardiser.\n");
            }

        }
        if (est_un_automate_deterministe(AF))
        {
            if (est_un_automate_complet(AF))
            {
                AFDC = AF;
            } else {
                AFDC = completion(AF);
            }
        }
        automate AC = completion(AF);
        affichage_automate(AC);
        printf("Voulez vous faire un autre automate\n");
        scanf("%d",&nombre_automate);
    }
    printf("Sortie du programme");
    return 0;
}