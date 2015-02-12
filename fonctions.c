#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fonctions.h"
#include "transport.h"
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
     int trouve=1;
     FILE *sortie;
     
     sortie=fopen(ACCOUNT_FILE, "rt");
     while ((trouve!=0) && fscanf(sortie,"%lu\n%d\n%s\n%s\n%[^\n]\n%s", &account->id, &account->type, account->firstname, account->lastname, account->adress, account->mail)>0 ) // tant que la fin du fichier n'est pas atteinte
     {
        printf("%lu\n%d\n%s\n%s\n%s\n%s\n", account->id, account->type, account->firstname, account->lastname, account->adress, account->mail);
         // printf("nomCLient : %s account : %s\n", nomClient, account->lastname );
         if (nomClient ) // Si un nom de client a ete saisi
         {
            trouve=(strcmp(nomClient, account->lastname));
            // printf("trouve : %d account->lasname : %s nomClient : %s\n", trouve, account->lastname, nomClient); getchar();
         }
     } // fin du while
    fclose(sortie);
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
    printf("\n\n\nAppuyez sur une touche pour continuer...\n");
    getchar();
    
}

void client_nouvelUtilisateur()
{
    char* reponse;
    char buffer[4096];
    UserAccount newAccount;
    saisieUtilisateur(&newAccount);

    sprintf(buffer, "ANC %s_$", serialiser_account(&newAccount));

    client_emission(buffer);
    reponse = client_reception();
    if (strcmp(reponse, "107 _$") == 0)
    {
        printf("\t\tNouveau compte créé :\n\n"); 
        printf("-Prénom : %s\n", newAccount.firstname ); //ATTENTION il y a déjà un \n dans la varable lu
        printf("-Nom : %s\n", newAccount.lastname );
        printf("-Adresse : %s\n", newAccount.adress );
        printf("-Mail : %s\n", newAccount.mail );
        printf("\nAppuyez sur une touche pour continuer...\n");
        getchar();
    }
    else
    {
        fprintf(stderr, "%s\n", "207 ERROR: Erreur de création du nouvel utilisateur");
    }
}

int serveur_nouvelUtilisateur(char* mess)
{
    char *s = strdup(mess + 4*(sizeof(char)));
    s[strlen(s)-1] = '\0';
    s[strlen(s)-2] = '\0';
    EnregDansFichier(deserialiser_account(s));
    serveur_emission("107 _$");
    free(s);
    return 0;
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
    videBuffer();

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
        if (item.idVendeur == account->id)
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
        }
    } // fin du while

    while(i>=1){
        printf("\n\n!!!!!\t FELICITATION !  %s vendu au prix de %d €\t!!!!\n", vendu[i].nom, vendu[i].prix );
        i--;
    }

    // nettoyerFichierObjet(account->id);
    // nettoyerFichierObjet(account->id); //On supprime les objets qu'il a vendu du fichier
    printf("\n\n\nAppuyez sur une touche pour continuer ...\n");getchar();
    fclose(sortie);
}

void nettoyerFichierObjet(long int idVendeur){ //Pas fini
    FILE *sortie;
    Item item;
    Item tabItem[20];
    int i=0, trouve=0;
    sortie=fopen(ITEM_FILE, "rt"); 
    while(fscanf(sortie,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id,&item.idVendeur, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere) > 0); // tant que la fin du fichier n'est pas atteinte
    {
        tabItem[i]=item;
        if (item.idVendeur==idVendeur && isDateOut(item.fermetureEnchere))
        {
            trouve=1;
            i--; 
        }
        i++;
    }
    i--;
    fclose(sortie);
    if (trouve)
    {
        //On supprime le contenu du fichier pour reécrire à partir du tableau et ainsi le mettre à jour
        sortie=fopen(ITEM_FILE, "w+");
        while(i>=0){
            fprintf(sortie,"%lu \n %lu \n %s \n %d \n %s \n %s \n %u \n", tabItem[i].id, tabItem[i].idVendeur, tabItem[i].nom, tabItem[i].prix, tabItem[i].description, tabItem[i].lieu, tabItem[i].fermetureEnchere);
            i--;
        }    
        fclose(sortie);
    }
}

int encherir(long int idacheteur){
    FILE *fic;
    Item item;
    Item tabItem[20];
    int i=0, prix, trouve=0;
    char nomItem[ITEM_NAME_LENGTH];

    system("clear");
    printf("Entrez le nom de l'objet sur lequel vous souhaitez encherir :\n");
    videBuffer();
    fgets(nomItem,ITEM_NAME_LENGTH,stdin);
    if(strlen(nomItem) < ITEM_NAME_LENGTH-1)
        nomItem[strlen(nomItem)-1] = '\0';
    printf("\t\tDe combien voulez-vous encherir ?\n");
    scanf("%d",&prix);
    videBuffer();

    fic=fopen(ITEM_FILE, "rt"); 
    printf("test 1\n");
    // fseek(fic,0,SEEK_SET);
    // fscanf(fic,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id,&item.idVendeur, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere);printf("%s\n",item.nom );getchar();
    while(fscanf(fic,"%lu\n%lu\n%s\n%d\n%[^\n]\n%s\n%u",&item.id,&item.idVendeur, item.nom, &item.prix, item.description, item.lieu, &item.fermetureEnchere)>0 ) // tant que la fin du fichier n'est pas atteinte
    {
        tabItem[i]=item;
        printf("%s      %s \n", item.nom,nomItem);
        if (strcmp(item.nom,nomItem)==0)
        {
            trouve=1;
            tabItem[i].idAcheteur=idacheteur;
            tabItem[i].prix+=prix;
        }
        i++;
    }
    i--;
    fclose(fic);
    printf("test 2\n");
    if (trouve)
    {
        //On supprime le contenu du fichier pour reécrire à partir du tableau et ainsi le mettre à jour
        fic=fopen(ITEM_FILE, "w+");
        while(i>=0){
            fprintf(fic,"%lu \n %lu \n %s \n %d \n %s \n %s \n %u \n", tabItem[i].id, tabItem[i].idVendeur, tabItem[i].nom, tabItem[i].prix, tabItem[i].description, tabItem[i].lieu, tabItem[i].fermetureEnchere);
            i--;
        }    
        fclose(fic);
    }
    return trouve;
}

char *serialiser_item(Item* i)
{
    char buffer[4096];

    sprintf(buffer, "%ld_%ld_%ld_%u_%s_%s_%d_%s",
      i->id, i->idVendeur, i->idAcheteur, i->fermetureEnchere, i->nom, i->description,
      i->prix, i->lieu);

    strdup(buffer);

}

Item *deserialiser_item(char* s)
{
    Item *d = malloc(sizeof(Item));
    int ci = 0, cb = 0;
    int i;
    char buff[1024];

    for (i=0;i<8;i++)
    {
        while (s[ci] != '_')
        {
            buff[cb] = s[ci];
            ci++;
            cb++;
        }
        ci++;
        buff[cb] = '\0';
        cb = 0;
        if (i == 0)
            d->id = atoi(buff);
        else if (i == 1)
            d->idVendeur = atoi(buff);
        else if (i == 2)
            d->idAcheteur = atoi(buff);
        else if (i == 3)
            d->fermetureEnchere = atoi(buff);
        else if (i == 4)
        {
            strncpy(d->nom, buff, ITEM_NAME_LENGTH);
            (d->nom)[ITEM_NAME_LENGTH-1] = '\0';
        }
        else if (i == 5)
        {
            strncpy(d->description, buff, ITEM_DESCRIPTION_LENGTH);
            (d->description)[ITEM_DESCRIPTION_LENGTH-1] = '\0';
        }
        else if (i == 6)
            d->prix = atoi(buff);
        else if (i == 7)
        {
            strncpy(d->lieu, buff, ITEM_LOCATION_LENGTH);
            (d->lieu)[ITEM_LOCATION_LENGTH-1] = '\0';
        }
    }

    return d;

}

char *serialiser_account(UserAccount* a)
{
    char buffer[4096];

    sprintf(buffer, "%ld_%d_%s_%s_%s_%s",
      a->id, a->type, a->firstname, a->lastname, a->adress, a->mail);

    strdup(buffer);

}

UserAccount *deserialiser_account(char* s)
{
    UserAccount *d = malloc(sizeof(UserAccount));
    int ci = 0, cb = 0;
    int i;
    char buff[1024];

    for (i=0;i<6;i++)
    {
        while (s[ci] != '_')
        {
            buff[cb] = s[ci];
            ci++;
            cb++;
        }
        ci++;
        buff[cb] = '\0';
        cb = 0;
        if (i == 0)
            d->id = atoi(buff);
        else if (i == 1)
            d->type = atoi(buff);
        else if (i == 2)
        {
            strncpy(d->firstname, buff, USERACCOUNT_FIRSTNAME_LENGTH);
            (d->firstname)[USERACCOUNT_FIRSTNAME_LENGTH-1] = '\0';
        }
        else if (i == 3)
        {
            strncpy(d->lastname, buff, USERACCOUNT_LASTNAME_LENGTH);
            (d->lastname)[USERACCOUNT_LASTNAME_LENGTH-1] = '\0';
        }
        else if (i == 4)
        {
            strncpy(d->adress, buff, USERACCOUNT_ADRESS_LENGTH);
            (d->adress)[USERACCOUNT_ADRESS_LENGTH-1] = '\0';
        }
        else if (i == 5)
        {
            strncpy(d->mail, buff, USERACCOUNT_MAIL_LENGTH);
            (d->mail)[USERACCOUNT_MAIL_LENGTH-1] = '\0';
        }
    }

    return d;

}



// void supprimerObjet(long int id){
//     int pos=0; 
//     int trouve=0; 
//     fichier=fopen(ITEM_FILE, "r+");

// // rewind(fichier); //On se place au début du fichier 
// // }


void test(){
    FILE *sortie;
       sortie=fopen(ITEM_FILE,"at"); 
       if (sortie == NULL)
       {
            printf("Un probleme est survenue lors de la tentative d'enregistrement de vos donnees dans le fichier\n");
       }
       else
       {
            fprintf(sortie,"lala");
       } 
       fclose(sortie);
    
}
/*
    Transformations jours en secondes :
    timestamp + (nbr jours * 86400)
    dt = localtime(&ts);
     // use any strftime format spec here
     strftime(b, sizeof(b), "%m%d%H%M%y", dt);
     fprintf(stdout, "%s", b);

*/


