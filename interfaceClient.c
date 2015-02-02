#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
#include "fonctions.h"




/* menuAccueil
 */
int menuAccueil()
{
    system("clear");
    fprintf(stdout, "\n\t\t\t\tBIENVENUE SUR MUVI\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Poursuivre anonymement\n", MENU_CHOICE_MAIN_ANONYMOUS);
    fprintf(stdout, "\t\t\t\t%d - Creation de compte\n", MENU_CHOICE_MAIN_ACCOUNT_CREATION);
    fprintf(stdout, "\t\t\t\t%d - Connexion\n", MENU_CHOICE_MAIN_CONNECTION);
    fprintf(stdout, "\t\t\t\t%d - Quitter\n", MENU_CHOICE_QUIT);
//    videBuffer();
    return saisieChar() - '0';
}


/* menuPrincipalAnonyme
 */
int menuPrincipalAnonyme()
{
    system("clear");
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR MUVI - Anonyme\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Liste d'objets\n", MENU_CHOICE_ITEM_LIST);
    fprintf(stdout, "\t\t\t\t%d - Recherche d'objet(s) par mot clef\n", MENU_CHOICE_MAIN_SEARCH);
    fprintf(stdout, "\t\t\t\t%d - Retour\n", MENU_CHOICE_QUIT);
//    videBuffer();
    return saisieChar() - '0';
}

/* menuPrincipal
 */
int menuPrincipalAdmin()
{
    system("clear");
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR MUVI - Admin\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Liste d'objets\n", MENU_CHOICE_ITEM_LIST);
    fprintf(stdout, "\t\t\t\t%d - Recherche d'objet(s) par mot clef\n", MENU_CHOICE_MAIN_SEARCH);
    fprintf(stdout, "\t\t\t\t%d - Retour\n", MENU_CHOICE_QUIT);
//    videBuffer();
    return saisieChar() - '0';
}

int menuPrincipalVendeur()
{
    system("clear");
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR MUVI - Vendeur\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Vendre un objet\n", MENU_CHOICE_SELL);
    fprintf(stdout, "\t\t\t\t%d - Voir vos objets en vente\n", MENU_CHOICE_ALREADY_SELL);
    fprintf(stdout, "\t\t\t\t%d - Retour\n", MENU_CHOICE_QUIT);
//    videBuffer();
    return saisieChar() - '0';
}

int menuPrincipalAcheteur()
{
    system("clear");
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR MUVI - Acheteur\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Liste d'objets\n", MENU_CHOICE_ITEM_LIST);
    fprintf(stdout, "\t\t\t\t%d - Recherche d'objet(s) par mot clef\n", MENU_CHOICE_MAIN_SEARCH);
    fprintf(stdout, "\t\t\t\t%d - Retour\n", MENU_CHOICE_QUIT);
//    videBuffer();
    return saisieChar() - '0';
}