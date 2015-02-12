#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"
#include "fonctions.h"

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
                if (strstr(message, "ANC") == message)
                    serveur_nouvelUtilisateur(message);
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