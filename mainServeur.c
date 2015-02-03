#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"
#include "serveur.h"

int main()
{
    char *message = NULL;
    int fini = 0;

    printf("%s\n", "Initialisation...");
    Initialisation();
    printf("%s\n", "Initialisation fini.");

    while(1)
    {
        fini = 0;

        printf("%s\n", "Attente d'un client...");
        AttenteClient();

        while(!fini)
        {
            printf("%s\n", "Reception...");
            message = Reception(); 

            if(message != NULL)
            {
                printf("J'ai reçu: %s\n", message);
                free(message);
            }
            else
            {
                fini = 1;
            }
        }

        TerminaisonClient();
    }

    return 0;
}