#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include <conio.h>

/*---------------------------------------------------------------------------*/
/* GESTION DU TERMINAL */
/*---------------------------------------------------------------------------*/
void gotoxy(int x, int y);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* GESTION DE L'ETAPE CHOIX PSEUDO ET VAISSEAU */
/*---------------------------------------------------------------------------*/
void InterfacePseudoVaisseau(void);
void Pseudo(char tabPseudo[8]);
int Vaisseau(void);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* GESTION DU MENU */
/*---------------------------------------------------------------------------*/
char Menu(void);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* GESTION DES OPTIONS DU MENU */
/*---------------------------------------------------------------------------*/
int ChoixModeDeJeu(void);
void Regles(void);
void HistoriqueScore(int tabScore[3],char tabPseudo[8]);
void GestionScore(int tabScore[3],int score);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* JEU */
/*---------------------------------------------------------------------------*/
int GAME(int modedejeu,int chxvaisseau);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* GESTION DU JEU */
/*---------------------------------------------------------------------------*/
void vitesse(int score,int vie,int modedejeu);
void vaisseau(int chxvaisseau);
void EcranDeFin(int modedejeu,int score,int resu);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* FONCTION PRINCIPALE */
/*---------------------------------------------------------------------------*/
int main()
{
    /****************************
     Initialisation des variables
     ****************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int r;                            //Gére la longueur de la barre de chargement
    int chxvaisseau;                  //Choix du vaisseau
    int modedejeu;                    //Choix du mode de jeu

    int score;                        //Score obtenu par le joueur lors de la dernière partie en mode survie
    int tabScore[3];                  //Tableau regroupant les 3 meilleurs scores
    int resu;                         //Variable qui défini la victoire (resu=1) ou la défaite (resu=0) pour le mode SAUVETAGE

    int i;                            //Permet le fonctionnement de la boucle for
    int j;                            //Permet le fonctionnement de la boucle for

    char chx;                         //Choix menu du joueur
    char tabPseudo[8];                //Tableau qui contient le pseudo du joueur
    char touche;                      //Permet de déterminer quel touche du clavier a été saisie
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



    HWND hwnd=GetForegroundWindow();        //Affiche le jeu en plein écran
    ShowWindow(hwnd,SW_MAXIMIZE);

    for(i=0;i<3;i++)
    {
        tabScore[i]=0;      //Initialise les 3 valeurs du tableau des scores à 0
    }



    /**********************************
     Affichage de l'interface d'accueil
     **********************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    color(13,0);   //Change la couleur de la police en rose fluo
    printf("                                                                  "
            "\n\t\t\t\t\t\t\t\t\t             _____ ____  ____  ____________  "
            "\n\t\t\t\t\t\t\t\t\t            / ___// __ \\/   | / ____/ ____/ "
            "\n\t\t\t\t\t\t\t\t\t           \\__  \\/ /_/ / /| |/ /   / __/   "
            "\n\t\t\t\t\t\t\t\t\t           ___/ / ____/ ___ / /___/ /___     "
            "\n\t\t\t\t\t\t\t\t\t          /____/_/   /_/  |_\\____/_____/    "




           "\n\t\t\t\t\t\t\t\t\t       _____   ___    _____    ____  __________     "
           "\n\t\t\t\t\t\t\t\t\t      /  _/ | / / |  / /   |  / __ \\/ ____/ __ \\  "
           "\n\t\t\t\t\t\t\t\t\t      / //  |/ /| | / / /| | / / / / __/ / /_/ /    "
           "\n\t\t\t\t\t\t\t\t\t     / // /|  / | |/ / ___ |/ /_/ / /___/ _  _/     "
           "\n\t\t\t\t\t\t\t\t\t   /___/_/ |_/  |___/_/  |_/_____/_____/_/ |_|      ");




    color(10,0);    //Change la couleur de la police en vert fluo
    printf(
           "\n\n\t\t\t\t\t\t\t\t\t              //////////////////        "
           "\n\t\t\t\t\t\t\t\t\t             ///////////////////////      "
           "\n\t\t\t\t\t\t\t\t\t           ///////////////////////////    "
           "\n\t\t\t\t\t\t\t\t\t          /////////////////////////////   "
           "\n\t\t\t\t\t\t\t\t\t          /////////////////////////////   "
           "\n\t\t\t\t\t\t\t\t\t         //**********///////**********/   "
           "\n\t\t\t\t\t\t\t\t\t          //**********/////**********//   "
           "\n\t\t\t\t\t\t\t\t\t          ///**********///**********///   "
           "\n\t\t\t\t\t\t\t\t\t           /////******////******/////     "
           "\n\t\t\t\t\t\t\t\t\t             ///////////////////////      "
           "\n\t\t\t\t\t\t\t\t\t              /////////////////////       "
           "\n\t\t\t\t\t\t\t\t\t                /////////////////         "
           "\n\t\t\t\t\t\t\t\t\t                   ////////////           "
           "\n\t\t\t\t\t\t\t\t\t                     ///////              ");



    color(5,0);     //Change la couleur de la police en pourpre

    gotoxy(87,30);
    printf("     Loading...");

    gotoxy(75,42);
    printf("- [z,q,s,d] : Selectionner un choix");
    gotoxy(75,44);
    printf("- [Entree] : Valider un choix");

    gotoxy(86,32);


    for (r=1; r<=20; r++)   //Boucle qui crée la barre de chargement (longueur et vitesse)
    {
        printf("%c",219);
        Sleep(150);
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    system("cls");  //Efface l'écran



    /*********************
     Etape du choix pseudo
         et vaisseau
     *********************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    InterfacePseudoVaisseau();

    Pseudo(tabPseudo);

    chxvaisseau=Vaisseau();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    /**********************
     Gestion des choix menu
     **********************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    while (chx!='d')    //Boucle qui réaffiche le menu tant que le choix "QUITTER" n'a pas été validé
    {
        chx=Menu();   //Choix de l'option du menu par le joueur

        system("cls");  //Efface l'écran



        if(chx=='a')    //Choix : JOUER
        {
            modedejeu=ChoixModeDeJeu();     //Choix du mode de jeu

            system("cls");  //Efface l'écran

            if(modedejeu==1)    //Gestion du jeu en mode SURVIE
            {
                score=GAME(modedejeu,chxvaisseau);  //Lancement du jeu

                system("cls");  //Efface l'écran

                EcranDeFin(modedejeu,score,resu);   //Affichage de l'écran de fin du jeu

                GestionScore(tabScore,score);   //Gestion du tableau de score selon le score de la dernière partie
            }
            else    //Gestion du jeu en mode SAUVETAGE
            {
                resu=GAME(modedejeu,chxvaisseau);   //Lancement du jeu

                system("cls");  //Efface l'écran

                EcranDeFin(modedejeu,score,resu);   //Affichage de l'écran de fin du jeu
            }
        }
        else if(chx=='b')   //Choix : REGLES DU JEU
        {
            Regles();
        }
        else if(chx=='c')   //Choix : HISTORIQUE DES SCORES
        {
            HistoriqueScore(tabScore,tabPseudo);
        }

        system("cls");  //Efface l'écran
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    return 0;

}





/*---------------------------------------------------------------------------*/
/* FONCTIONS DE GESTION DE L'ETAPE CHOIX PSEUDO ET VAISSEAU */
/*---------------------------------------------------------------------------*/


/* ROLE : affiche l'interface de l'étape choix pseudo et vaisseau*/
void InterfacePseudoVaisseau()
{
    int i;  //Permet le fonctionnement de la boucle for
    int j;  //Permet le fonctionnement de la boucle for

    color(10,0);     //Change la couleur de la police en vert fluo


    gotoxy(20,25);
    printf("PSEUDO  =>  ");


    for(i=0;i<=51;i++)  //Boucle permettant d'afficher une ligne verticale à l'écran
    {
        gotoxy(90,i);
        printf("|");
    }

    for(i=10;i<40;i=i+12)   //Boucle permettant d'afficher 3 cases
    {
        gotoxy(105,i);
        printf("___________");

        for(j=i+1;j<i+5;j++)
        {
            gotoxy(104,j);
            printf("|\t    |");
        }

        gotoxy(104,i+5);
        printf("|___________|");
    }

    color(11,0);    //Change la couleur de la police en turquoise

    gotoxy(109,13);     //Affiche le premier vaisseau dans la première case
    printf("<o>");      //Design du premier vaisseau

    gotoxy(109,25);     //Affiche le second vaisseau dans la seconde case
    printf("=^=");      //Design du second vaisseau

    gotoxy(109,37);     //Affiche le troisème vaisseau dans la troisième case
    printf("q|p");      //Design du troisième vaisseau
}



/* ROLE : Permet la saisie et l'enregistrement du pseudo du joueur
   ENTREE/SORTIE :  tableau contenant le pseudo du joueur                */
void Pseudo(char tabPseudo[8])
{
    gotoxy(32,25);

    scanf("%s",tabPseudo);  //Saisie du pseudo
}



/* ROLE : Permet au joueur de séléctionner un des 3 vaisseaux
   SORTIE : choix du vaisseau (1, 2 ou 3)                      */
int Vaisseau(void)
{
    int chxvaisseau;    //Choix du vaisseau
    int y;              //Variable de la position verticale de la fléche de séléction
    char touche;        //Permet de déterminer quel touche du clavier a été saisie

    y=13;   //Initialisation de y

    gotoxy(119,y);
    printf("<--");  //Affichage le la flèche

    while (1==1)    //Boucle infini
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche=='z') //'Z' : Permet de déplacer la flèche sur le choix au dessus
            {
                gotoxy(119,y);
                printf("   ");

                if(y==13)   //Si aucun choix présent au dessus, la flèche est déplacé sur le dernier choix
                {
                    y=37;
                    gotoxy(119,y);
                    printf("<--");
                }
                else
                {
                    y=y-12;
                    gotoxy(119,y);
                    printf("<--");
                }
            }
            else if(touche=='s')    //'S' : Permet de déplacer la flèche sur le choix en dessous
            {
                gotoxy(119,y);
                printf("   ");

                if(y==37)   //Si aucun choix présent en dessous, la flèche est déplacé sur le premier choix
                {
                    y=13;
                    gotoxy(119,y);
                    printf("<--");
                }
                else
                {
                    y=y+12;
                    gotoxy(119,y);
                    printf("<--");
                }
            }
            else if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                if(y==13)   //Choix du premier vaisseau
                {
                    chxvaisseau=1;
                }
                else if(y==25)  //Choix du deuxième vaisseau
                {
                    chxvaisseau=2;
                }
                else    //Choix du troisième vaisseau
                {
                    chxvaisseau=3;
                }

                system("cls");  //Efface l'écran

                return chxvaisseau; //Envoie le choix du vaisseau au main
            }
        }
    }
}







/*---------------------------------------------------------------------------*/
/* FONCTION DE GESTION DU MENU */
/*---------------------------------------------------------------------------*/

/* ROLE : affiche le menu et permet de séléctionner, a l'aide d'une flèche,
          le choix menu par le joueur
   SORTIE : choix menu                                     */
char Menu(void)
{
    char touche;        //Permet de déterminer quel touche du clavier a été saisie
    char chx;           //Choix menu
    int y;              //Variable de la position verticale de la fléche de séléction

    color(10,0);     //Change la couleur de la police en vert fluo

    /*****************
     Affichage du menu
     *****************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    gotoxy(80,05);
    printf("\n\t\t\t\t\t\t\t\t\t\t    __  __________   ____  __ "
           "\n\t\t\t\t\t\t\t\t\t\t   /  |/  / ____/ | / / / / /"
           "\n\t\t\t\t\t\t\t\t\t\t  / /|_/ / __/ /  |/ / / / / "
           "\n\t\t\t\t\t\t\t\t\t\t / /  / / /___/ /|  / /_/ /  "
           "\n\t\t\t\t\t\t\t\t\t\t/_/  /_/_____/_/ |_/\\____/   ");


    gotoxy(80,20);
    printf("\n\t\t\t\t\t\t\t\t\t      _  ____  _    _ ______ _____"
           "\n\t\t\t\t\t\t\t\t\t     | |/ __ \\| |  | |  ____|  __ \\ "
           "\n\t\t\t\t\t\t\t\t\t     | | |  | | |  | | |__  | |__) | "
           "\n\t\t\t\t\t\t\t\t\t _   | | |  | | |  | |  __| |  _  /   "
           "\n\t\t\t\t\t\t\t\t\t| |__| | |__| | |__| | |____| | \\ \\  "
           "\n\t\t\t\t\t\t\t\t\t \\____/ \\____/ \\____/|______|_|  \\_\\ ");



    gotoxy(80,30);
    printf("\n\t\t\t\t\t\t\t\t\t _____            _                       _           _              "
           "\n\t\t\t\t\t\t\t\t\t|  __ \\          | |                     | |         (_)             "
           "\n\t\t\t\t\t\t\t\t\t| |__) |___  __ _| | ___  ___          __| |_   _     _  ___ _   _   "
           "\n\t\t\t\t\t\t\t\t\t|  _  // _ \\/ _` | |/ _ \\/ __|        / _` | | | |   | |/ _ \\ | | |  "
           "\n\t\t\t\t\t\t\t\t\t| | \\ \\  __/ (_| | |  __/\\__ \\       | (_| | |_| |   | |  __/ |_| |  "
           "\n\t\t\t\t\t\t\t\t\t|_|  \\_\\___|\\__, |_|\\___||___/        \\__,_|\\__,_|   | |\\___|\\__,_|  "
           "\n\t\t\t\t\t\t\t\t\t             __/ |                                  _/ |             "
           "\n\t\t\t\t\t\t\t\t\t            |___/                                  |__/              ");

    gotoxy(80,40);
    printf("\n\t\t\t\t\t\t\t\t        _    _ _     _             _                        _                                         "
           "\n\t\t\t\t\t\t\t\t       | |  | (_)   | |           (_)                      | |                                        "
           "\n\t\t\t\t\t\t\t\t       | |__| |_ ___| |_ ___  _ __ _  __ _ _   _  ___    __| | ___  ___   ___  ___ ___  _ __ ___  ___ "
           "\n\t\t\t\t\t\t\t\t       |  __  | / __| __/ _ \\| '__| |/ _` | | | |/ _ \\  / _` |/ _ \\/ __| / __|/ __/ _ \\| '__/ _ \\/ __|"
           "\n\t\t\t\t\t\t\t\t       | |  | | \\__ \\ || (_) | |  | | (_| | |_| |  __/ | (_| |  __/\\__ \\ \\__ \\ (_| (_) | | |  __/\\__ \\"
           "\n\t\t\t\t\t\t\t\t       |_|  |_|_|___/\\__\\___/|_|  |_|\\__, |\\__,_|\\___| \\__,_|\\___| |___/ |___/\\___\\___/|_|  \\___||___/"
           "\n\t\t\t\t\t\t\t\t                                        | |                                                           "
           "\n\t\t\t\t\t\t\t\t                                        |_|                                                           ");

    gotoxy(80,50);
    printf("\n\t\t\t\t\t\t\t\t\t   ____        _ _   _            "
           "\n\t\t\t\t\t\t\t\t\t  / __ \\      (_) | | |           "
           "\n\t\t\t\t\t\t\t\t\t | |  | |_   _ _| |_| |_ ___ _ __ "
           "\n\t\t\t\t\t\t\t\t\t | |  | | | | | | __| __/ _ \\ '__|"
           "\n\t\t\t\t\t\t\t\t\t | |__| | |_| | | |_| ||  __/ |   "
           "\n\t\t\t\t\t\t\t\t\t  \\___\\_\\__,_|_|\\__|\\__\\___|_|   ");
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



    /*************************************
     Séléction et validation du choix menu
     *************************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    y=24;   //Initialisation de y

    gotoxy(66,y);
    printf("-->");  //Affichage le la flèche

    while(1==1)    //Boucle infini
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche=='z') //'Z' : Permet de déplacer la flèche sur le choix au dessus
            {
                gotoxy(66,y);
                printf("   ");

                if(y==24)   //Si aucun choix présent au dessus, la flèche est déplacé sur le dernier choix
                {
                    y=54;
                    gotoxy(66,y);
                    printf("-->");
                }
                else
                {
                    y=y-10;
                    gotoxy(66,y);
                    printf("-->");
                }
            }
            else if(touche=='s')    //'S' : Permet de déplacer la flèche sur le choix en dessous
            {
                gotoxy(66,y);
                printf("   ");

                if(y==54)   //Si aucun choix présent en dessous, la flèche est déplacé sur le premier choix
                {
                    y=24;
                    gotoxy(66,y);
                    printf("-->");
                }
                else
                {
                    y=y+10;
                    gotoxy(66,y);
                    printf("-->");
                }
            }
            else if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                if(y==24)   //Choix : JOUER
                {
                    chx='a';
                }
                else if(y==34)  //Choix : REGLES DU JEU
                {
                    chx='b';
                }
                else if(y==44)  //Choix : HISTORIQUE DES SCORES
                {
                    chx='c';
                }
                else if(y==54)  //Choix : QUITTER
                {
                    chx='d';
                }

                return chx; //Envoie le choix menu au main
            }
        }
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}





/*---------------------------------------------------------------------------*/
/* FONCTIONS DE GESTION DES OPTIONS DU MENU */
/*---------------------------------------------------------------------------*/

/* ROLE : Permet au joueur de choisir un des 2 modes de jeu. Et pour le cas
          du mode SAUVETAGE, de choisir le nombre de vies a atteindre
   SORTIE : choix du mode de jeu                    */
int ChoixModeDeJeu(void)
{
    int modedejeu;      //Choix du mode de jeu

    int x;              //Variable de la position horizontale de la fléche de séléction
    int y;              //Variable de la position verticale de la fléche de séléction
    char touche;        //Permet de déterminer quel touche du clavier a été saisie

    int i;              //Permet le fonctionnement de la boucle for
    int j;              //Permet le fonctionnement de la boucle for


    modedejeu=0;


    /**********************************
     Affichage des choix de mode de jeu
     **********************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    gotoxy(70,10);
    printf("\n\t\t\t\t\t\t\t\t    __  _______  ____  ______   ____  ______       __________  __"
           "\n\t\t\t\t\t\t\t\t   /  |/  / __ \\/ __ \\/ ____/  / __ \\/ ____/      / / ____/ / / /"
           "\n\t\t\t\t\t\t\t\t  / /|_/ / / / / / / / __/    / / / / __/    __  / / __/ / / / /"
           "\n\t\t\t\t\t\t\t\t / /  / / /_/ / /_/ / /___   / /_/ / /___   / /_/ / /___/ /_/ /"
           "\n\t\t\t\t\t\t\t\t/_/  /_/\\____/_____/_____/  /_____/_____/   \\____/_____/\\____/");

    gotoxy(25,20);
    printf("\n\t\t\t\t   _____ __  ______ _    ____________"
           "\n\t\t\t\t  / ___// / / / __ \\ |  / /  _/ ____/"
           "\n\t\t\t\t  \\__ \\/ / / / /_/ / | / // // __/"
           "\n\t\t\t\t ___/ / /_/ / _, _/| |/ // // /___"
           "\n\t\t\t\t/____/\\____/_/ |_| |___/___/_____/");


    gotoxy(115,20);
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   _____ ___   __  ___    _________________   ____________"
           "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  / ___//   | / / / / |  / / ____/_  __/   | / ____/ ____/"
           "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  \\__ \\/ /| |/ / / /| | / / __/   / / / /| |/ / __/ __/"
           "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t ___/ / ___ / /_/ / | |/ / /___  / / / ___ / /_/ / /___"
           "\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t/____/_/  |_\\____/  |___/_____/ /_/ /_/  |_\\____/_____/");
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    /********************************
     Séléction et validation du choix
              de mode de jeu
     ********************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    x=48;   //Initialisation de x

    gotoxy(x,28);
    printf("^");
    gotoxy(x,29);
    printf("|");
    gotoxy(x,30);
    printf("|");      //Affichage le la flèche

    while(modedejeu==0) //Boucle qui continue tant que aucun mode de jeu n'a été choisi
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche=='q'||touche=='d') //'Q'/'D' : Permet de déplacer la flèche sur l'autre choix
            {
                gotoxy(x,28);
                printf(" ");
                gotoxy(x,29);
                printf(" ");
                gotoxy(x,30);
                printf(" ");

                if(x==48)
                {
                    x=150;
                    gotoxy(x,28);
                    printf("^");
                    gotoxy(x,29);
                    printf("|");
                    gotoxy(x,30);
                    printf("|");
                }
                else
                {
                    x=48;
                    gotoxy(x,28);
                    printf("^");
                    gotoxy(x,29);
                    printf("|");
                    gotoxy(x,30);
                    printf("|");
                }
            }
            else if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                if(x==48)   //Choix : MODE SURVIE
                {
                    modedejeu=1;
                }
                else    //Choix : MODE SAUVETAGE
                {
                    modedejeu=2;
                }
            }
        }
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    system("cls");  //Efface l'écran



    /***********************************
     Choix du nombre de vies a atteindre
        (si le choix du mode de jeu
            est le SAUVETAGE)
     ***********************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(modedejeu==2)
    {
        gotoxy(90,5);
        printf("NOMBRES DE VIES A ATTEINDRE");

        for(i=15;i<36;i=i+10)
        {
            gotoxy(65,i);
            printf(" _________");

            for(j=i+1;j<i+5;j++)
            {
                gotoxy(65,j);
                printf("|\t   |");
            }

            gotoxy(65,i+5);
            printf("|_________|");
        }

        gotoxy(67,18);
        printf("10 VIES");

        gotoxy(67,28);
        printf("20 VIES");

        gotoxy(67,38);
        printf("30 VIES");


        y=18;   //Initialisation de y

        gotoxy(77,y);
        printf("<--");  //Affichage le la flèche

        while(modedejeu==2) //Boucle qui continue tant que aucun nombre de vies a atteindre n'a été choisi
        {
            if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
            {
                touche = getch();   //Enregistre la touche saisie dans la variable touche

                if(touche=='z') //'Z' : Permet de déplacer la flèche sur le choix au dessus
                {
                    gotoxy(77,y);
                    printf("   ");

                    if(y==18)   //Si aucun choix présent au dessus, la flèche est déplacé sur le dernier choix
                    {
                        y=38;
                        gotoxy(77,y);
                        printf("<--");
                    }
                    else
                    {
                        y=y-10;
                        gotoxy(77,y);
                        printf("<--");
                    }
                }
                else if(touche=='s')    //'S' : Permet de déplacer la flèche sur le choix en dessous
                {
                    gotoxy(77,y);
                    printf("   ");

                    if(y==38)   //Si aucun choix présent en dessous, la flèche est déplacé sur le premier choix
                    {
                        y=18;
                        gotoxy(77,y);
                        printf("<--");
                    }
                    else
                    {
                        y=y+10;
                        gotoxy(77,y);
                        printf("<--");
                    }
                }
                else if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
                {
                    if(y==18)   //Choix : 10 vies
                    {
                        modedejeu=3;
                    }
                    else if(y==28)  //Choix : 20 vies
                    {
                        modedejeu=4;
                    }
                    else    //Choix : 30 vies
                    {
                        modedejeu=5;
                    }
                }
            }
        }
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    return modedejeu; //Envoie le choix du mode de jeu au main
}


/* ROLE : affiche les règles du jeu */
void Regles(void)
{
    int i;              //Permet le fonctionnement de la boucle for
    char touche;        //Permet de déterminer quel touche du clavier a été saisie

    /***************************
     Affichage des règles du jeu
     ***************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    gotoxy(12,8);
    printf("Regles du jeu :");
    gotoxy(12,9);
    printf("-------------");
    gotoxy(17,11);
	printf("- Vous controlez un vaisseau pouvant tirer.");
	gotoxy(17,13);
	printf("- Vous devez eviter les navettes ennemies (");
	color(12,0);    //Change la couleur de la police en rouge
	printf("V--V");
	color(10,0);    //Change la couleur de la police en vert fluo
	printf(")et les asteroides (");
	color(4,0);    //Change la couleur de la police en marron
	printf("OO");
	color(10,0);    //Change la couleur de la police en vert fluo
	printf(")");
	gotoxy(20,14);
    printf("qui descendent dans la zone de jeu et attraper les vitamines (");
    color(2,0);    //Change la couleur de la police en vert
    printf("++++");
    color(10,0);    //Change la couleur de la police en vert fluo
    printf(").");
	gotoxy(17,16);
	printf("- Lorsque vous n'avez plus de vie c'est GAME OVER.");


	gotoxy(110,8);
    printf("Fonctionnement :");
    gotoxy(110,9);
    printf("--------------");
    gotoxy(115,11);
	printf("- Appuyez sur ENTREE pour demarrer une partie.");
	gotoxy(115,13);
	printf("- Utilisez les touches 'z', 'q', 's' et 'd' pour vous diriger");
	gotoxy(118,14);
	printf("dans 4 directions differentes.");
	gotoxy(115,16);
	printf("- Utilisez la touche ESPACE pour tirer un laser.");


    gotoxy(12,33);
    printf("Mode Survie :");
    gotoxy(12,34);
    printf("-----------");
    gotoxy(17,36);
	printf("- Votre but est de survivre le plus longtemps possible.");
	gotoxy(17,38);
	printf("- Plus vous progresserez dans le jeu, plus la vitesse des vaisseaux");
	gotoxy(20,39);
    printf("augmentera par palier.");
	gotoxy(17,41);
	printf("- Lorsque vous n'avez plus de vie, la partie se termine avec");
	gotoxy(20,42);
	printf("le score atteint enregistre.");


    gotoxy(110,33);
    printf("Mode Sauvetage :");
    gotoxy(110,34);
    printf("--------------");
    gotoxy(115,36);
	printf("- Votre but est d'obtenir un nombre de vies requis");
    gotoxy(118,37);
    printf("(choix du nombre de vies a atteindre par le joueur).");
	gotoxy(115,39);
	printf("- Plus vous gagnerez de vies au cours de la partie, plus la vitesse des vaisseaux");
	gotoxy(118,40);
    printf("et le nombre de vies perdu par contact ennemie augmentera par palier.");
	gotoxy(115,42);
	printf("- Lorsque vous n'avez plus de vie, vous perdez la partie.");
	gotoxy(115,44);
	printf("- Lorsque vous avez atteint le nombre de vies requis, vous gagnez la partie.");
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    for (i=0;i<=196;i++)    //Boucle qui affiche une ligne horizontale qui coupe l'écran
    {
        gotoxy(i,25);
        printf("_");
    }

    for(i=0;i<=51;i++)  //Boucle qui affiche une ligne verticale qui coupe l'écran
    {
        gotoxy(98,i);
        printf("|");
    }


    /* Permet au joueur de retourner au menu en saisisant la touche 'Entrée*/

    while(1==1) //Boucle infini
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                return 0;   //Retour au menu
            }
        }
    }
}


/* ROLE : Affiche l'historique des 3 meilleurs scores obtenu par le joueur
   ENTREE :  - pseudo du joueur
   ENTREE/SORTIE :  - tableau des meilleurs scores    */
void HistoriqueScore(int tabScore[3],char tabPseudo[8])
{
    char touche;        //Permet de déterminer quel touche du clavier a été saisie

    /************************************
     Affichage de l'historique des scores
     ************************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    gotoxy(88,5);
    printf("HISTORIQUE DES SCORES");

    if(tabScore[0]!=0)  //Affiche le pseudo et le score si le score est non nul
    {
        gotoxy(82,20);
        printf("%s",tabPseudo); //Affichage du pseudo du joueur
        gotoxy(110,20);
        printf("%d",tabScore[0]);   //Affichage du meilleur score
    }

    if(tabScore[1]!=0)  //Affiche le pseudo et le score si le score est non nul
    {
        gotoxy(82,25);
        printf("%s",tabPseudo); //Affichage du pseudo du joueur
        gotoxy(110,25);
        printf("%d",tabScore[1]);   //Affichage du second meilleur score
    }

    if(tabScore[2]!=0)  //Affiche le pseudo et le score si le score est non nul
    {
        gotoxy(82,30);
        printf("%s",tabPseudo); //Affichage du pseudo du joueur
        gotoxy(110,30);
        printf("%d",tabScore[2]);   //Affichage du troisième meilleur score
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    /* Permet au joueur de retourner au menu en saisisant la touche 'Entrée*/

    while(1==1) //Boucle infini
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                return 0;   //Retour au menu
            }
        }
    }
}


/* ROLE : ajoute le score de la dernière partie et trie le tableau
          si le dernier score est supérieur au minimum au troisième
          meilleur score
   ENTREE :  le score de la dernière partie de joueur
   ENTREE/SORTIE : le tableau des 3 meilleurs scores*/
void GestionScore(int tabScore[3],int score)
{
    int i;  //Permet le fonctionnement de la boucle for

    for(i=0;i<3;i++)    //Boucle permettant de comparer le dernier score obtenu avec les 3 meilleurs scores
    {
        if(score>tabScore[i])   //Détermine si le dernier score obtenu est supérieur a l'un des 3 meilleurs scores
        {
            if(i==0)    //Ajout et trie du tableau des scores si le dernier score obtenu est supérieur au meilleur score
            {
                tabScore[2]=tabScore[1];
                tabScore[1]=tabScore[0];
                tabScore[0]=score;
            }
            else if(i==1)    //Ajout et trie du tableau des scores si le dernier score obtenu est supérieur au second meilleur score
            {
                tabScore[2]=tabScore[1];
                tabScore[1]=score;
            }
            else    //Ajout si le dernier score obtenu est supérieur au troisième meilleur score
            {
                tabScore[2]=score;
            }

            score=0;    //Réinitialisation du score
        }
    }
}







/*---------------------------------------------------------------------------*/
/* FONCTION DU JEU */
/*---------------------------------------------------------------------------*/

/* ROLE : affiche le jeu, gère les commandes du joueur et gère le progression du jeu
   ENTREE :  - le mode de jeu choisi par le joueur
             - le vaisseau choisi par le joueur
   SORTIE : - Si mode SURVIE : le score final du joueur
            - Si mode SAUVETAGE : "0" si le joueur a perdu ou "1" si le joueur a gagné*/
int GAME(int modedejeu,int chxvaisseau)
{
    /****************************
     Initialisation des variables
     ****************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int x,y;    //Coordonnées x et y du vaisseau du joueur sur l'écran

    int tabYEM[10];     //Tableau des coordonnées x des vaisseaux ennemies
    int tabXEM[10];     //Tableau des coordonnées y des vaisseaux ennemies
    int tabXA[20];      //Tableau des coordonnées x des astéroïdes
    int tabYA[20];      //Tableau des coordonnées y des astéroïdes
    int tabXV[3];       //Tableau des coordonnées x des vitamines
    int tabYV[3];       //Tableau des coordonnées y des vitamines

    int mouv;           //Mouvement horizzontale aléatoire des vaisseaux ennemies

    int i;              //Permet le fonctionnement de la boucle for
    int pause;          //Permet au programme de déterminer si le jeu est en pause ou non

    int vie;            //Nombre de vies du joueur au cours de la partie
    int cooldown;       //Temps d'attente du joueur pour pouvoir retirer un laser
    int munitions;      //Nombre de munitions de laser du joueur au cours de la partie
    int chxvies;        //Nombre de vies a atteindre pour gagner
    int score;          //Score du joueur au cours de la partie

    char touche;        //Permet de déterminer quel touche du clavier a été saisie
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


    srand( time(NULL) );

    for (i=0;i<50;i++)  //Boucle qui permet de dessiner les limites de la surface de jeu
    {
        gotoxy(57,i);
        printf("|");

        gotoxy(136,i);
        printf("|");
    }



    /******************************************
     Initialisation des valeurs de début de jeu
     ******************************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    score=0;
    munitions=5;
    cooldown=0;

    if(modedejeu==1)    //Attribution du nombre de vies de départ au joueur pour le mode SURVIE
    {
        vie=3;
    }
    else    //Attribution du nombre de vies de départ au joueur pour le mode SAUVETAGE
    {
        vie=1;

        if(modedejeu==3)
        {
            chxvies=10;
            modedejeu=2;
        }
        else if(modedejeu==4)
        {
            chxvies=20;
            modedejeu=2;
        }
        else
        {
            chxvies=30;
            modedejeu=2;
        }
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




    /**************************
     Initialisation du vaisseau
            du joueur
     **************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    x=97;   //Initialisation de la postion x
    y=45;   //Initialisation de la position y

    gotoxy(x,y);            //Position du joueur
    vaisseau(chxvaisseau);  //Affichage du joueur
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~*/




    /****************************
     Initialisation des vaisseaux
              ennemies
     ****************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for (i=0;i<10;i++)
    {
        tabXEM[i]= (rand() % 73)+59;    //Initialisation aléatoire de la position x
        tabYEM[i]= rand() % 41;         //Initialisation aléatoire de la position y
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




    /*****************************
     Initialisation des astéroïdes
     *****************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for (i=0;i<20;i++)
    {
        tabXA[i]= (rand() % 73)+59;    //Initialisation aléatoire de la position x
        tabYA[i]= rand() % 41;         //Initialisation aléatoire de la position y
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




    /****************************
     Initialisation des vitamines
     ****************************/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(i=0;i<3;i++)
    {
        tabXV[i]= (rand() % 73)+59;    //Initialisation aléatoire de la position x
        tabYV[i]= rand() % 21;         //Initialisation aléatoire de la position y
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




    while (1==1)    //Boucle infini qui permet de faire tourner le jeu continuellement
    {

        /***************************
         Gestion des commandes et du
              vaisseau du joueur
         ***************************/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        gotoxy(x,y);            //Position du joueur
        vaisseau(chxvaisseau);  //Affichage du joueur

        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche


            /* Gestion de la pause et de l'arrêt de jeu */

            if(touche=='p')  // 'P' met le jeu en pause/marche
            {
                pause=1;

                while(pause==1)
                {
                    gotoxy(27,25);
                    printf("PAUSE");    //Affiche le message "PAUSE" pour confirmer la mise en pause du jeu

                    if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
                    {
                        touche = getch();   //Enregistre la touche saisie dans la variable touche

                        if(touche=='p')  // 'P' : met le jeu en pause/marche
                        {
                            gotoxy(27,25);
                            printf("     ");    //Retire le message "PAUSE" pour confirmer la remise en marche du jeu
                            pause=0;
                        }
                    }
                }
            }
            else if(touche==27)     //Touche echap : met fin au jeu
            {
                if(modedejeu==1)  //Envoie au main le score si le mode était le mode SURVIE
                {
                    return score;
                }
                else  //Envoie au main la valeur de défaite si le mode était le mode SAUVETAGE
                {
                    return 0;
                }
            }


            /* Gestion des déplacements du joueur */

            gotoxy(x,y);         //Position du joueur
            printf("   ");       //Effacement du vaiseau du joueur

            if(touche=='q'&&x!=59)
            {
                x= x-1; /* gauche */
            }
            else if(touche=='d'&&x!=132)
            {
                x= x+1; /* droite */
            }
            else if(touche=='z'&&y!=30)
            {
                y= y-1; /* haut */
            }
            else if(touche=='s'&&y!=49)
            {
                y= y+1; /* bas */
            }

            gotoxy(x,y);            //Position du joueur
            vaisseau(chxvaisseau);  //Affichage du joueur



            /* Gestion du laser du joueur */

            if(touche==32&&munitions>0&&cooldown==0)    //Conditions permettant au joueur de tirer un laser ou non
            {
                color(5,0); //Change la couleur de la police en pourpre

                for(i=0;i<y;i++)    //Boucle permettant l'affichage du laser
                {
                    gotoxy(x+1,i);
                    printf("*");
                }

                Sleep(200);     //Permet au laser d'avoir le temps de s'afficher



                /* Gestion des collisions ennemies et astéroïdes avec le laser */

                color(12,0);    //Change la couleur de la police en rouge
                for(i=0;i<10;i++)   //Boucle qui permet de vérifier si une collision a eu lieu entre le laser et un vaisseau ennemie
                {
                    if(tabYEM[i]<y)
                    {
                        if(tabXEM[i]==x+1||tabXEM[i]+1==x+1||tabXEM[i]+2==x+1||tabXEM[i]+3==x+1)
                        {
                            /* Si collision a eu lieu : Effacement du vaisseau ennemie et
                                  repositionnement aléatoire en haut de l'écran */

                            gotoxy(tabXEM[i],tabYEM[i]);
                            printf("    ");

                            tabYEM[i]=0;
                            tabXEM[i]=(rand() % 72)+59;

                            gotoxy(tabXEM[i],tabYEM[i]);
                            printf("V--V");

                            score=score+50; //Ajoute +50 au score pour chaque ennemie touché au laser
                        }
                    }
                }

                color(4,0); //Change la couleur de la police en marron
                for(i=0;i<20;i++)   //Boucle qui permet de vérifier si une collision a eu lieu entre le laser et un astéroïde
                {
                    if(tabYA[i]<y)
                    {
                        if(tabXA[i]==x+1||tabXA[i]+1==x+1)
                        {
                            /* Si collision a eu lieu : Effacement de l'astéroïde et
                                  repositionnement aléatoire en haut de l'écran */

                            gotoxy(tabXA[i],tabYA[i]);
                            printf("  ");

                            tabYA[i]=0;
                            tabXA[i]=(rand() % 72)+59;

                            gotoxy(tabXA[i],tabYA[i]);
                            printf("OO");

                            score=score+50; //Ajoute +50 au score pour chaque astéroïde touché au laser
                        }
                    }
                }

                for(i=0;i<y;i++)    //Boucle qui permet d'éffacer le laser de l'écran
                {
                    gotoxy(x+1,i);
                    printf(" ");
                }


                vitesse(score,vie,modedejeu);   //Gestion de la vitesse du jeu

                munitions=munitions-1;  //Diminution du stock de munition
                cooldown=-10;   //Ajout d'un temps d'attente
            }
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




        /*****************************
         Gestion ennemies + collisions
         *****************************/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        color(12,0);    //Chage la couleur de la police en rouge
        for(i=0;i<10;i++)   //Boucle permetant de gérer chaque vaisseau
        {
            /* Vérification de collision avant le mouvement */

            if(y==tabYEM[i])
            {
                if(x==tabXEM[i]||x==tabXEM[i]+1||x==tabXEM[i]+2||x==tabXEM[i]+3||x+2==tabXEM[i]+1||x+2==tabXEM[i])
                {
                    /* Si collision détecté */


                    if(modedejeu==1||modedejeu==2&&vie<20)  //Perte de vie en condition normale
                    {
                        vie=vie-2;
                    }
                    else    //Perte de vie en condition de SAUVETAGE et en ayant atteint le palier de vie récolté requis
                    {
                        vie=vie-3;
                    }


                    gotoxy(tabXEM[i],tabYEM[i]);
                    printf("    ");                     //Effacement du vaisseau ennemie

                    tabYEM[i]=0;
                    tabXEM[i]=(rand() % 72)+59;         //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXEM[i],tabYEM[i]);
                    printf("V--V");                     //Affichage du vaisseau ennemie
                }
            }

            gotoxy(tabXEM[i],tabYEM[i]);
            printf("    ");                 //Effacement du vaisseau ennemie

            if(tabYEM[i]==49)   //Repositionnement aléatoire en haut de l'écran si le vaisseau ennemie a atteint le bas de l'écran
            {
                tabYEM[i]=0;
                tabXEM[i]=(rand() % 72)+59;
            }
            else    //Progression du vaisseau vers le bas de l'écran
            {
                tabYEM[i]=tabYEM[i]+1;
            }



            /* Gestion des mouvements horizontaux aléatoires */

            do      //Initialisation aléatoire du mouvement horizontale des vaisseaux ennemies
            {
                mouv= (rand() % 4)-2;

            } while(mouv==0);


            ///Déplacement du vaisseau ennemie du côté gauche de l'écran si le vaisseau se trouvait initiallement
            ///du côté droit de l'écran et qu'il ait fait un mouvement vers la droite  (inversement aussi)

            if (tabXEM[i]==130&&mouv==2||tabXEM[i]==131&&mouv==1)
            {
                tabXEM[i]=59;
            }
            else if (tabXEM[i]==131&&mouv==2)
            {
                tabXEM[i]=60;
            }
            else if (tabXEM[i]==59&&mouv==-1||tabXEM[i]==60&&mouv==-2)
            {
                tabXEM[i]=131;
            }
            else if (tabXEM[i]==59&&mouv==-2)
            {
                tabXEM[i]=130;
            }
            else
            {
                tabXEM[i]=tabXEM[i]+mouv;
            }


            gotoxy(tabXEM[i],tabYEM[i]);
            printf("V--V");                 //Affichage du vaisseau ennemie


            /* Vérification de collision après le mouvement */

            if(y==tabYEM[i])
            {
                if(x==tabXEM[i]||x==tabXEM[i]+1||x==tabXEM[i]+2||x==tabXEM[i]+3||x+2==tabXEM[i]+1||x+2==tabXEM[i])
                {
                    /* Si collision détecté */


                    if(modedejeu==1||modedejeu==2&&vie<20)  //Perte de vie en condition normale
                    {
                        vie=vie-2;
                    }
                    else    //Perte de vie en condition de SAUVETAGE et en ayant atteint le palier de vie récolté requis
                    {
                        vie=vie-3;
                    }


                    gotoxy(tabXEM[i],tabYEM[i]);
                    printf("    ");                     //Effacement du vaisseau ennemie

                    tabYEM[i]=0;
                    tabXEM[i]=(rand() % 72)+59;         //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXEM[i],tabYEM[i]);
                    printf("V--V");                     //Affichage du vaisseau ennemie
                }
            }
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




        /*******************************
         Gestion astéroïdes + collisions
         *******************************/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        color(4,0); //Change la couleur de la police en marron
        for (i=0;i<20;i++)   //Boucle permetant de gérer chaque astéroïde
        {
            /* Vérification de collision avant le mouvement */

            if(y==tabYA[i])
            {
                if(x==tabXA[i]||x==tabXA[i]+1||x+1==tabXA[i]||x+2==tabXA[i])
                {
                    /* Si collision détecté */


                    if(modedejeu==1||modedejeu==2&&vie<20)  //Perte de vie en condition normale
                    {
                        vie=vie-1;
                    }
                    else    //Perte de vie en condition de SAUVETAGE et en ayant atteint le palier de vie récolté requis
                    {
                        vie=vie-2;
                    }

                    gotoxy(tabXA[i],tabYA[i]);
                    printf("  ");                     //Effacement de l'astéroïde

                    tabYA[i]=0;
                    tabXA[i]=(rand() % 72)+59;        //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXA[i],tabYA[i]);
                    printf("OO");                     //Affichage de l'astéroïde
                }
            }

            gotoxy(tabXA[i],tabYA[i]);
            printf("  ");   //Effacement de l'astéroïde

            if(tabYA[i]==49)   //Repositionnement aléatoire en haut de l'écran si l'astéroïde a atteint le bas de l'écran
            {
                tabYA[i]=0;

                tabXA[i]=(rand() % 72)+59;

            }
            else    //Progression de l'astéroïde vers le bas de l'écran
            {
                tabYA[i]=tabYA[i]+1;
            }

            gotoxy(tabXA[i],tabYA[i]);
            printf("OO");   //Affichage de l'asttéroïde


            /* Vérification de collision après le mouvement */

            if(y==tabYA[i])
            {
                if(x==tabXA[i]||x==tabXA[i]+1||x+1==tabXA[i]||x+2==tabXA[i])
                {
                    /* Si collision détecté */


                    if(modedejeu==1||modedejeu==2&&vie<20)  //Perte de vie en condition normale
                    {
                        vie=vie-1;
                    }
                    else    //Perte de vie en condition de SAUVETAGE et en ayant atteint le palier de vie récolté requis
                    {
                        vie=vie-2;
                    }

                    gotoxy(tabXA[i],tabYA[i]);
                    printf("  ");                     //Effacement de l'astéroïde

                    tabYA[i]=0;
                    tabXA[i]=(rand() % 72)+59;        //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXA[i],tabYA[i]);
                    printf("OO");                     //Affichage de l'astéroïde
                }
            }
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/




        /******************************
         Gestion vitamines + collisions
         ******************************/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        color(2,0); //Change la couleur de la police en vert
        for (i=0;i<3;i++)   //Boucle permetant de gérer chaque vitamine
        {
            /* Vérification de collision avant le mouvement */

            if(y==tabYV[i])
            {
                if(x==tabXV[i]||x==tabXV[i]+1||x==tabXV[i]+2||x==tabXV[i]+3||x+2==tabXV[i]+1||x+2==tabXV[i])
                {
                    /* Si collision détecté */


                    score=score+100;            //Gain de score
                    vie=vie+1;                  //Gain de vie
                    munitions=munitions+1;      //Gain de munition de laser

                    gotoxy(tabXV[i],tabYV[i]);
                    printf("    ");                   //Effacement de la vitamine

                    tabYV[i]=0;
                    tabXV[i]=(rand() % 72)+59;        //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXV[i],tabYV[i]);
                    printf("++++");                     //Affichage de la vitamine
                }
            }

            gotoxy(tabXV[i],tabYV[i]);
            printf("    ");     //Effacement de la vitamine

            if(tabYV[i]==49)   //Repositionnement aléatoire en haut de l'écran si la vitamine a atteint le bas de l'écran
            {
                tabYV[i]=0;
                tabXV[i]=(rand() % 72)+59;
            }
            else    //Progression de la vitamine vers le bas de l'écran
            {
                tabYV[i]=tabYV[i]+1;
            }

            gotoxy(tabXV[i],tabYV[i]);
            printf("++++");     //Affichage de la vitamine


            /* Vérification de collision avant le mouvement */

            if(y==tabYV[i])
            {
                if(x==tabXV[i]||x==tabXV[i]+1||x==tabXV[i]+2||x==tabXV[i]+3||x+2==tabXV[i]+1||x+2==tabXV[i])
                {
                    /* Si collision détecté */


                    score=score+100;            //Gain de score
                    vie=vie+1;                  //Gain de vie
                    munitions=munitions+1;      //Gain de munition de laser

                    gotoxy(tabXV[i],tabYV[i]);
                    printf("    ");                   //Effacement de la vitamine

                    tabYV[i]=0;
                    tabXV[i]=(rand() % 72)+59;        //Repositionnement aléatoire en haut de l'écran

                    gotoxy(tabXV[i],tabYV[i]);
                    printf("++++");                     //Affichage de la vitamine
                }
            }
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


        /* Gestion du temps d'attente pour pouvoir retirer un laser */

        if(cooldown<0)
        {
            cooldown=cooldown+1;
        }



        /************************
         Gestion de l'interface
                 du jeu
         ************************/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        color(15,0);    //Change la couleur de la police en blanc

        gotoxy(150,15);
        printf("                ");
        gotoxy(150,15);
        printf("VIES : %d",vie);        //Actualise l'affichage du nombre de vies à l'instant

        gotoxy(150,17);
        if(modedejeu==1)    //Affiche le score à l'instant du joueur si le mode de jeu est le mode SURVIE
        {
            score=score+1;
            printf("SCORE : %d",score);
        }
        else if(modedejeu==2)   //Affiche le nombre de vies a atteindre si le mode de jeu est le mode SAUVETAGE
        {
            printf("OBJECTIF : %d",chxvies);
        }

        gotoxy(150,23);
        printf("                   ");
        gotoxy(150,23);
        printf("MUNITIONS : %d",munitions);        //Actualise l'affichage du nombre de munitions à l'instant

        gotoxy(150,25);
        printf("             ");
        gotoxy(150,25);
        printf("COOLDOWN : %d",cooldown);   //Actualise l'affichage du temps d'attente pour pouvoir retirer un laser à l'instant

        gotoxy(15,32);
        printf("TIRER UN LASER : [espace]");       //Affiche un message indiquant au joueur la touche pour tirer un laser

        gotoxy(15,35);
        printf("METTRE LE JEU EN ARRET/MARCHE :  p");       //Affiche un message indiquant au joueur la touche pour mettre le jeu en pause

        gotoxy(15,38);
        printf("METTRE FIN AU JEU : [echap]");       //Affiche un message indiquant au joueur la touche pour mettre fin au jeu
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/





        /***************************************
         GESTION DES CONDITIONS DE FIN DE PARTIE
         ***************************************/

        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if(modedejeu==1&&vie<=0)    //Lorsque le joueur n'a plus de vie (SURVIE)
        {
            return score;   //Score obtenu lors de la partie SURVIE
        }
        else if(modedejeu==2&&vie==10&&chxvies==10||modedejeu==2&&vie==20&&chxvies==20||modedejeu==2&&vie==30&&chxvies==30) /*Lorsque le joueur atteint le*/
        {                                                                                                                   /*nombre de vie requis (SAUVETAGE)*/
            return 1;   //Valeur de victoire de la partie SAUVETAGE
        }
        else if(modedejeu==2&&vie<=0)   //Lorsque le joueur n'a plus de vie (SAUVETAGE)
        {
            return 0;   //Valeur de défaite de la partie SAUVETAGE
        }
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


        vitesse(score,vie,modedejeu);   //Gestion de la vitesse du jeu
    }
}





/*---------------------------------------------------------------------------*/
/* FONCTIONS DE GESTION DU JEU */
/*---------------------------------------------------------------------------*/

/* ROLE : gère la vitesse du jeu selon le score (SURVIE) ou le nombre de vies (SAUVETAGE)
   ENTREE :  - Le score de la partie en cours du joueur
             - Le nombre de vies du joueur à l'instant
             - Le choix du mode de jeu                        */
void vitesse(int score,int vie,int modedejeu)
{
    if(modedejeu==1)    //Gestion de la vitesse du jeu en mode SURVIE
    {
        if(score<1000)  //Vitesse initiale lorsque le score est inférieur a 1000
        {
            Sleep(150);
        }
        else if(score<7500) //Vitesse intermédiaire lorsque le score est compris entre 1000 et 7500
        {
            Sleep(90);
        }
        else    //Vitesse maximale lorsque le score est supérieur a 7500
        {
            Sleep(65);
        }
    }
    else if(modedejeu==2)    //Gestion de la vitesse du jeu en mode SAUVETAGE
    {
        if(vie<10)  //Vitesse initiale lorsque le nombre de vies est inférieur a 10
        {
            Sleep(150);
        }
        else if(vie<25) //Vitesse intermédiaire lorsque le nombre de vies est compris entre 10 et 25
        {
            Sleep(90);
        }
        else    //Vitesse maximale lorsque le nombre de vie est supérieur a 25
        {
            Sleep(65);
        }
    }
}


/* ROLE : calcule la résistance équivalente dans un montage électrique
   ENTREE :     nbR : nombre de résistances du circuit électrique
                tabR : tableau avec les valeurs des nbR résistances
                typeMont : type de montage (série 's' ou parallèle 'p')
   SORTIE : valeur de la résistance équivalente en Ohms                     */
void vaisseau(int chxvaisseau)
{
    color(11,0);    //Change la couleur de la police en turquoise

    if(chxvaisseau==1)
    {
        printf("<o>");  //Affichage du premier vaisseau
    }
    else if(chxvaisseau==2)
    {
        printf("=^=");  //Affichage du deuxieme vaisseau
    }
    else
    {
        printf("q|p");  //Affichage du troisième vaisseau
    }
}


/* ROLE : afficher un écran de fin de jeu en fonction du résultat de la dernière partie
   ENTREE :  - le mode de jeu
             - le score obtenu par le joueur lors de la partie
             - la variable qui défini la victoire (resu=1) ou la défaite (resu=0) pour le mode SAUVETAGE */
void EcranDeFin(int modedejeu,int score,int resu)
{
    char touche;        //Permet de déterminer quel touche du clavier a été saisie

    color(10,0);    //Change la couleur de la police en vert fluo

    if(modedejeu==1||resu==0)   //Ecran de GAME OVER lorsque le mode de jeu joué est le mode SURVIE ou lorsque le joueur perd le mode SAUVETAGE
    {
        gotoxy(50,20);
        printf("\n\t\t\t\t\t\t\t\t       _________    __  _________   ____ _    ____________"
               "\n\t\t\t\t\t\t\t\t      / ____/   |  /  |/  / ____/  / __ \\ |  / / ____/ __ \\"
               "\n\t\t\t\t\t\t\t\t     / / __/ /| | / /|_/ / __/    / / / / | / / __/ / /_/ /"
               "\n\t\t\t\t\t\t\t\t    / /_/ / ___ |/ /  / / /___   / /_/ /| |/ / /___/ _, _/"
               "\n\t\t\t\t\t\t\t\t    \\____/_/  |_/_/  /_/_____/   \\____/ |___/_____/_/ |_| ");

        if(modedejeu==1)    //Affichage du score si le mode de jeu séléctionné est le mode SURVIE
        {
            gotoxy(87,35);
            printf("Votre score : %d",score);
        }
    }
    else    //Ecran de VICTOIRE lorsque le joueur gagne le mode SAUVETAGE
    {
        gotoxy(50,20);
        printf("\n\t\t\t\t\t\t\t\t      _    ______________________  ________  ______"
               "\n\t\t\t\t\t\t\t\t     | |  / /  _/ ____/_  __/ __ \\/  _/ __ \\/ ____/"
               "\n\t\t\t\t\t\t\t\t     | | / // // /     / / / / / // // /_/ / __/"
               "\n\t\t\t\t\t\t\t\t     | |/ // // /___  / / / /_/ // // _, _/ /___"
               "\n\t\t\t\t\t\t\t\t     |___/___/\\____/ /_/  \\____/___/_/ |_/_____/");

    }


    /* Permet au joueur de retourner au menu en saisisant la touche 'Entrée*/

    while(1==1) //Boucle infini
    {
        if(kbhit() == 1)    //Détecte la saisie d'une touche du clavier
        {
            touche = getch();   //Enregistre la touche saisie dans la variable touche

            if(touche==13) //'Entrée' : Permet de valider le choix pointé par la flèche
            {
                return 0;   //Retour au menu
            }
        }
    }
}





/*---------------------------------------------------------------------------*/
/* FONCTIONS DE GESTION DU TERMINAL */
/*---------------------------------------------------------------------------*/

/*****************************************/
/*  POSITIONNEMENT DU CURSEUR SUR L'ECRAN
    x est la colonne et y est la ligne   */
/*****************************************/
void gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

/************************************************************/
/*  Choix des couleurs de la police et de la fenêtre CONSOLE
    cT correspond à la couleur du texte
    cF correspond à la couleur de fond
    Codes couleurs :
        0: noir
        1: bleu foncé
        2: vert
        3: bleu-gris
        4: marron
        5: pourpre
        6: kaki
        7: gris clair
        8: gris
        9: bleu
        10: vert fluo
        11: turquoise
        12: rouge
        13: rose fluo
        14: jaune fluo
        15: blanc               */
/************************************************************/
void color(int cT,int cF)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,cF*16+cT);
}

