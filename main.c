#include "copy_list.h"
#include "synchro_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

pid_t testDisponibilite() {
    return rand() % 2 == 0 ? 1 : 0;
}

void sync_directories() {
    const char *cmd = "rsync -avz --delete Production/ Backup/ && rsync -avz --delete Backup/ Production/";
    system(cmd);
}

int main(void) {
    int pid_production, pid_backup;
    int p_fd[2], res = 1;
    sync_directories();

    FILE *updateListFile = fopen("listCopy.txt", "r");
    if (!updateListFile) {
        perror("Erreur lors de l'ouverture du fichier de liste");
        return 1;
    }

        if (pipe(p_fd) == -1) {
        perror("Erreur lors de la création du pipe.");
        exit(EXIT_FAILURE);
    }

    printf("Processus d'Intégration démarré\n");


if (res == 1) {

        if ((pid_production = fork()) > 0) {
        getFileNames();
        pipeSendList(p_fd);
        wait(NULL);
    } else if (pid_production == 0) {
        printf("Access to this\n");
        pipeReceiveList(p_fd); // Recevoir la liste des enfants
        checkAndCopyFiles(updateListFile); // Mettre à jour la liste du parent
        fclose(updateListFile);
    } else {
        perror("Erreur lors de la création du processus.");
        exit(EXIT_FAILURE);
    }
}else {        
    if ((pid_backup = fork()) > 0) {
        getFileNames();
        pipeSendList(p_fd);
        wait(NULL);
    } else if (pid_backup == 0) {
        printf("Access to this\n");
        pipeReceiveList(p_fd); // Recevoir la liste des enfants
        checkAndCopyFiles(updateListFile); // Mettre à jour la liste du parent
        fclose(updateListFile);
    } else {
        perror("Erreur lors de la création du processus.");
        exit(EXIT_FAILURE);
    }
    }


    printf("Tous les processus sont terminés\n");

    return 0;
}

/*

        if ((res = fork()) > 0) {
        getFileNames();
        pipeSendList(p_fd);
        wait(NULL);
    } else if (res == 0) {
        printf("TEST TEST\n");
        pipeReceiveList(p_fd);
    } else {
        perror("Erreur lors de la création du processus.");
        exit(EXIT_FAILURE);
    }

    if (res == 1) {
        pid_production = fork();
        printf("Processus de Production démarré\n");
        pipeSendList(p_fd); 
        wait(NULL); // Attendre la fin des processus enfants
    }else {
        pid_backup = fork();
        printf("Processus de Backup démarré\n");
        pipeSendList(p_fd);
        wait(NULL); // Attendre la fin des processus enfants
    }

    pipeReceiveList(p_fd); // Recevoir la liste des enfants
    checkAndCopyFiles(updateListFile); // Mettre à jour la liste du parent
    fclose(updateListFile);

    printf("Tous les processus sont terminés\n");

*/