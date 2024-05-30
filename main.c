#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "synchro_list.h"
#include "copy_list.h"


int main() {
    FILE *updateListFile = fopen("listCopy.txt", "r");
    if (!updateListFile) {
        perror("Erreur lors de l'ouverture du fichier de liste");
        return 1;
    }

    checkAndCopyFiles(updateListFile);

    fclose(updateListFile);
    return 0;
}  /*
    if (pipe(pipe_fd) == -1) {
        perror("Erreur lors de la création du pipe.");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) > 0) {
        close(pipe_fd[0]); // Fermer le descripteur de fichier de lecture dans le processus parent
        writeFileNames();
        pipeSendList(pipe_fd);
        wait(NULL);
    } else if (pid == 0) {
        close(pipe_fd[1]); // Fermer le descripteur de fichier d'écriture dans le processus enfant
        pipeReceiveList(pipe_fd);
    } else {
        perror("Erreur lors de la création du processus.");
        exit(EXIT_FAILURE);
    }
    */