#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
//#include <sys/types.h>
#include <string.h>
#include "synchro_list.h"

#define MSG_SIZE 128

char* message = "TEST SUCCESS";


int main(void){

    if(synchroniseLists() == 1){
        printf("Lists have beeen successfully synchronized. \n");
    }
    else{
        printf("Error during lists synchronization.\n");
    }
    return 0;
}