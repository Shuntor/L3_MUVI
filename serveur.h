#ifndef __SERVEUR_H__
#define __SERVEUR_H__


/* Initialisation.
 * 
 */
int Initialisation(char *port);


/* connectait.
 *
 */
int AttenteClient();


/* Recoit un message envoye par le client.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();


/* Envoie un message au client.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int Emission(char *message);


/* Recoit des donnees envoyees par le client.
 * renvoie le nombre d'octets reus, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);


/* Envoie des donnes au client en prcisant leur taille.
 * renvoie le nombre d'octets envoys, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);


/* Ferme la connexion avec le client.
 */
void TerminaisonClient();


/* Arrete le serveur.
 */
void Terminaison();


/*
 * D : Calcul la longueur d'un fichier
 * R : -1 si le fchier est inconnu, 0 si il est vide, sinon la longueur du fichier
*/
size_t file_length(char *filename);



/*
 *
*/
int sendStatusLine(int statusCode);


/*
 *
*/
int sendHeaderField();


/*
int envoyerContenuFichierTexte(char *nomFichier);
int envoyerContenuFichierBinaire(char *nomFichier);
int testExtension(char *nomFichier, char *extension);
*/


#endif