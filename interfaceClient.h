#ifndef __INTERFACECLIENT_H__
#define __INTERFACECLIENT_H__


// valeurs des choix dans les menus
// commun
#define MENU_CHOICE_QUIT 0
// Menu d'accueil
#define MENU_CHOICE_MAIN_CONNECTION 1
#define MENU_CHOICE_MAIN_ACCOUNT_CREATION 2
#define MENU_CHOICE_MAIN_ANONYMOUS 3
// Menus d'utilisateurs
#define MENU_CHOICE_ITEM_LIST 1
#define MENU_CHOICE_MAIN_SEARCH 2
//
#define MENU_CHOICE_SELL 1
#define MENU_CHOICE_ALREADY_SELL 2 


/* menuAccueil.
 * Affiche l'écran d'accueil.
 * retourne le choix de l'utilisateur.
 */
int menuAccueil();


/* menuPrincipalAnonyme.
 * Affiche le menu principal pour un anonyme.
 * retourne le choix de l'utilisateur.
 */
int menuPrincipalAnonyme();

/* menuPrincipalAnonyme.
 * Affiche le menu principal pour un anonyme.
 * retourne le choix de l'utilisateur.
 */
int menuPrincipalAdmin();

/* menuPrincipalAnonyme.
 * Affiche le menu principal pour un anonyme.
 * retourne le choix de l'utilisateur.
 */
int menuPrincipalVendeur();

/* menuPrincipalAnonyme.
 * Affiche le menu principal pour un anonyme.
 * retourne le choix de l'utilisateur.
 */
int menuPrincipalAcheteur();

#endif