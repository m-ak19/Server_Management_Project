#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define MAX_NOM_FICHIER 256
#define INTEGRATION_LIST "listCopy.txt"
#define ENVOI_DIRECTORY "Production/"
#define RECEPTION_DIRECTORY "Integration/"

void extractDateTime(const char *dateStr, struct tm *tm) {
    sscanf(dateStr, "%d/%d/%d - %d:%d:%d",
           &tm->tm_mday, &tm->tm_mon, &tm->tm_year,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);
    tm->tm_mon -= 1;  
    tm->tm_year -= 1900;  
}

void copyFile(const char *srcPath, const char *destPath) {
    FILE *srcFile = fopen(srcPath, "rb");
    if (!srcFile) {
        perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    FILE *destFile = fopen(destPath, "wb");
    if (!destFile) {
        perror("Erreur lors de l'ouverture du fichier de destination");
        fclose(srcFile);
        return;
    }

    char buffer[BUFSIZ];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

void checkAndCopyFiles(FILE *updateListFile) {
    char line[512];
    char fileName[MAX_NOM_FICHIER];
    char dateStr[30];
    struct stat fileStat;
    struct tm listTime, fileTime;

    while (fgets(line, sizeof(line), updateListFile) != NULL) {
        char fileLine[256];
        if (sscanf(line, "%[^-] - %[^\n]", fileLine, dateStr) != 2) {
            fprintf(stderr, "Format de ligne incorrect : %s\n", line);
            continue;
        }

        char *startPtr = fileLine;
        while (*startPtr == ' ') startPtr++;
        char *endPtr = startPtr + strlen(startPtr) - 1;
        while (*endPtr == ' ') endPtr--;
        *(endPtr + 1) = '\0';
        strcpy(fileName, startPtr);

        char srcPath[MAX_NOM_FICHIER * 2];
        char destPath[MAX_NOM_FICHIER * 2];
        snprintf(srcPath, sizeof(srcPath), "%s%s", ENVOI_DIRECTORY, fileName);
        snprintf(destPath, sizeof(destPath), "%s%s", RECEPTION_DIRECTORY, fileName);

        if (stat(destPath, &fileStat) == 0) {
            localtime_r(&fileStat.st_mtime, &fileTime);
            extractDateTime(dateStr, &listTime);

            if (difftime(mktime(&fileTime), mktime(&listTime)) != 0) {
                copyFile(srcPath, destPath);
            }
        } else {
            copyFile(srcPath, destPath);
        }
    }
}









/*
#define MAX_NOM_FICHIER 100

void lire_noms_fichiers(const char *nom_fichier) {
    FILE *file;
    char ligne[256]; // Taille maximale d'une ligne
    char nom_fichier_buffer[MAX_NOM_FICHIER]; // Buffer pour stocker le nom du fichier

    // Ouvrir le fichier en mode lecture
    file = fopen(nom_fichier, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lire le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), file) != NULL) {
        // Utiliser strtok pour séparer la ligne par " - "
        char *nom = strtok(ligne, " - ");
        // Copier le nom du fichier dans le buffer
        if (nom != NULL) {
            strncpy(nom_fichier_buffer, nom, MAX_NOM_FICHIER);
            nom_fichier_buffer[MAX_NOM_FICHIER - 1] = '\0'; // Assurer la terminaison de la chaîne
            printf("%s\n", nom_fichier_buffer); // Afficher le nom du fichier
        }
    }
}

void getCopiedFileNames(){

	FILE* updateListFile = fopen(integrationList, "r+");

    char *nom, concat[200], *ligne, *temp, *search , buffer[MAX_NOM_FICHIER], *date;
    struct stat attribute;
    struct dirent *entree;
    DIR *dossier = opendir(integrationDirectory);

    ligne = (char*)malloc(256*sizeof(char));
    search = (char*)malloc(5*sizeof(char));
    nom = (char*)malloc(256*sizeof(char));
    date = (char*)malloc(30*sizeof(char));
    temp = (char*)malloc(256*sizeof(char));

    if (dossier == NULL) {
        perror("Erreur lors de l'ouverture du dossier.");
        exit(1);
    }
    // A CHANGER
    while (fgets(ligne, sizeof(ligne), updateListFile) != NULL) 
    {
        //strcpy(temp, ligne);
        search = "- ";


        temp = strstr(ligne, search);
        date = temp + 1;
        size_t length = ligne - temp;
        strncpy(nom, temp, length);

        printf("Nom:%s\nDate:%s\n", nom, date);
        while ((entree = readdir(dossier)) != NULL) 
	    {
            if (entree->d_name[0] != '.') 
	    	{
                if((strcmp(entree->d_name, nom)) == 0)
                {

                }
                else
                {
                    break;
                }
	    	}
	    }

    }

}
*/
/*


        strcpy(temp, ligne);
        char* nom = strtok(temp, " - ");
        //char* date = strtok();





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

*/

