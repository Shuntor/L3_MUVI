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
            message = serveur_reception();

            if(message != NULL) 
            {
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