#include <stdio.h>
#include "Automate.h"

int main()
{
    int choix_automate;
    printf("Quel automate voulez-vous  utiliser ?\n");
    scanf("%d",&choix_automate);
    automate AF;
    Stockagedonneesautomate(&AF,choix_automate);
    affichage_automate(AF);
    est_un_automate_deterministe(AF);
    completion(&AF);
    affichage_automate(AF);



    return 0;
}