#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int erreur_integreation=getNombreErreur("stat_erreur_integration.txt");
    int fichier_recu_integration=getNombreFichierRecus("stat_fichier_recus_integration.txt");
    int ecrire_erreur_integration=ecrire_fin_fichier_stat("Erreur 2","stat_erreur_integration.txt" );
    int ecrire_fichier_recu_integration=ecrire_fin_fichier_stat("Fichier ","stat_fichier_recus_integration.txt" );

    return 0;
}