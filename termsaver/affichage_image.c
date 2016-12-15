#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>


pid_t d_create_process(){
  
  pid_t pid;

  do{
    pid = fork();                                                             //creer un processus fils
  }while ((pid==-1) && (errno == EAGAIN));


  return pid;
}



void global_creationEtRemplissageTbl (int largeur,int hauteur,char*img)
{
 
  char **tab;                                                                 //defini le tableau
  char caractereActuel = 'a';
  char caractereImage = 'W';
  int blanc = 219;                                                            //defini les charactere ascii a utilisé pour le noir
  int noir = 255;                                                             //defini le charactere ascii a utilisé pour le blanc
  FILE *fichier = fopen(img, "r");                                            //ouvre le fichier de l'image
  



    

      tab = malloc((hauteur) * sizeof(char*));                                    // allocation mémoire tableau
  for (int i = 0 ; i < largeur ; i++)
    {
      tab[i] = malloc((largeur) * sizeof(char));
    }
    for (int i = 0; i < hauteur; ++i)
    {
        for (int j = 0; j < largeur; ++j)
        {
            tab[i][j]=0;
        }
    }

 
   for (int a = 0; a < 2; ++a)                                                //boucle pour lire les caracteres
    {
                           
        do
        {
            caractereActuel = fgetc(fichier);                                  // On lit le caractère
        } while (caractereActuel != '\n');                                     // On continue tant que fgetc n'a pas retourné \n (saut de ligne)

    }

    for (int i = 0; i < hauteur; ++i)                                          // écriture tableau selon la hauteur et la largeur
    {
        for (int j = 0; j < largeur; ++j)
        {
            
            caractereImage = fgetc (fichier);

            switch (caractereImage){                                           //affiche dans le tableau les caracteres ascii selon les 1 et les 0

                case '0':
                    tab[i][j]= noir;                                           
                    break;

                case '1':
                    tab[i][j]= blanc;
                    break;

                case ' ':
                    j--;
                    break;

                default:
                    tab[i][j]=' ';
                    break;
            }

   

        }
    }
    
  fclose(fichier);
  initscr();                                                                   //initialise l'écran de ncurse pour afficher le tableau
  int posline = LINES/2 - hauteur/2;                                           //Position curseur
  int poscol = COLS/2 - largeur/2;
  move(posline,poscol); 
    for (int i = 0;i < hauteur; ++i)                                           // affichage tableau selon ses parametres
    {
      for (int j = 0;j < largeur; ++j)
        {
          
          printw("%c", tab[i][j-1]);
          move(posline,poscol);                                                //déplace le tableau selon ses parametres et son positionnement
          poscol ++;
          
        }
    posline ++;                                                                //passe une ligne
    poscol = COLS/2 - largeur/2;                                               //positionne au milieu

    move(0,0);                                                                 //déplace le curseur en 0,0
    }
  refresh();
  getch();
  endwin();
}

int main(int argc,char *argv[])
{
  char caractereActuel;
  char largeur[3];
  char hauteur[4];
  int largeurInt;
  int hauteurInt;
    char arg[200];


  pid_t pid = d_create_process();

  switch (pid){                                                               //gere le fork

    case -1:
    perror("fork");
    return EXIT_FAILURE;
    break;

    case 0:


  strcpy(arg,getenv("EXIASAVER1_PBM"));                                     //genere l'arg qui prendra le nom du fichier
  strcat(arg,argv[1]);

  FILE* fichier = fopen(arg, "r");                                          //ouvre le fichier
  
  if (fichier != NULL)
    {
      // Boucle de lecture des caractères un à un
      do
        {
            caractereActuel = fgetc(fichier);                                // On lit le caractère
        }
      while (caractereActuel != '\n');                                       // On continue tant que fgetc n'a pas retourné \n (saut de ligne)
      fgets (largeur,3,fichier);
      fgets (hauteur,4,fichier);
      largeurInt = atoi (largeur)+1;
      hauteurInt = atoi (hauteur)+1;
      fclose(fichier); 
      global_creationEtRemplissageTbl(largeurInt, hauteurInt,arg);           //creation et remplissage du tableau
    }

    break;

    default:
    (wait(NULL));
    break;
    
  return 0;
}
}