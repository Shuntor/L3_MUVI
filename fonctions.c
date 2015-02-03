#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctions.h"


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

// int insertionCompteFichier(UserAccount* account){ //Fonction incomplète
//     FILE* f;
//     if((f=fopen(ACCOUNT_FILE ,"ab"))==NULL)
//         return(-1); //Erreur d'ouverture
//     fwrite(account,sizeof(UserAccount),1,f);
//     fclose(f);
//     return TRUE;
// }

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

// int LectureCompteFichier (UserAccount *user) //Fonction ncomplète
// {
//     FILE* f;
//     if((f=fopen(ACCOUNT_FILE,"rb"))==NULL)
//         return(-1); //Erreur d'ouverture
//     fread(&user,sizeof(UserAccount),1,f);
//     fclose(f);
//     return TRUE;
// }



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

    videBuffer();
    printf("Entrez le nom de l'objet :\n");
    fgets(item->nom,ITEM_NAME_LENGTH,stdin);
    if(strlen(item->nom) < ITEM_NAME_LENGTH-1)
        item->nom[strlen(item->nom)-1] = '\0';
    system("clear");

    printf("Entrez le prix de départ :\n");
    scanf("%d",&item->prixDepart);
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
}

void EnregDansFichierObjet (Item* item, UserAccount* account)
{
    FILE *sortie; 
    sortie=fopen(ITEM_FILE,"at");
    if (sortie == NULL)
    {
        printf("Un probleme est survenue lors de la tentative d'enregistrement de votre objet dans le fichier\n");
    }
    else
    {
        fprintf(sortie,"%lu \n %s \n %d \n %s \n %s \n", account->id, item->nom, item->prixDepart, item->description, item->lieu);
    } 
    fclose(sortie);
}

void nouvelObjet(UserAccount* account){
    
    Item item;

    saisieObjet(&item);
    EnregDansFichierObjet (&item, account);
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
     while ((trouve!=0) && fscanf(sortie,"%lu\n%s\n%d\n%[^\n]\n%s",&item->id, item->nom, &item->prixDepart, item->description, item->lieu)>0  ) // tant que la fin du fichier n'est pas atteinte
     {
        trouve=(strcmp(nomObjet, item->nom));
     } // fin du while
     fclose(sortie);

    if (!trouve){
        printf("Cet objet existe bien !\n");
        printf("Voici ses informations :\nnom : %s\nprix : %d\ndescripton : %s\nlieu : %s\n", item->nom, item->prixDepart, item->description, item->lieu );
    }else
        printf("Malheureusement cet objet n'exste pas :-(\n");
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
    while (fscanf(sortie,"%lu\n%s\n%d\n%[^\n]\n%s",&item.id, item.nom, &item.prixDepart, item.description, item.lieu)>0  ) // tant que la fin du fichier n'est pas atteinte
    {
       printf("Nom : %s\nPrix de depart : %d\nDescription : %s\nlieu :%s\n",item.nom, item.prixDepart, item.description, item.lieu);
       printf("================================\n");
    } // fin du while

    printf("\n\n\nAppuyez sur une touche pour continuer ...\n");getchar();
    fclose(sortie);

    return 0;
}


