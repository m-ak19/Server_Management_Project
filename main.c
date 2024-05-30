#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>



int main() {
    AffichNombreFichierRecus();
    AffichNombreErreur();
    //ecrire_fichier_recu("règles.pdf");
    //ecrire_erreur("Problème lors de l'initialisation!");
    return 0;
}