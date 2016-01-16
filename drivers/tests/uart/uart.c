/*
 * Created by Thibault PIANA on 12/12/15.
*/

#include <stdio.h>
#include <stdlib.h>

int kmain()
{
    int nombreMystere = 0, nombreEntre = 0;
    const int MAX = 100, MIN = 1;

    // Génération du nombre aléatoire

    srand(0);
    nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

    /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */

    do
    {
        // On demande le nombre
        printf("Quel est le nombre ? ");
        scanf("%d", &nombreEntre);

        // On compare le nombre entré avec le nombre mystère

        if (nombreMystere > nombreEntre)
            printf("C'est plus !\n\n");
        else if (nombreMystere < nombreEntre)
            printf("C'est moins !\n\n");
        else
            printf ("Bravo, vous avez trouve le nombre mystere !!!\n\n");
    } while (nombreEntre != nombreMystere);

    return 0;
}