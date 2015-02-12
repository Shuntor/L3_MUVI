#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"
#include "serveur.h"

/* TODO:

- Switch suivant les cas des messages
- Renvoyer une erreur quand le message est trop grand

*/

int main()
{
    char *message = NULL;
    message = (char*) malloc(4096);
    int ret;

    int fini = 0;

    Initialisation();

    while(1)
    {
        fini = 0;

        AttenteClient();

        while(!fini)
        {
            ret = ReceptionBinaire(message, 4096);

            if(message != NULL) 
            {
                int i = 0;
                while (i < ret)
                {
                    printf("%03u ", message[i++]);
                }
                printf("\n");
                printf("%04u\n\n", ret);
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