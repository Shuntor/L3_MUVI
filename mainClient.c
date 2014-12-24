#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main() {
	char *message;

	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

	if(Emission("Test de message client1.\n")!=1) {
		printf("Erreur d'emission\n");
		return 1;
	}
	if(Emission("Test de message client2.\n")!=1) {
		printf("Erreur d'emission\n");
		return 1;
	}
	if(Emission("Test de message client3.\n")!=1) {
		printf("Erreur d'emission\n");
		return 1;
	}

	message = Reception();
	if(message != NULL) {
		printf("J'ai recu: %s\n", message);
		free(message);
	} else {
		printf("Erreur de reception\n");
		return 1;
	}

	message = Reception();
	if(message != NULL) {
		printf("J'ai recu: %s\n", message);
		free(message);
	} else {
		printf("Erreur de reception\n");
		return 1;
	}

	message = Reception();
	if(message != NULL) {
		printf("J'ai recu: %s\n", message);
		free(message);
	} else {
		printf("Erreur de reception\n");
		return 1;
	}

	Terminaison();

	return 0;
}
