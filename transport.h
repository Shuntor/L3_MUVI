/*
** transport.h
** -----------
** Offre un service de transport pour que le protocole application de niveau
** supérieur puisse fonctionner.
*/

#ifndef __TRANSPORT_H__
#define __TRANSPORT_H__

#define LONGUEUR_TAMPON 300

/*
** Initialise le socket client et se connecte au serveur donné
** Retourne 0 si succès, -1 sinon
*/
int client_init(char* machine, char* port);

/*
** Initialise le socket serveur
** Retourne 0 si succès, -1 sinon
*/
int serveur_init(char* port);

/*
** Attends qu'un client se connecte sur le serveur
** Retourne 0 si fin normale, -1 si erreur
*/
int serveur_attente_client();

/*
** Recoit un message envoyé par le client
** Retourne un pointeur vers l'emplacement du message
*/
char *serveur_reception();

/*
** Recoit un message envoyé par le client
** Retourne un pointeur vers l'emplacement du message
*/
char *client_reception();

/* 
** Envoie un message au serveur.
** Attention, le message doit etre termine par "_$"
** Retourne le nombre de caractères émis ou -1 si erreur.
*/
int client_emission(char *message);

/* 
** Envoie un message au client.
** Attention, le message doit etre termine par "_$"
** Retourne le nombre de caractères émis ou -1 si erreur.
*/
int serveur_emission(char *message);

/*
** Ferme la connexion avec le serveur (coté client)
*/
void client_terminaison();

/*
** Ferme la connexion avec le client (coté serveur)
*/
void serveur_terminaison();

/*
** Arrete d'écouter pour des connexions entrantes (coté serveur)
*/
void serveur_arreter_ecoute();

#endif