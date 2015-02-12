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
                printf("inc_taille: %d bytes\n", (int)strlen(message));
                printf("inc: %s\n", message);
                if (strstr(message, "ANC") == message)
                    serveur_nouvelUtilisateur(message);
                else if (strstr(message, "ACL") == message)
                    // serveur_auth_client();
                else if (strstr(message, "SCL") == message)
                    // serveur_suppr_client();
                else if (strstr(message, "DME") == message)
                    // serveur_nouvel_objet();
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