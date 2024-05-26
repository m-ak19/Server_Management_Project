#ifndef STATH
#define STATH

int getNombreLigne(char* nom_fichier);
int getNombreErreur(char* nom_fichier);
int getNombreFichierRecus(char* nom_fichier);
int ecrire_erreur(char* erreur, char* nom_fichier);
int ecrire_fin_fichier_stat(char* texte_a_ecrire, char* nom_fichier);

#endif