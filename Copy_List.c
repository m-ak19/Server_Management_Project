
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


sem_t sInteg, sProd, sBackup, ressourceProd, sTestServer;
pthread_t integ, backup, prod; //threads représentant les 3 serveurs
int serveur;
int nbErreur = 0, nbCommEnvoyes = 0, nbCommProd = 0, nbCommBackup = 0; //variables globales qui nous sert pour les statistiques

void copyList(){
	FILE * fileProd =  fopen("logProd.txt", "r+");
	FILE * fileBackup = fopen("logBackup.txt", "r+");
	int c=0;
	int semVal;
	sem_getvalue(&ressourceProd, &semVal);
	if (serveur==1) {
		//copy de Prod à Backup
    while((c = fgetc(fileProd) ) != EOF)
    {
        fputc(c, fileBackup);
    }

		fclose(fileProd);
		fclose(fileBackup);
		printf("La synchronisation des logs du serveur Production vers le serveur Backup a bien été effectuée !\n");

	} else {
		//copy de Backup à Prod
    while ((c = fgetc(fileBackup) ) != EOF)
    {
        fputc(c, fileProd);
    }
		fclose(fileProd);
		fclose(fileBackup);
		printf("La synchronisation des logs du serveur Backup vers le serveur Production a bien été effectuée !\n");

	}
}

