#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc,char* argv[])
{


printf("\033[H\033[J");//vide la console
srand (time (NULL));

int compteur;// varible utilisé dans toutes les boucles comme compteur



int espace_h;
int espace_v;
int angle;
int espace_v2;
char *pbr;
char *pbr2;


espace_h = strtol(argv[1], &pbr,10);//récupére la variable aléatoire de la coordonée en x
espace_v = strtol(argv[2], &pbr2,10);//récupére la variable aléatoire de la coordonée en y
angle = rand() % 4 + 1;//choisis aléatoirement l'angle de départ de l'avoin








while(1){

espace_v2 = 18-espace_v;//définie la variable qui comble les derniéres lignes de la console

for (compteur = 0 ; compteur < espace_v ; compteur++)//place le point de départ en y
{
    printf("\n");
}

if     (angle == 1){


        for(compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");

        }




        printf("   X  \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("X   X \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("XXXXXX\n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("    X \n");


        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("   X \n");

        for(compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");

        }

        printf("      \n");

        }//affiche un avion différent en fonction de l'angle

else if(angle == 2){

        for(compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");

        }

        printf("   XX \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("   X  \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("   X  \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf(" X X X\n");


        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("  XXX \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("   X  \n");
        }

else if(angle == 3){

        for(compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");

        }

        printf("  X   \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf(" X   X\n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("XXXXXX\n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf(" X    \n");


        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("  X   \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("      \n");


        }

else if(angle == 4){

        for(compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");

        }

        printf("   X  \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("  XXX \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf(" X X X\n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("   X  \n");


        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }


        printf("   X  \n");

        for (compteur = 0 ; compteur < espace_h ; compteur++)
        {
        printf(" ");
        }

        printf("  XX  \n");


        }


for (compteur = 1 ; compteur < espace_v2 ; compteur++){

    printf("\n");
}//comble les derniéres lignes de la console

char commande;

commande=getchar();//recupere la commande utilisteur


printf("\033[2J\033[1;1H");//vide la console

if(commande == 'z'){//modifie les coordonée en fonction des commandes

espace_v--;
espace_v2++;
angle = 4;

}

if(commande == 's'){

espace_v++;
espace_v2--;
angle = 2;

}

if(commande == 'q'){

espace_h--;
angle = 3;

}

if(commande == 'd'){


angle = 1;

}

if(commande != ('8','4','6','0')){


    if(angle == 1){

        espace_h+=2;

    }

    if(angle == 2){

        espace_v+=2;
        espace_v2--;

    }

    if(angle == 3){

        espace_h-=2;

    }

    if(angle== 4){

        espace_v-=2;

    }


}



if(espace_v > 20){//empeche l'avion de sortir de la console

espace_v = 20;


}

if(espace_h > 74){

espace_h = 74;

}

if(espace_v < 0){


espace_v = 0;


}

if(espace_v2 < 1){


espace_v2 = 1;

}

if(espace_h < 0){

espace_h = 0;

}



if(commande == 'x'){//commande pour sortir du programme

return 0;

}
}


}
