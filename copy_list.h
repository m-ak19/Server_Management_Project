#ifndef COPYLISTH
#define COPYLISTH

#include <stdio.h>


void getCopiedFileNames();
void lire_noms_fichiers(const char* nom_fichier);
void checkAndCopyFiles(FILE *updateListFile);
void copyFile(const char *srcPath, const char *destPath);
void extractDateTime(const char *dateStr, struct tm *tm);

#endif