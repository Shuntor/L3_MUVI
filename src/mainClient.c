#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"
#include "interfaceClient.h"
#include "client.h"
#include "transport.h"


/********A faire********\
 *
 * - SUPPRESSION D'UN OBJET a faire imperativement ou pas
 * - Voir vos objets en vente (rajouter l'id du vendeur)
 * - ENcherir
 * - 
*/

/********Déjà fait********\
 *
 * - Connexion
 * - Recherche d'un compte à partir du nom
 * - Creation d'un compte
 * - Creation d'un objet 
 * - Recherche d'objet
 * - listeObjet
*/


int main(void)
{
	//Declaration des variables
	int choix; //Stock le choix de l'utilisateur
	// int test;
	UserAccount account;
	Item item;


	if (client_init(SERVER_ADDRESS, SERVER_PORT) != 0)
	{
		fprintf(stderr, "Connexion au serveur impossible !\n");
		fprintf(stderr, "Etes-vous sur que celui-ci est démarré correctement ?\n");
		exit(1);
	}


	while( (choix = menuAccueil()) != MENU_CHOICE_QUIT ){
		switch(choix){
			case MENU_CHOICE_MAIN_ANONYMOUS:
				while((choix = menuPrincipalAnonyme()) != MENU_CHOICE_QUIT){
				    switch(choix)
				    {
				        case MENU_CHOICE_ITEM_LIST:
				            //Liste d'objets
				        	listeObjet();
				            break;
				        case MENU_CHOICE_MAIN_SEARCH:
				            //Recherche d'un objet
				        	rechercheObjet(&item);
				            break;
				        case MENU_CHOICE_QUIT:
				            //On quitte
				            break;
				        default:
				            printf("\n\t\t Votre choix est invalide ...\n\n");
				            break;
				    }
				}
				system("clear");
			break;
			case MENU_CHOICE_MAIN_ACCOUNT_CREATION:
				client_nouvelUtilisateur();
			break;
			case MENU_CHOICE_MAIN_CONNECTION:
				if ((connexion(&account)) && (account.type > 0 )){
					switch(account.type)
					{
						case ACCOUNT_TYPE_ADMIN: //==1
							while((choix = menuPrincipalAdmin()) != MENU_CHOICE_QUIT){
							    switch(choix)
							    {
							        case MENU_CHOICE_ITEM_LIST:
							            //Liste d'objets
							        	listeObjet();
							            break;
							        case MENU_CHOICE_MAIN_SEARCH:
							            //Recherche d'un objet							        	
							        	rechercheObjet(&item);
							            break;
							        case MENU_CHOICE_QUIT:
							            //On quitte
							            break;
							        default:
							            printf("\n\t\t Votre choix est invalide ...\n\n");
							            break;
							    }
							}
						break;
						case ACCOUNT_TYPE_VENDOR: //==2
							while((choix = menuPrincipalVendeur()) != MENU_CHOICE_QUIT){
							    switch(choix)
							    {
							        case MENU_CHOICE_SELL:
							            //Liste d'objets
							        		nouvelObjet(&account);
							            break;
							        case MENU_CHOICE_ALREADY_SELL:
							        		seeSelfItem(&account);
							            break;
							        case MENU_CHOICE_QUIT:
							            //On quitte
							            break;
							        default:
							            printf("\n\t\t Votre choix est invalide ...\n\n");
							            break;
							    }
							}
						break;
						case ACCOUNT_TYPE_USER: //==3
							while((choix = menuPrincipalAcheteur()) != MENU_CHOICE_QUIT){
							    switch(choix)
							    {
							        case MENU_CHOICE_ITEM_LIST:
							            //Liste d'objets
							        	listeObjet();
							            break;
							        case MENU_CHOICE_MAIN_SEARCH:
							            //Recherche d'un objet							        
							        	rechercheObjet(&item);
							            break;
							        case MENU_CHOICE_MAIN_ENCHERIR:
							            //Encherir							        
							        	if (!encherir(account.id))
							        		printf("L'objet n'existe pas...\n");getchar();
							            break;
							        case MENU_CHOICE_QUIT:
							            //On quitte
							            break;
							        default:
							            printf("\n\t\t Votre choix est invalide ...\n\n");
							            break;
							    }
							}
						break;
					}
				}
				else{
					printf("Nom de compte incorrect...\nAppuyez sur une touche pour continuer...\n");
					getchar();
				}
			break;
			case 9:
				test();
				break;
			default:
			    printf("\n\t\t Votre choix est invalide ...\n\n");
			break;
		}
	}
	client_terminaison();

	system("clear");
    printf("\n\t\tMUVI vous souhaite une bonne journée et espère vous revoir très bientôt !\n\n");

    // videBuffer();
    fgetc(stdin); // équivaut à une pause

    return 0;
}