#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"

int main()
{
    char *message = NULL;
    int fini = 0;

    serveur_init("5050");

    while(1)
    {
        fini = 0;

        serveur_attente_client();


        while(!fini)
        {
                printf("avant recep fini\n");
            message = serveur_reception();
                printf("recep fini\n");

            if(message != NULL) 
            {
                printf("Reception d'un message:\n");
                printf("%s\n", message);
                serveur_emission("GUT too_$");
            }
            else
            {
                fini = 1;
            }
        }


        serveur_terminaison();
    }

    return 0;
}