#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ncurses.h>


pid_t d_create_process(){
	
	pid_t pid;

	do{
		pid = fork(); //creer un processus fils
	}while ((pid==-1) && (errno == EAGAIN));


	return pid;
}


int d_str_pbm(const char* arg){
	int i=0;
	const char* stat=".pbm";
    if( strlen(arg) != strlen(stat) ){  //on verifie la taille
        return 0;
    }
    for(i=0;i<strlen(arg);i++){			//on verifie caractère par caractère
        if( arg[i] != stat[i]){
            return 0;
        }
    }
    return 1;


}







int d_afficher_chiffres(int d_taille,char *d_img_chemin,int d_arg_N){


		time_t secondes;							//creer variable du tps
		struct tm instant;
		time(&secondes);
		instant=*localtime(&secondes);



		char d_heure_cara[8]={'\0'};

		sprintf(d_heure_cara,"%d:%d:%d",instant.tm_hour, instant.tm_min, instant.tm_sec); // trnasformer les differents int du temps en string



		pid_t pid = d_create_process(); 



					
		switch (pid){																	// FORK

		case -1:										
		perror("fork");
		return EXIT_FAILURE;
		break;

		case 0:	//--------------------------------------------------------LECTURE ECRITURE (FILS)--------------------------------------------------------------------
		clear();




		int d_ligne=(LINES-(d_taille*2-1))/2;					//On place des variables pour coordonées, elles permettentd'avoir un affichage relatif à la taille.
		int d_colone=(COLS-(8*d_taille+3))/2;



		int d_cara_compteur = 0;								//on creer les variable pour la boucle for des 8 caracteres, plus des string pour chaque image et le chemin d'acces
		char d_caractere_affich=0;
		char d_caractere_affich_str[5]={'\0'};
		char d_img_chemin_2[200]={'\0'};

		for (; d_cara_compteur<8;d_cara_compteur++){

			d_caractere_affich=0;
			memset(d_caractere_affich_str,0,strlen(d_caractere_affich_str)); //on reinitialize la suite de char du nom du fichier

			d_caractere_affich=d_heure_cara[d_cara_compteur];
			

		

			d_caractere_affich_str[0]=d_caractere_affich;
			strcat(d_caractere_affich_str,".pbm");							//on transforme le caractere du chiffre ou des : en .pbm pour les lire

			if (d_str_pbm(d_caractere_affich_str)==1){
				strcpy(d_caractere_affich_str,"b.pbm"); }					//si les derniers caracteres sont vides, on affiche un blanc

			

			strcpy(d_img_chemin_2,d_img_chemin);
			
			strcat(d_img_chemin_2,d_caractere_affich_str);					//on creer le chemin en entier de l'image (chemin+nom)



			FILE* d_fichier_point = NULL;									

			d_fichier_point = fopen(d_img_chemin_2,"r");					//on ouvre le fichier

			int d_compteur_ligne=0;
			rewind(d_fichier_point);

			fseek(d_fichier_point,7,SEEK_CUR);								//on place le curseur dans le  fichier au début des 0 et des 1

			int d_cpt_i=0;
			int d_cpt_j=0;
			char d_car_a;


			//if (d_taille==3){												//Taille 5x3
				for (;d_cpt_i<5;d_cpt_i++){									//deplacement en hauteur du curseur fichier et ncurses
				d_cpt_j=0;
				for (;d_cpt_j<3;d_cpt_j++){									//deplacement en largeur
					move(d_ligne,d_colone);									//positionement du curseur
					d_car_a=fgetc(d_fichier_point);							//lecture du fichier
					if(d_car_a=='1'){										//si 1, afficher un carré noir
						addch(219);
					}
					fseek(d_fichier_point,1,SEEK_CUR);						
					d_colone++;
				}
				d_colone=d_colone-3;
				d_ligne=d_ligne+1;
			}

			d_colone=d_colone+4;
			d_ligne=d_ligne-5;
			fclose(d_fichier_point);
			}
			
		
			/*else{								//Taille 11x6
				for(;d_cpt_i<5;d_cpt_i++){
				d_cpt_j=0;
					for (;d_cpt_j<3;d_cpt_j++){
					move(d_ligne,d_colone);
					d_car_a=fgetc(d_fichier_point);
					if(d_car_a=='1'){
						addch('X');
						d_colone++;
						move(d_ligne,d_colone);
						addch('X');
						d_ligne++;
						move(d_ligne,d_colone);
						addch('X');
						d_colone--;
						move(d_ligne,d_colone);
						addch('X');
					}
					fseek(d_fichier_point,1,SEEK_CUR);
					d_colone=d_colone+2;
					d_ligne--;
				}
				d_colone=d_colone-6;
				d_ligne=d_ligne+2;

				//afficher 11x6
				}
				d_colone=d_colone+7;
				d_ligne=d_ligne-10;
			}*/

			









			



		
	
		
		move(LINES-1,1);
		printw("Cet écran sera actualisé dans quelques secondes");
		int d_cpt_N=0;
		refresh();													//affichage de l'écran

		for (d_cpt_N=0;d_cpt_N<d_arg_N;d_cpt_N++){					//affichage des points
			printw(".");
			sleep(1);
			refresh();
		}
	
		clear();
		endwin(); //DEBUG

		break;//------------------------------------------------------------------------------------------------------------------------------------------------------

		default:
		wait(NULL);

		break;
		

	}
	return 0;
}








int main(int argc, char const *argv[],char *envp[])
{


	int d_taille;							//defini la variable de la taille (largeur; longueur = largeurx2 -1) //s'il y a un seul argument et qu'il correspond au format 3 ou 4 caractères, 
	char d_taille_char[3];								//alors il est analysé, sinon la taille est 5x3
	char* d_taille_char_x;								//défini les varables : 1 pour copier l'argument, 2 pour les coordonnées en string, 2 pour les coordonnées en long.
	char* d_taille_char_y;									
	char *d_ptr;

	long d_taille_long_x;
	long d_taille_long_y;

	if(getenv("EXIASAVER2_TAILLE")!=NULL){
	strcpy(d_taille_char, getenv("EXIASAVER2_TAILLE"));					//copie l'argument
	}
	else{
		strcpy(d_taille_char, "5x3");
	}

	d_taille_char_y=strtok(d_taille_char,"x");	//on coupe en 2 parties la chaine de base. Ces deux parties restes des string, uniquement composés de chiffres
	d_taille_char_x=strtok(NULL,"x");

	

	d_taille_long_x=strtol(d_taille_char_x,&d_ptr,10); //on convertie les 2 parties de string en long int
	d_taille_long_y=strtol(d_taille_char_y,&d_ptr,10);

	int d_taille_x=d_taille_long_x;//on convertie les 2 long int en int
	int d_taille_y=d_taille_long_y;
	

	if (d_taille_y==((2*d_taille_x)-1) && d_taille_x<10 && d_taille_x>2){ //on verifie qu'il y a bien x*2-1;x sinon 5x3
		d_taille=d_taille_x;
	}
	else{
		d_taille=3;
	}




	if (2<d_taille && d_taille<5){  					//arondi à la taille 3 ceux autour 
		d_taille=3;										//Les arrondis permettent de n'avoir que 2 tailles à afficher
														//il y a la taille 3 et 6, signifiant que la largeur (le "bas", l'abscisse) est à 3 ou 6
	}													// et la longueur est à X*2-1, soit 5 ou 11.
	if (4<d_taille && d_taille<10){						//arrondi à la taille 6 ceux autour
		d_taille=6;

	}
	

	char d_img_chemin[200];								//permet de ne pas avoir d'allocation dynamique pour eviter toute fuite de mémoire
	strcpy(d_img_chemin,getenv("EXIASAVER2_PBM"));						//on recupere le chemin en argument du lanceur			




	initscr();															//debut du lncurses

	char *d_ptr_2;
	int d_arg_N;

	if (getenv("EXIASAVER2_SLEEP")==NULL){
		d_arg_N=10;
	}
	d_arg_N=strtol(getenv("EXIASAVER2_SLEEP"),&d_ptr_2,10);			//on recupere la valeur N d'attente avec les points


	while (1){															//boucle infinie, le seul moyen de quitter est donc ctrl+c , le signal kill

		d_afficher_chiffres(d_taille,d_img_chemin,d_arg_N);				//fonction majeure, elle permet d'afficher l'heure sur le terminal
	}







	return 0;
	}



	/*pid_t pid = d_create_process();

	switch (pid){

		case -1:
		perror("fork");
		return EXIT_FAILURE;
		break;

		case 0:
		printf("lecture\n");


		break;

		default:
		(wait(NULL)
		break;
		}*/