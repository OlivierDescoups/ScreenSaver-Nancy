#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void global_creationEtRemplissageTbl (int v,int w);

int main(void)
{
    char caractereActuel;
    char largeur[3];
    char hauteur[4];

    int largeurInt;
    int hauteurInt;
 
    FILE* fichier = fopen("img1.pbm", "r");
 
    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
            caractereActuel = fgetc(fichier); // On lit le caractère
        } while (caractereActuel != '\n'); // On continue tant que fgetc n'a pas retourné \n (saut de ligne)
 		
        fgets (largeur,3,fichier);
        //fseek(fichier,1,SEEK_CUR);
        fgets (hauteur,4,fichier);

        //printf("largeur=%s & hauteur=%s\n", largeur,hauteur);

        largeurInt = atoi (largeur);
        hauteurInt = atoi (hauteur);

        printf("%d&%d\n",largeurInt,hauteurInt );

        fclose(fichier);

        global_creationEtRemplissageTbl(largeurInt,hauteurInt);
    }
 
    return 0;
}



void global_creationEtRemplissageTbl (int largeur,int hauteur)
{
    int i, j;
    char **tab;
    char caractereActuel;
    char caractereImage = 'W';
    int blanc=254;
    int noir=255;


    tab = malloc((largeur+1) * sizeof(char*));             // allocation mémoire tableau
    for (i = 0 ; i < largeur ; i++)
    {
        tab[i] = malloc((hauteur+1) * sizeof(char));
    }


    FILE* fichier = fopen("img1.pbm", "r");

    for (int a = 0; a < 2; ++a)
    {
                           
        do
        {
            caractereActuel = fgetc(fichier); // On lit le caractère
        } while (caractereActuel != '\n'); // On continue tant que fgetc n'a pas retourné \n (saut de ligne)

    }

    for (i = 0; i < largeur+1; ++i)                     // écriture tableau
    {
        for (j = 0; j < hauteur+1; ++j)
        {
            
            caractereImage = fgetc (fichier);

            if (caractereImage == '0'){
                tab[i][j]=noir;
            }

            else if (caractereImage=='1')
            {
                tab[i][j]=blanc;
            }
            else if (caractereImage==' '){
                j--;
            }
          

        }

    }
    fclose(fichier);

    for (i = 0; i < largeur; ++i)                     // affichage tableau
    {
        for (j = 0; j < hauteur; ++j)
        {
            printf("%c",tab[i][j] );

        }
        printf("\n");
    }

}