#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int SaveInlog(const char *Nomfichier, char *data){
    FILE* fichier = NULL;
    time_t temps_actuel;

    // Obtenir le temps actuel
    temps_actuel = time(NULL);

    fichier = fopen(Nomfichier, "a+");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture de fichier\n");
        return EXIT_FAILURE;
    }

    // Récupérer la date de modification du fichier
    char dateTimeString[128];
    struct tm *modificationTime = localtime(&temps_actuel);
    strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", modificationTime);

    fprintf(fichier, "--- %s:\t%s\n",dateTimeString,data);


    fclose(fichier);

    return EXIT_SUCCESS;
}