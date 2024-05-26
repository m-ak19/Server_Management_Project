#include "stat.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int getNombreLigne(char* nom_fichier){
    int nbLigne = 0;
    char c;
    FILE *fichier = fopen(nom_fichier, "r");
    
    if(fichier==NULL){
        printf("Problème lors de l'ouverture du fichier %s\n",nom_fichier);
        return -1;
    }

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            nbLigne++;
        }
    }

    fclose(fichier);
    return nbLigne;
}

int getNombreErreur(char* nom_fichier){
    int nbErreur=getNombreLigne(nom_fichier);
    printf("Il y a %d erreurs dans le fichier %s!\n",nbErreur,nom_fichier);
    return nbErreur;
}

int getNombreFichierRecus(char* nom_fichier){
    int nbFichierRecus=getNombreLigne(nom_fichier);
    printf("%d fichiers ont été reçus dans %s\n",nbFichierRecus,nom_fichier);
    return nbFichierRecus;
}

int ecrire_fin_fichier_stat(char* texte_a_ecrire, char* nom_fichier){

    time_t now;
    struct tm *date_heure_actuelles;
    char date_heure[100];

    now = time(NULL);
    date_heure_actuelles = localtime(&now);

    strftime(date_heure, sizeof(date_heure), "%d-%m-%Y, %H:%M:%S --> ", date_heure_actuelles);

    FILE *fichier = fopen(nom_fichier, "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n",nom_fichier);
        return -1; 
    }

    fputs(date_heure, fichier);
    fputs(texte_a_ecrire, fichier);
    fputs("\n", fichier);
    fclose(fichier);
    return 0;
}
