/*
** transport.c
** -----------
** Offre un service de transport pour que le protocole application de niveau
** supérieur puisse fonctionner.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>

#include "transport.h"

/*
** Variables partagées entre les différentes fonctions
*/

int socket_client;
int socket_serveur;
int socket_ecoute;

socklen_t taille_adresse;

char tampon_client[LONGUEUR_TAMPON];
char tampon_serveur[LONGUEUR_TAMPON];

int debut_tampon_client;
int fin_tampon_client;
int debut_tampon_serveur;
int fin_tampon_serveur;

bool serveur_fin_connexion;
bool client_fin_connexion;

/*
** Initialise le socket client et se connecte au serveur donné
** Retourne 0 si succès, -1 sinon
*/
int client_init(char *machine, char* port) {
    int n;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(machine, port, &hints, &res)) )
    {
        fprintf(stderr, "client_init(), erreur de getaddrinfo() : %s", gai_strerror(n));
        return -1;
    }

    ressave = res;

    do {
        socket_client = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socket_client < 0)
            continue;   /* ignore this one */

        if ( !connect(socket_client, res->ai_addr, res->ai_addrlen) )
            break;      /* SUCESS */

        close(socket_client);    /* ignore this one */
    } while ( (res = res->ai_next) != NULL );

    if (res == NULL) {
            perror("client_init(), erreur de connect()");
            return -1;
    }

    freeaddrinfo(ressave);

    client_fin_connexion = false;

    printf("Connexion avec le serveur réussie.\n");

    return 0;
}

/*
** Initialise le socket serveur
** Retourne 0 si succès, -1 sinon
*/
int serveur_init(char* port) {
    int n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    bzero(&hints, sizeof(struct addrinfo));

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(NULL, port, &hints, &res)) != 0 )
    {
        fprintf(stderr, "getaddrinfo() failed, error : %s", gai_strerror(n));
        return -1;
    }

    ressave = res;

    do {
        socket_ecoute = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socket_ecoute < 0)
            continue;       /* error, try next one */

        setsockopt(socket_ecoute, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

        if (bind(socket_ecoute, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* SUCESS */

        close(socket_ecoute);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("bind error");
            return -1;
    }

    taille_adresse = res->ai_addrlen;

    freeaddrinfo(ressave);
    listen(socket_ecoute, 4);
    printf("Init sucess! Socket listening and bound to port: %s\n", port);

    return 0;
}

/*
** Attends qu'un client se connecte sur le serveur
** Retourne 0 si fin normale, -1 si erreur
*/
int serveur_attente_client() {
    struct sockaddr *clientAddr;
    char machine[NI_MAXHOST];

    printf("Attente d'une connexion sur le socket...\n");

    clientAddr = (struct sockaddr*) malloc(taille_adresse);
    socket_serveur = accept(socket_ecoute, clientAddr, &taille_adresse);
    if (socket_serveur == -1) {
        perror("serveur_attente_client(), erreur de accept.");
        return -1;
    }
    if(getnameinfo(clientAddr, taille_adresse, machine, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
        printf("Client sur la machine d'adresse %s connecté.\n", machine);
    } else {
        printf("Client anonyme connecté.\n");
    }
    free(clientAddr);

    /*
    ** Reinit buffer
    */
    debut_tampon_serveur = 0;
    fin_tampon_serveur = 0;
    serveur_fin_connexion = false;

    return 0;
}

/*
** Recoit un message envoyé par le client
** Retourne un pointeur vers l'emplacement du message
*/
char *serveur_reception() {
    char message[LONGUEUR_TAMPON];
    int index = 0;
    int fini = false;
    int retour = 0;
    int trouve = false;
    debut_tampon_serveur = fin_tampon_serveur = 0;

    if(serveur_fin_connexion)
    {
        return NULL;
    }

    while(!fini)
    {
        /* on cherche dans le tampon courant */
        while((fin_tampon_serveur > debut_tampon_serveur) && (!trouve) &&
          (index < LONGUEUR_TAMPON-1))
        {

            message[index] = tampon_serveur[debut_tampon_serveur];

            if (index > 0)
                if ((message[index]=='$') && (message[index-1]=='_'))
                    trouve = true;
            
            index++;
            debut_tampon_serveur++;

        }
        /* on a trouve ? */
        if (trouve)
        {
            message[index] = '\0';
            fini = true;
            // fprintf(stderr, "trouve\n");

            return strdup(message);

        }
        else if (index == LONGUEUR_TAMPON-2 && !trouve)
        {
            fprintf(stderr, "Taille max du tampon atteint: index: %u\n", index);
            message[index] = '\0';
            fini = true;
            return strdup(message);
        }
        else
        {
            /* il faut en lire plus */
            debut_tampon_serveur = 0;
            fprintf(stderr, "recv\n");
            retour = recv(socket_serveur, tampon_serveur, LONGUEUR_TAMPON, 0);
            fprintf(stderr, "retour : %d\n", retour);
            int i;
            for (i = 0; i<retour; i++)
            fprintf(stderr, "tampon_serveur[%u]=%c\n", i, tampon_serveur[i]);
            if (retour < 0) {
                perror("serveur_reception(), erreur de recv");
                return NULL;
            } else if(retour == 0) {
                fprintf(stderr, "serveur_reception(), le client a ferme la connexion.\n");
                serveur_fin_connexion = true;
                // on n'en recevra pas plus, on renvoie ce qu'on avait ou null sinon
                if(index > 0) {
                    message[index] = '\0';
                    return strdup(message);
                } else {
                    return NULL;
                }
            } else {
                /* on a recu "retour" octets */
                fin_tampon_serveur = retour;
            }
        }
    }
    return NULL;
}


/*
** Recoit un message envoyé par le client
** Retourne un pointeur vers l'emplacement du message
*/
char *client_reception() {
    char message[LONGUEUR_TAMPON];
    int index = 0;
    int fini = false;
    int retour = 0;
    int trouve = false;
    debut_tampon_client = fin_tampon_client = 0;

    if(client_fin_connexion)
    {
        return NULL;
    }

    while(!fini)
    {
        /* on cherche dans le tampon courant */
        while((fin_tampon_client > debut_tampon_client) && (!trouve) &&
          (index < LONGUEUR_TAMPON-1))
        {

            message[index] = tampon_client[debut_tampon_client];

            if (index > 0)
                if ((message[index]=='$') && (message[index-1]=='_'))
                    trouve = true;
            
            index++;
            debut_tampon_client++;

        }
        /* on a trouvé "_$" ? */
        if (trouve)
        {
            message[index] = '\0';
            fini = true;
            return strdup(message);

        }
        else if (index == LONGUEUR_TAMPON-2 && !trouve)
        {
            fprintf(stderr, "Taille max du tampon atteint: index: %u\n", index);
            message[index] = '\0';
            fini = true;
            return strdup(message);
        }
        else
        {
            /* il faut en lire plus */
            debut_tampon_client = 0;
            fprintf(stderr, "recv\n");
            retour = recv(socket_client, tampon_client, LONGUEUR_TAMPON, 0);
            fprintf(stderr, "retour : %d\n", retour);
            int i;
            for (i = 0; i<retour; i++)
            fprintf(stderr, "tampon_client[%u]=%c\n", i, tampon_client[i]);
            if (retour < 0) {
                perror("client_reception(), erreur de recv");
                return NULL;
            } else if(retour == 0) {
                fprintf(stderr, "client_reception(), le serveur a ferme la connexion.\n");
                client_fin_connexion = true;
                // on n'en recevra pas plus, on renvoie ce qu'on avait ou null sinon
                if(index > 0) {
                    message[index] = '\0';
                    return strdup(message);
                } else {
                    return NULL;
                }
            } else {
                /* on a recu "retour" octets */
                fin_tampon_client = retour;
            }
        }
    }
    return NULL;
}

/* 
** Envoie un message au serveur.
** Attention, le message doit etre termine par "_$"
** Retourne le nombre de caractères émis ou -1 si erreur.
*/
int client_emission(char *message) {
    int taille, emis;
    taille = strlen(message);

    if(message[taille-2] != '_' || message[taille-1] != '$') {
        fprintf(stderr, "Erreur émission : le message n'est pas terminé par \"_$\"\n");
        return -2;
    }

    if(taille > LONGUEUR_TAMPON-2) {
        fprintf(stderr, "Erreur émission : le message est trop long : %u > %u\n", taille, LONGUEUR_TAMPON-2);
        return -3;
    }

    if(taille < 6) {
        fprintf(stderr, "Erreur émission : le message est trop court : %u < 6\n", taille);
        return -4;
    }
/*
    printf("Message à émettre:\n");
    int i = 0;
    while (i < taille)
    {
        printf("%#04x ", message[i++]);
    }
    printf("\n");
    i = 0;
    while (i < taille)
    {
        printf("%c", message[i++]);
    }
    printf("\n");
    printf("Taille: %u bytes\n", taille);
*/
    if ((emis = send(socket_client, message, taille, 0)) == -1) {
        perror("client_emission(), problème lors du send");
        return -1;
    }
    printf("Emission de %d bytes\n", emis);
    return emis;
}


/* 
** Envoie un message au client.
** Attention, le message doit etre termine par "_$"
** Retourne le nombre de caractères émis ou -1 si erreur.
*/
int serveur_emission(char *message) {
    int taille, emis;
    taille = strlen(message);

    if(message[taille-2] != '_' || message[taille-1] != '$') {
        fprintf(stderr, "Erreur émission : le message n'est pas terminé par \"_$\"\n");
        return -2;
    }

    if(taille > LONGUEUR_TAMPON-2) {
        fprintf(stderr, "Erreur émission : le message est trop long : %u > %u\n", taille, LONGUEUR_TAMPON-2);
        return -3;
    }

    if(taille < 6) {
        fprintf(stderr, "Erreur émission : le message est trop court : %u < 6\n", taille);
        return -4;
    }
/*
    printf("Message à émettre:\n");
    int i = 0;
    while (i < taille)
    {
        printf("%#04x ", message[i++]);
    }
    printf("\n");
    i = 0;
    while (i < taille)
    {
        printf("%c", message[i++]);
    }
    printf("\n");
    printf("Taille: %u bytes\n", taille);
*/
    if ((emis = send(socket_serveur, message, taille, 0)) == -1) {
        perror("serveur_emission(), problème lors du send");
        return -1;
    }
    printf("Emission de %d bytes\n", emis);
    return emis;
}

/*
** Ferme la connexion avec le serveur (coté client)
*/
void client_terminaison() {
    close(socket_client);
}

/*
** Ferme la connexion avec le client (coté serveur)
*/
void serveur_terminaison() {
    close(socket_serveur);
}

/*
** Arrete d'écouter pour des connexions entrantes (coté serveur)
*/
void serveur_arreter_ecoute() {
    close(socket_ecoute);
}
