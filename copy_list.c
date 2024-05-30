#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define MAX_NOM_FICHIER 256
#define INTEGRATION_LIST "listCopy.txt"
#define ENVOI_DIRECTORY "Production/"
#define RECEPTION_DIRECTORY "Integration/"

void extractDateTime(const char *dateStr, struct tm *tm) {
    sscanf(dateStr, "%d/%d/%d - %d:%d:%d",
           &tm->tm_mday, &tm->tm_mon, &tm->tm_year,
           &tm->tm_hour, &tm->tm_min, &tm->tm_sec);
    tm->tm_mon -= 1;  
    tm->tm_year -= 1900;  
}

void copyFile(const char *srcPath, const char *destPath) {
    FILE *srcFile = fopen(srcPath, "rb");
    if (!srcFile) {
        perror("Erreur lors de l'ouverture du fichier source");
        return;
    }

    FILE *destFile = fopen(destPath, "wb");
    if (!destFile) {
        perror("Erreur lors de l'ouverture du fichier de destination");
        fclose(srcFile);
        return;
    }

    char buffer[BUFSIZ];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(srcFile);
    fclose(destFile);
}

void checkAndCopyFiles(FILE *updateListFile) {
    char line[512];
    char fileName[MAX_NOM_FICHIER];
    char dateStr[30];
    struct stat fileStat;
    struct tm listTime, fileTime;

    while (fgets(line, sizeof(line), updateListFile) != NULL) {
        char fileLine[256];
        if (sscanf(line, "%[^-] - %[^\n]", fileLine, dateStr) != 2) {
            fprintf(stderr, "Format de ligne incorrect : %s\n", line);
            continue;
        }

        char *startPtr = fileLine;
        while (*startPtr == ' ') startPtr++;
        char *endPtr = startPtr + strlen(startPtr) - 1;
        while (*endPtr == ' ') endPtr--;
        *(endPtr + 1) = '\0';
        strcpy(fileName, startPtr);

        char srcPath[MAX_NOM_FICHIER * 2];
        char destPath[MAX_NOM_FICHIER * 2];
        snprintf(srcPath, sizeof(srcPath), "%s%s", ENVOI_DIRECTORY, fileName);
        snprintf(destPath, sizeof(destPath), "%s%s", RECEPTION_DIRECTORY, fileName);

        if (stat(destPath, &fileStat) == 0) {
            localtime_r(&fileStat.st_mtime, &fileTime);
            extractDateTime(dateStr, &listTime);

            if (difftime(mktime(&fileTime), mktime(&listTime)) != 0) {
                copyFile(srcPath, destPath);
            }
        } else {
            copyFile(srcPath, destPath);
        }
    }
}

