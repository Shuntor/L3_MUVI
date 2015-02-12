#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fonctions.h"
#include "client.h"
// #include "serveur.h"

/* videBuffer.
*/
void videBuffer()
{
    char buff = fgetc(stdin);
    while(buff != '\n' && buff != EOF)
    {
        buff = fgetc(stdin);
    }
    // int c = 0;
    // while ((c = getchar()) != '\n' && c != EOF);
}


/* saisieChar
 */
char saisieChar()
{
    char temp = fgetc(stdin);
    while(temp == '\n' || temp == EOF)
    {
        temp = fgetc(stdin);
    }

    return temp;
}

/* verifMail.
*/
int verifMail(char *mail, int taille)
{
    if(mail == NULL)
    {
        fprintf(stderr,"null pointer");
        exit(1);
    }
    int i = 0;
    int arobase = 0 ;
    int dot = 0 ;
    // test '@'
    for(i=0;i<taille;i++){
        if((mail[i] == '@'))
            arobase ++;
        if((mail[i] == '.'))
            dot++;
    }

    return (arobase == 1 && dot == 1)? TRUE : FALSE;
}

void saisieUtilisateur(UserAccount * account)
{
    system("clear");
    int isValide = FALSE;

    do
    {
        // Choix du type de compte
        printf("\t\t\tVeuillez choisir votre type de compte : \n\n");
        printf("1 : Administrateur (Reservé aux utilisateurs aguérris !\n");
        printf("2 : Vendeur (Vous souhaitez vendre quelque chose ? C'est ici !) \n" );
        printf("3 : Acheteur (Sans plus attendre venez acheter l'objet de vos rêves !)\n");
        account->type = (saisieChar()- '0');
        system("clear");
        printf("%d\n", account->type );
        switch(account->type) //Control pour vérifier le choix de l'utilisateur
        {
            case ACCOUNT_TYPE_ADMIN:
                isValide = TRUE;
                break;
            case ACCOUNT_TYPE_VENDOR:
                isValide = TRUE;
                break;
            case ACCOUNT_TYPE_USER:
                isValide = TRUE;
                break;
            default:
                isValide = FALSE;
                printf("Erreur de saisie, veuillez réessayer...\n");
                break;
        }
    }while(!isValide);

    //Identifiant
    account->id=time(NULL);

    system("clear");

    videBuffer();
    printf("Entrez votre prénom :\n");
    fgets(account->firstname,USERACCOUNT_FIRSTNAME_LENGTH,stdin);
    if(strlen(account->firstname) < USERACCOUNT_FIRSTNAME_LENGTH-1)
        account->firstname[strlen(account->firstname)-1] = '\0';
    system("clear");

    printf("Entrez votre nom de famille :\n");
    fgets(account->lastname,USERACCOUNT_LASTNAME_LENGTH,stdin);
    if(strlen(account->lastname) < USERACCOUNT_LASTNAME_LENGTH-1)
        account->lastname[strlen(account->lastname)-1] = '\0';
    // videBuffer();
    system("clear");

    printf("Entrez votre adresse :\n");
    fgets(account->adress,USERACCOUNT_ADRESS_LENGTH,stdin);
    if(strlen(account->adress) < USERACCOUNT_LASTNAME_LENGTH-1)
        account->adress[strlen(account->adress)-1] = '\0';
    // videBuffer();
    system("clear");

    do
    {
        printf("Entrez votre adresse e-mail :\n");
        fgets(account->mail,USERACCOUNT_MAIL_LENGTH,stdin);
        if(strlen(account->mail) < USERACCOUNT_MAIL_LENGTH-1)
            account->mail[strlen(account->mail)-1] = '\0';
        // videBuffer();
    }while(!verifMail(account->mail,strlen(account->mail)));
    system("clear");
}


void EnregDansFichier (UserAccount* account)
{
     FILE *sortie;
  
       sortie=fopen(ACCOUNT_FILE,"at");
 
       if (sortie == NULL)
       {
            printf("Un probleme est survenue lors de la tentative d'enregistrement de vos donnees dans le fichier\n");
       }
       else
       {
            fprintf(sortie,"%lu \n %d \n %s \n %s \n %s \n %s \n", account->id, account->type, account->firstname, account->lastname, account->adress, account->mail);
       } 

       fclose(sortie);
}

int RechercheCpte (UserAccount* account, char* nomClient) //Marche bien maintenant
{
     int trouve=-1;
     FILE *sortie;
      // printf("nomCLient : %s account : %s\n", nomClient, account->lastname );
     
     sortie=fopen(ACCOUNT_FILE, "rt");
     while ((trouve!=0) && fscanf(sortie,"%lu\n%d\n%s\n%s\n%s\n%s", &account->id, &account->type, account->firstname, account->lastname, account->adress, account->mail) ) // tant que la fin du fichier n'est pas atteinte
     {
        // printf("%lu\n%d\n%s\n%s\n%s\n%s\n", account->id, account->type, account->firstname, account->lastname, account->adress, account->mail);
         if (nomClient ) // Si un nom de client a ete saisi
         {
            trouve=(strcmp(nomClient, account->lastname));
            // printf("trouve : %d account->lasname : %s nomClient : %s\n", trouve, account->lastname, nomClient); getchar();
         }
     } // fin du while
    return (trouve==0)? TRUE : FALSE;
}


void nouvelUtilisateur(){
    UserAccount newAccount;
    saisieUtilisateur(&newAccount);

    EnregDansFichier(&newAccount);

    printf("\t\tNouveau compte créé :\n\n"); 
    printf("-Prénom : %s\n", newAccount.firstname ); //ATTENTION il y a déjà un \n dans la varable lu
    printf("-Nom : %s\n", newAccount.lastname );
    printf("-Adresse : %s\n", newAccount.adress );
    printf("-Mail : %s\n", newAccount.mail );
    printf("\nAppuyez sur une touche pour continuer...\n");
    getchar();
    
}

void saisieObjet(Item* item)
{
    system("clear");

    item->id=time(NULL);

    videBuffer();
    printf("Entrez le nom de l'objet :\n");
    fgets(item->nom,ITEM_NAME_LENGTH,stdin);
    if(strlen(item->nom) < ITEM_NAME_LENGTH-1)
        item->nom[strlen(item->nom)-1] = '\0';
    system("clear");

    printf("Entrez le prix de départ :\n");
    scanf("%d",&item->prix);
    videBuffer();
    system("clear");

    printf("Entrez la description :\n");
    fgets(item->description,ITEM_DESCRIPTION_LENGTH,stdin);
    if(strlen(item->description) < ITEM_DESCRIPTION_LENGTH-1)
        item->description[strlen(item->description)-1] = '\0';
    // videBuffer();
    system("clear");

    printf("Entrez le lieu ou est stocké l'objet :\n");
    fgets(item->lieu,ITEM_LOCATION_LENGTH,stdin);
    if(strlen(item->lieu) < ITEM_LOCATION_LENGTH-1)
        item->lieu[strlen(item->lieu)-1] = '\0';
    // videBuffer();
    system("clear");

    printf("Entrez le nombre de jours pendant lesquels l'objet sera en enchère :\n");
    scanf("%u",&item->fermetureEnchere);
    item->fermetureEnchere=calculFinEnchere(item->fermetureEnchere); 
    videBuffer();
    system("clear");

}

void EnregDansFichierObjet (Item* item)
{
    FILE *sortie; 
    sortie=fopen(ITEM_FILE,"at");
    if (sortie == NULL)
    {
        printf("Un probleme est survenue lors de la tentative d'enregistrement de votre objet dans le fichier\n");
    }
    else
    {
        fprintf(sortie,"%lu \n %lu \n %s \n %d \n %s \n %s \n %u \n", item->id, item->idVendeur, item->nom, item->prix, item->description, item->lieu, item->fermetureEnchere);
    } 
    fclose(sortie);
}

void nouvelObjet(UserAccount* account){
    
/*    long long id; */
    srand(time(NULL));

/*    id = rand();
    id = id | ((uint64_t)time(NULL) << 16);*/


    Item item;

    saisieObjet(&item);

    item.idVendeur = account->id;

    EnregDansFichierObjet (&item);
}

int rechercheObjet (Item* item) 
{
     int trouve=-1;
     FILE *sortie;
     char nomObjet[ITEM_NAME_LENGTH];
     videBuffer();
     printf("Veuillez saisir le nom de l'objet recherché : \n");
     fgets(nomObjet,ITEM_NAME_LENGTH,stdin);
    if(strlen(nomObjet) < ITEM_NAME_LENGTH-1)
        nomObjet[strlen(nomObjet)-1] = '\0';;
    system("clear");

     sortie=fopen(ITEM_FILE, "rt");
     while ((trouve!=0) && fscanf(sortie,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item->id,&item->idVendeur, item->nom, &item->prix, item->description, item->lieu, &(item->fermetureEnchere))>0  ) // tant que la fin du fichier n'est pas atteinte
     {
        trouve=(strcmp(nomObjet, item->nom));
     } // fin du while
     fclose(sortie);

    if (!trouve){
        printf("Cet objet existe bien !\n");
        printf("Voici ses informations :\nnom : %s\nprix : %d\ndescripton : %s\nlieu : %s\n", item->nom, item->prix, item->description, item->lieu );
        afficherDate(item->fermetureEnchere); 
    }else
        printf("Malheureusement cet objet n'existe pas :-(\n");
    printf("\n\n\nAppuyez sur une touche pour continuer ...\n");getchar();

    return 0;
}

int connexion(UserAccount* account)
{
    char lastname[USERACCOUNT_LASTNAME_LENGTH];
    videBuffer();
    printf("Veuillez saisir votre nom :\n");
    fgets(lastname,USERACCOUNT_LASTNAME_LENGTH,stdin);
    if(strlen(lastname) < USERACCOUNT_LASTNAME_LENGTH-1)
        lastname[strlen(lastname)-1] = '\0';;
    system("clear");
    return (RechercheCpte(account, lastname)) ;
}

int listeObjet()
{
    FILE *sortie;
    Item item;
    videBuffer();
    system("clear");
    sortie=fopen(ITEM_FILE, "rt");
    printf("========LISTE DES OBJETS======== \n\n");
    while (fscanf(sortie,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id,&item.idVendeur, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere)>0  ) // tant que la fin du fichier n'est pas atteinte
    {
       printf("Nom : %s\nPrix : %d\nDescription : %s\nlieu :%s\n",item.nom, item.prix, item.description, item.lieu);
       afficherDate(item.fermetureEnchere);
       printf("================================\n");
    } // fin du while

    printf("\n\n\nAppuyez sur une touche pour continuer ...\n");getchar();
    fclose(sortie);
    return 0;
}

unsigned calculFinEnchere(int nbrjour){
    // printf("timestamp : %u \n timefinEnchere : %u\n",(unsigned)time(NULL), (unsigned)(time(NULL)+(nbrjour*86400)));
    // getchar();getchar();
    return ((time_t)time(NULL)+(nbrjour*86400));
}

void afficherDate(time_t finEnchere){
    struct tm * dt;
    char b[15];
    dt = localtime(&finEnchere);
    strftime(b, sizeof(b), "%m-%d-%H-%M-%y", dt);
    printf("Date fin enchere (Mois-Jour-Heure-minute-seconde): %s\n", b);
}

int isDateOut(unsigned date){
    time_t ts=(time_t)time(NULL); //timestamp
    return (ts>date)? TRUE : FALSE ; 
}

void seeSelfItem(UserAccount* account){
    FILE *sortie;
    Item item;
    Item vendu[10];
    int i=0;
    videBuffer();
    system("clear");
    sortie=fopen(ITEM_FILE, "rt");
    printf("========LISTE DE VOS OBJETS ENCORE EN VENTE======== \n\n");
    while (fscanf(sortie,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id,&item.idVendeur, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere)>0  ) // tant que la fin du fichier n'est pas atteinte
    {
        if (!isDateOut(item.fermetureEnchere)) 
        {
            printf("Nom : %s\nPrix : %d\nDescription : %s\nlieu :%s\n",item.nom, item.prix, item.description, item.lieu);
            afficherDate(item.fermetureEnchere);
            printf("================================\n");
        }else
        { //On stocks les objets vendus 
            i++;
            vendu[i]=item;
        }
    } // fin du while

    while(i>=1){
        printf("\n\n!!!!!\t FELICITATION !  %s vendu au prix de %d €\t!!!!\n", vendu[i].nom, vendu[i].prix );
        i--;
    }

    // nettoyerFichierObjet(account->id);

    printf("\n\n\nAppuyez sur une touche pour continuer ...\n");getchar();
    fclose(sortie);
}

void nettoyerFichierObjet(long int idVendeur){ //Pas fini
    FILE *sortie;
    Item item;
    videBuffer();
    sortie=fopen(ITEM_FILE, "rt");
    while (fscanf(sortie,"%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere)>0  ) // tant que la fin du fichier n'est pas atteinte
    {
        if (isDateOut(item.fermetureEnchere) && item.idVendeur == idVendeur)
        {
            // supprimerObjet(item.id);
        }
    }
    fclose(sortie);
}

int encherir(long int idObjet, long int idacheteur, int prix){
    FILE *sortie;
    Item item;
    File f;
    int i=0,cond;
    Item* deb;

    sortie=fopen(ITEM_FILE, "rt+");
 
    while(fscanf(sortie,"%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere) > 0); // tant que la fin du fichier n'est pas atteinte
    {
        if (i=0)
        {
            f.item=item;
            deb=&f.item;

        }else
        {
            f.suivant = (Item)malloc(sizeof(Item));
            f.suivant = item;
        }

        tabItem[i]=item;
        if (item.id==idObjet)
        {
            tabItem[i].idAcheteur=idacheteur;
            tabItem[i].prix=prix;
        }
        i++
    }
    //On supprime le contenu du fichier pour reécrire à partir du tableau et ainsi le mettre à jour
    fclose(sortie);
    sortie=fopen(ITEM_FILE, "w+");
    while()

    fclose(sortie);
}

void serialiser(Item* item, char* chaineRes)
{

     //Il faut passer la chaine dans laquelle tout est serialisé en paramètre, celle-ci doit avoir une taille max de la lg du champ données


    strcat(strcpy(chaineRes, item.id),"_") ;
    strcat(strcat(item.idVendeur , chaineRes),"_");  
    strcat(strcat(item.idAcheteur , chaineRes),"_");
    strcat(strcat(item.fermetureEnchere , chaineRes),"_");
    strcat(strcat(item.nom  , chaineRes),"_");
    strcat(strcat(item.description  , chaineRes),"_");
    strcat(strcat(item.prix , chaineRes),"_");
    strcat(strcat(item.lieu , chaineRes),"_");

}

// void supprimerObjet(long int id){
//     int pos=0; 
//     int trouve=0; 
//     fichier=fopen(ITEM_FILE, "r+");

// // rewind(fichier); //On se place au début du fichier 
// // }


void test(){
    // char *message;
   

    
}
/*
    Transformations jours en secondes :
    timestamp + (nbr jours * 86400)
    dt = localtime(&ts);
     // use any strftime format spec here
     strftime(b, sizeof(b), "%m%d%H%M%y", dt);
     fprintf(stdout, "%s", b);

*/


