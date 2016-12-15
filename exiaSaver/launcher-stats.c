#include <stdio.h>
#include <stdlib.h>

int launcher_menuStats();
void launcher_affichHisto();
void launcher_calculStats ();

int main(int argc, char const *argv[])
{
	int launcher_choixUser=launcher_menuStats();	
	//printf("%d\n", launcher_choixUser);

	switch (launcher_choixUser){																//execute selon le choix de l'utilisateur
		case 1:
			launcher_calculStats();
			break;
		case 2:
			launcher_affichHisto();
			break;
		default:
			printf("Erreur de saisie\n");
			break;
	}

	return 0;
}

int launcher_menuStats (){																		//enonce les différentes option du menu
	int launcher_choixUser = 0;
	printf("1 : Calcul des statistiques.\n");
	printf("2 : Afficher l'historique par ordre chronologique.\n");
	printf("Veuillez entrer le numero correspondant a l'action que vous souhaitez:");	
	scanf("%d", &launcher_choixUser);															//releve le choix fait par l'utilisateur

	return(launcher_choixUser);
}

void launcher_affichHisto(){																	//affiche l'historique trié selon l'ordre chronoligique soit le fichier comme il est écrit initialement
	FILE* historique=NULL;
	char caractereActuel;
	historique=fopen("historique.txt","r");

	if (historique!=NULL)
	{
		
	    do
	    {
	        caractereActuel = fgetc(historique);                                                // On lit le caractère
	        printf("%c", caractereActuel); 														// On l'affiche
	    } while (caractereActuel != EOF); 														// On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
	}
	else {
		printf("Erreur lors de l'ouverture du fichier.\n");
	}

	fclose(historique);

}

void launcher_calculStats (){
	FILE* historique=NULL;
	char caractereActuel;
	char typeEcran;
	float totalEcran=0.0;
	int totalStatique=0;
	int totalDyn=0;
	int totalInteract=0;
	float tauxStatique=0.0;
	float tauxDyn=0.0;
	float tauxInteract=0.0;

		historique=fopen("historique.txt","r");													// ouvre le fichier historique
	if (historique!=NULL)																		// si l'historique n'est pas vide
	{
		
	    do
	    {
	    	do
	    	{
	    		
	   			caractereActuel = fgetc(historique);
    	    	
	     	} while (caractereActuel != ';');

	     	typeEcran = fgetc (historique);

	     	do
	    	{
	    		
	   			caractereActuel = fgetc(historique);
    	    	
	     	} while (caractereActuel != '\n');

	     	//printf("%c", typeEcran);
	     	totalEcran++;																		//releve le nombre d'écran total
	     	//printf(" %f\n", totalEcran);
	     	switch(typeEcran){
	     		case '1':
	     			totalStatique++;															//stats du statique
	     			break;
	     		case '2':
	     			totalDyn++;																	//stats du dynamique
	     			break;
	     		case '3':
	     			totalInteract++;															//stats interactifs
	     			break;
	     		default:
	     			//printf("Erreur\n");
	     			break;
	     	}

	     caractereActuel = fgetc(historique);
	    } while (caractereActuel != EOF); 														// On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

	    //printf("%d\n",totalStatique);
	    //printf("%d\n",totalDyn);
	    //printf("%d\n",totalInteract);

	    tauxStatique=(totalStatique/totalEcran)*100.0;
	    tauxDyn=(totalDyn/totalEcran)*100.0;
	    tauxInteract=(totalInteract/totalEcran)*100.0;

	    printf("%.2f %%\n", tauxStatique);														//affiche les statistiques
	    printf("%.2f %%\n", tauxDyn);
	    printf("%.2f %%\n", tauxInteract);

	}
	else {
		printf("Erreur lors de l'ouverture du fichier.\n");										//erreur si le fichier est vide
	}

	fclose(historique);
}