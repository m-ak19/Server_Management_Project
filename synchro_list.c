#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include "synchro_list.h"

#define MSG_SIZE 128
#define FILENAME_LENGTH 256

char* ProdServList = "listProduction.txt";
char* BackupServList = "listBackup.txt";


int synchroniseLists(){

    char buffer[MSG_SIZE], cpy[] ="Production/", concat[200], date[10];
    int p[2], pid, nbytes;
    struct stat attribute;


    struct dirent *entree;
    DIR *dossier = opendir("Production");

    if (dossier == NULL) {
        perror("Erreur lors de l'ouverture du dossier.");
        exit(1);
    }

    FILE* fichier = fopen(ProdServList, "w+");
    fichier = fopen(ProdServList, "a+");

    while ((entree = readdir(dossier)) != NULL) {
        if (entree->d_name[0] != '.') {
            strcpy(concat, cpy);
            strcat(concat, entree->d_name);
            stat(concat, &attribute);
            //printf("%s\n", entree->d_name);
                if(fichier != NULL)
                {
                    // while((character = fgetc(fichier)) != EOF)
                    // {
                        // fputc(character, fichier);
                    // }
                    fputs(entree->d_name, fichier);
                    fputs(" - ", fichier);
                    strftime(date, 10, "%d/%m/%y", localtime(&(attribute.st_ctime)));
                    fputs(date, fichier);
                    strftime(date, 10, "%T", localtime(&(attribute.st_ctime)));
                    fputs(" - ", fichier);
                    fputs(date, fichier);   
                    fputc('\n', fichier);
                }
        }
    }
    fclose(fichier);
    closedir(dossier);
    

    if(pipe(p) < 0){
        printf("ERROR DURING PIPE CREATION");
        exit(1);
    }

    if((pid = fork()) > 0){
        close(p[0]);
        FILE* fichier = fopen(ProdServList, "r");
        char actualCharacter = '~';
        int i = 0;
        if (fichier == NULL)
        {
            printf("ERREUR: Impossible d'ouvrir le fichier.\n");
            close(p[1]);
            exit(1);
        }

        while((actualCharacter = fgetc(fichier)) != EOF)
        {
            i = 0;
            while(actualCharacter != '\n' && actualCharacter != EOF)
            {
                buffer[i] = actualCharacter;
                i++;
                actualCharacter = fgetc(fichier);
            }
            buffer[i] = '\0';
            write(p[1], buffer, MSG_SIZE);
        }
        close(p[1]); 
        wait(NULL);
    }

    else { 
            close(p[1]);
            FILE* fichier = fopen(BackupServList, "w+");
            while ((nbytes = read(p[0], buffer, MSG_SIZE)) > 0){
                fichier = fopen(BackupServList, "a+");
                if(fichier != NULL)
                {
                    // while((character = fgetc(fichier)) != EOF)
                    // {
                        // fputc(character, fichier);
                    // }
                    fputs(buffer, fichier);
                    fputc('\n', fichier);
                    printf("Buffer: %s\n", buffer);
                    fclose(fichier);
                }
            }
            close(p[0]); 
            exit(EXIT_SUCCESS);
            if (nbytes == 0){ 
                exit(2);
            } 
            printf("Finished reading\n"); 
    } 
    return 1;
}