#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


int e_arg_stats(const char* arg){
	int i=0;
	const char* stat="-stats";
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

pid_t e_create_process(){
	
	pid_t pid;

	do{
		pid = fork();
	}while ((pid==-1) && (errno == EAGAIN));


	return pid;
}



int main(int argc, char const *argv[]){

	system("clear");
	if (argc==2){  //si il y a un seul argument, verifier s'il s'agit de -stats
		char e_arg[6];
		strcpy(e_arg, argv[1]);
		if (e_arg_stats(e_arg)==1){
		char *arg[]={NULL};
 		execv("stat",arg); //lancer les stats
 			return 1;
		}
		else{
			return 2;
		}
	}

	if (argc>2){
		return 3;
	}

	int e_rand_prgm;

	srand(time(NULL));                         															   //initialise rand()
	e_rand_prgm=(rand()%3)+1;             						    //Permet d'avoir un nombre aléatoire entre 0 et 3(exclu)

												//DEBUG



	time_t secondes;							//creer variable
	struct tm instant;
	time(&secondes);
	instant=*localtime(&secondes);


	FILE* e_fichier_historique = NULL;																		   // creer le poiteur du fichier


		while(e_fichier_historique==NULL){
	    e_fichier_historique= fopen("historique.txt", "a");													// recuperer le fichier
		}

	    if ( e_fichier_historique != NULL )

	    {
	         fprintf(e_fichier_historique,"%d/%d/2016 %d:%d:%d;%d;",instant.tm_mday+1, instant.tm_mon+1, instant.tm_hour, instant.tm_min, instant.tm_sec, e_rand_prgm); //ecrire
	     }



	char e_interactif_char1[2]={'\0'};
	char e_interactif_char2[2]={'\0'};
	char e_char_to_add[6]={'\0'};

	switch (e_rand_prgm){                                     // Dois réaliser les lectures du .profile necessaire, 

		case 1:
		// e_statique_()

		srand(time(NULL));
		int e_i = rand()%4;
		sprintf(e_char_to_add,"%d",e_i  );
		//transforme entier en string
		strcat(e_char_to_add, ".pbm");    // Ajoute ".pbm" à la fin
		break;

		case 2:

		
		strcpy(e_char_to_add,getenv("EXIASAVER2_TAILLE"));


		break;

		case 3:

		while(0);   //evite un conflite entre case et une declaration de variable

		int e_interactif_int1=(rand()%74)+1;
		int e_interactif_int2=(rand()%17)+1;

		sprintf(e_interactif_char1,"%dx",e_interactif_int1);
		sprintf(e_interactif_char2,"%d",e_interactif_int2);

		strcpy(e_char_to_add,e_interactif_char1);
		strcat(e_char_to_add,e_interactif_char2);

		break;

		default :
		printf("ERREUR : ecran inconnu\n");
		return 1;
	}



	fprintf(e_fichier_historique,"%s\n",e_char_to_add);




	     


// ------------------------------------------AJOUTER LES AUTRES VARIABLES À ENRIGSTRER-----------------------------------------------



	fclose(e_fichier_historique);


	char e_chemin[100]={'\0'};



	switch (e_rand_prgm){  //lance les termsaver

		case 1:

		
		

		strcpy(e_chemin,getenv("EXIASAVER_HOME"));
		strcat(e_chemin,"termsaver_statique");

		char *arg1[]={"termsaver",e_char_to_add,NULL};
 		execv(e_chemin,arg1);

		//
		break;

		case 2:

		strcpy(e_chemin,getenv("EXIASAVER_HOME"));
		strcat(e_chemin,"termsaver_dynamique");

		char *arg2[]={NULL};
 		execv(e_chemin,arg2);

		break;

		case 3:

		strcpy(e_chemin,getenv("EXIASAVER_HOME"));
		strcat(e_chemin,"termsaver_interactif");

		char *arg3[]={"termsaver_interactif",e_interactif_char1,e_interactif_char2,NULL};
 		execv(e_chemin,arg3);



		break;

		default :
		printf("ERREUR : type d'ecran inconnu\n");
		return 2;




	}


	return 0;
}