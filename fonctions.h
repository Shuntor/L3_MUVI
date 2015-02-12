#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

#define TRUE 1
#define FALSE 0

//Fichiers
#define ACCOUNT_FILE "listeComptes"
#define ITEM_FILE "listeObjets"

// account types
#define ACCOUNT_TYPE_ADMIN 1
#define ACCOUNT_TYPE_VENDOR 2
#define ACCOUNT_TYPE_USER 3

// account labels
// #define ACCOUNT_LABEL_ADMIN "Admin, become a god ;) "
// #define ACCOUNT_LABEL_VENDOR "Vendor, limited to sell things"
// #define ACCOUNT_LABEL_USER "User, limited to bought things"


//Longueur des champs
//Utilisateur
#define USERACCOUNT_FIRSTNAME_LENGTH 75
#define USERACCOUNT_LASTNAME_LENGTH 64
#define USERACCOUNT_ADRESS_LENGTH 96
#define USERACCOUNT_MAIL_LENGTH 80
//Objets
#define ITEM_NAME_LENGTH 50
#define ITEM_DESCRIPTION_LENGTH 200
#define ITEM_LOCATION_LENGTH 100


	typedef struct UserAccount
	{
		long int id; //Identifiant de l'utilisateur, il est unique !
	    int type; //Type d'utilisateur {Admin,vendeur,acheteur}
	    char firstname[USERACCOUNT_FIRSTNAME_LENGTH]; //Prénom
	    char lastname[USERACCOUNT_LASTNAME_LENGTH]; //Nom de famille
	    char adress[USERACCOUNT_ADRESS_LENGTH]; // Adresse
	    char mail[USERACCOUNT_MAIL_LENGTH]; // Adresse mail
	} UserAccount;

	typedef struct Item
	{
		long int id ;
		long int idVendeur ;
		long int idAcheteur ;
		unsigned fermetureEnchere ;
 		//char* Categorie ;
	 	char nom[ITEM_NAME_LENGTH] ;
	 	char description[ITEM_DESCRIPTION_LENGTH] ;  
	 	int prix ;
	 	//int quantite ;
	 	char lieu[ITEM_LOCATION_LENGTH];
	} Item;

	typedef struct File{
		Item item ;
		Item * suivant;
	}File;


	/* N : videBuffer.
	 * D : vide le buffer
	 * R : -
	*/
	void videBuffer();

	/* N : saisieChar.
	 * D : saisie d'un caractere, elimine les '\n' et EOF
	 * R : retourne un caractere
	*/
	char saisieChar();

	/* N : verifMail
	 * D : Verifie si le mail est bien structuré, présence de l'arobase et du point
	 * R : TRUE or FALSE
	*/
	 int verifMail(char *mail, int taille);

	/* N : saisieUtilisateur
	 * D : Permet de saisir toutes les données propres à un utilisateur
	 * R : -
	*/
	void saisieUtilisateur(UserAccount * account);
	
	/* N : insertionComtpeFichier
	 * D : Insere un compte dans le fichier de comptes
	 * R : TRUE or FALSE
	*/
	void EnregDansFichier (UserAccount* account);
	
	/* N : RechercheCpte
	 * D : Permet de rechercher un compte dans le fichier de compte à l'aide du nom de l'utilisateur
	 * R : TRUE or FALSE
	*/
	int RechercheCpte ( UserAccount* account, char* nomClient );

	/* N : nouvelUtilisateur
	 * D : Créer un nouvel utilisateur
	 * R : -
	*/
	void nouvelUtilisateur();
	
	/* N : saisieObjet
	 * D : Saisir un objet
	 * R : -
	*/
	void saisieObjet(Item* item);
	
	/* N : EnregDansFichierObjet
	 * D : Enregistrer un objet dans un fichier
	 * R : -
	*/
	void EnregDansFichierObjet (Item* item);
	
	/* N : nouvelObjet
	 * D : Créer un nouvel objet
	 * R : -
	*/
	void nouvelObjet(UserAccount* account);
	
	/* N : rechercheObjet
	 * D : Rechercher un objet dans le fichier d'objets
	 * R : 0
	*/
	int rechercheObjet(Item* item);
	
	/* N : connexion
	 * D : Connexion en recherchant uniquement le nom de l'utilisateur
	 * R : TRUE or FALSE
	*/
	int connexion(UserAccount* account);
	
	/* N : listeObjet
	 * D : 
	 * R : 
	*/
	int listeObjet();

	
	/* N : 
	 * D : 
	 * R : 
	*/
	unsigned calculFinEnchere(int nbrjour);
	
	/* N : 
	 * D : 
	 * R : 
	*/
	void afficherDate(time_t finEnchere);
	
	/* N : 
	 * D : 
	 * R : 
	*/	
	void seeSelfItem(UserAccount* account);

	/* N : 
	 * D : 
	 * R : 
	*/
	void nettoyerFichierObjet(long int idVendeur);
	
	/* N : 
	 * D : 
	 * R : 
	*/
	int encherir(long int idObjet, long int idVendeur, int prix);

	/* N : 
	 * D : 
	 * R : 
	*/
	void supprimerObjet(long int id);


	/* Foncton de tests */
	void test();




#endif