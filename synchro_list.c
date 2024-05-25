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


void getFileNames(){

    char cpy[] ="Production/", concat[200], date[10];
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
}

void pipeSendList(int pipe_fd[]){
    char buffer[MSG_SIZE];
    int i;

    close(pipe_fd[0]);
    FILE* fichier = fopen(ProdServList, "r");
    char actualCharacter = '~';
    if (fichier == NULL)
    {
        printf("ERREUR: Impossible d'ouvrir le fichier.\n");
        close(pipe_fd[1]);
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
        write(pipe_fd[1], buffer, MSG_SIZE);
    }
    close(pipe_fd[1]); 


}

void pipeReceiveList(int pipe_fd[]){
    char buffer[MSG_SIZE];
    int nbytes;


    close(pipe_fd[1]);
    FILE* fichier = fopen(BackupServList, "w+");
    while ((nbytes = read(pipe_fd[0], buffer, MSG_SIZE)) > 0){
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
    close(pipe_fd[0]); 
    exit(EXIT_SUCCESS);
    if (nbytes == 0){ 
        exit(2);
    } 
    printf("Finished reading\n"); 
}