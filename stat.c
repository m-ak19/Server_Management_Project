#include "stat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int getNombreFichierRecus(){
    int nbFichierRecus = 0;
    char c;
    FILE *fichier = fopen("stat.txt", "r");
    
    if(fichier==NULL){
        printf("Problème lors de l'ouverture du fichier stat\n");
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fichier)) {
        if (strncmp(line, "Fichier", 7) == 0) {
            nbFichierRecus++;
        }
    }

    fclose(fichier);
    return nbFichierRecus;
}

int getNombreErreur(){
    int nbErreurs = 0;
    char c;
    FILE *fichier = fopen("stat.txt", "r");
    
    if(fichier==NULL){
        printf("Problème lors de l'ouverture du fichier stat\n");
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fichier)) {
        if (strncmp(line, "Erreur", 6) == 0) {
            nbErreurs++;
        }
    }

    fclose(fichier);
    return nbErreurs;
}


void AffichNombreErreur(){
    printf("On compte %d erreurs jusqu'à maintenant!\n",getNombreErreur("stat.txt"));
}

void AffichNombreFichierRecus(){
    printf("%d fichiers ont été reçus.\n",getNombreFichierRecus("stat.txt"));
}

int ecrire_fichier_recu(char* nom_fichier_recu){

    time_t now;
    struct tm *date_heure_actuelles;
    char date_heure[100];

    now = time(NULL);
    date_heure_actuelles = localtime(&now);

    strftime(date_heure, sizeof(date_heure), "%d-%m-%Y, %H:%M:%S --> ", date_heure_actuelles);

    FILE *fichier = fopen("stat.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier stat\n");
        return -1; 
    }

    fputs("Fichier reçu: ", fichier);
    fputs(date_heure, fichier);
    fputs(nom_fichier_recu, fichier);
    fputs("\n", fichier);
    fclose(fichier);
    return 0;
}

int ecrire_erreur(char* erreur){

    time_t now;
    struct tm *date_heure_actuelles;
    char date_heure[100];

    now = time(NULL);
    date_heure_actuelles = localtime(&now);

    strftime(date_heure, sizeof(date_heure), "%d-%m-%Y, %H:%M:%S --> ", date_heure_actuelles);

    FILE *fichier = fopen("stat.txt", "a");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier stat\n");
        return -1; 
    }

    fputs("Erreur: ", fichier);
    fputs(date_heure, fichier);
    fputs(erreur, fichier);
    fputs("\n", fichier);
    fclose(fichier);
    return 0;
}

