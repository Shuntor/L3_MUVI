#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"
#include "fonctions.h"
#include "protocole.h"

int main()
{
    char *message = NULL;
    int fini = 0;

    serveur_init(SERVER_PORT);

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
                    serveur_auth_user(message);
                else if (strstr(message, "SCL") == message)
                    NULL;
                    // serveur_suppr_client();
                else if (strstr(message, "DME") == message)
                    NULL;
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