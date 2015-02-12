#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transport.h"
#include "fonctions.h"

/*
  gcc test_client.c transport.c -o test_client
  gcc test_serveur.c transport.c -o test_serveur
*/

int main()
{
    char* message;
    client_init("localhost", "5050");

    client_emission("HEL test_$");
    client_nouvelUtilisateur();

    message = client_reception();
    if (message!=NULL)
    {
    	printf("Reception d'un message:\n");
    	printf("%s\n", message);
    }
    client_terminaison();

    return 0;
}