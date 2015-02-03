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
		int enchereMax ; 
		long int ouvertureEnchere ;
		long int fermetureEnchere ;
 		//char* Categorie ;
	 	char nom[ITEM_NAME_LENGTH] ;
	 	char description[ITEM_DESCRIPTION_LENGTH] ;  
	 	int prixDepart ;
	 	//int quantite ;
	 	char lieu[ITEM_LOCATION_LENGTH];
	}Item;



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

	/*
	 *
	 *
	*/
	 int verifMail(char *mail, int taille);

	/*
	 *
	 *
	*/
	void saisieUtilisateur(UserAccount * account);


	/*
	 *
	 *
	*/
	int insertionCompteFichier(UserAccount *account);
	void EnregDansFichier (UserAccount* account);
	
	/*
	 *
	 * R : 
	*/
	int RechercheCpte ( UserAccount* account, char* nomClient );
	int LectureCompteFichier (UserAccount *user);

	/*
	 *
	 *
	*/
	void nouvelUtilisateur();

	void saisieObjet(Item* item);
	void EnregDansFichierObjet (Item* item, UserAccount* account);
	void nouvelObjet(UserAccount* account);
	int rechercheObjet(Item* item);
	int connexion(UserAccount* account);
	int listeObjet();




#endif