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

char* ServList = "listCopy.txt";
char* IntegrationServList = "listIntegration.txt";
char* cpy = "Production/";
char* directory = "Production";

void writeFileNames(){

    char concat[200], date[50];
    struct stat attribute;


    struct dirent *directoryGetter;
    DIR *dossier = opendir(directory);

    if (dossier == NULL) {
        perror("Erreur lors de l'ouverture du dossier.");
        exit(1);
    }

    FILE* fichier = fopen(ServList, "w+");
    fichier = fopen(ServList, "a+");

    while ((directoryGetter = readdir(dossier)) != NULL) {
        if (directoryGetter->d_name[0] != '.') {
            strcpy(concat, cpy);
            strcat(concat, directoryGetter->d_name);
            stat(concat, &attribute);
            //printf("%s\n", directoryGetter->d_name);
                if(fichier != NULL)
                {
                    // while((character = fgetc(fichier)) != EOF)
                    // {
                        // fputc(character, fichier);
                    // }
                    fputs(directoryGetter->d_name, fichier);
                    fputs(" - ", fichier);
                    strftime(date, 50, "%d/%m/%Y - %T", localtime(&(attribute.st_ctime)));
                    fputs(date, fichier);
                    fputc('\n', fichier);
                }
        }
    }
    fclose(fichier);
    closedir(dossier);
}

void pipeSendList(int p_fd[]){
    char buffer[MSG_SIZE];
    int i;

    close(p_fd[0]);
    FILE* fichier = fopen(ServList, "r");
    char actualCharacter = '~';
    if (fichier == NULL)
    {
        printf("ERREUR: Impossible d'ouvrir le fichier.\n");
        close(p_fd[1]);
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
        write(p_fd[1], buffer, MSG_SIZE);
    }
    close(p_fd[1]); 


}

void pipeReceiveList(int p_fd[]){
    char buffer[MSG_SIZE];
    int nbytes;


    close(p_fd[1]);
    FILE* fichier = fopen(IntegrationServList, "w+");
    while ((nbytes = read(p_fd[0], buffer, MSG_SIZE)) > 0){
        fichier = fopen(IntegrationServList, "a+");
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
    close(p_fd[0]); 
    exit(EXIT_SUCCESS);
    if (nbytes == 0){ 
        exit(2);
    } 
    printf("Finished reading\n"); 
}