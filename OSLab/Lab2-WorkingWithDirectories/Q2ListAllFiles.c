#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printFilesInDir(char * dirName) {
    DIR * dirPtr;
    struct dirent *dirEntry;
    struct stat fileStat;

    if ((dirPtr = opendir(dirName)) == NULL) {
        printf("Cannot open directory: %s\n", dirName);
        return;
    }
    chdir(dirName);

    while ((dirEntry = readdir(dirPtr)) != NULL) {
        stat(dirEntry->d_name, &fileStat);
        if (!S_ISDIR(fileStat.st_mode)) {
            printf("%s\n", dirEntry->d_name);
        }
        else {
            if (!(strcmp(".", dirEntry->d_name) == 0 || strcmp("..", dirEntry->d_name) == 0))
                printFilesInDir(dirEntry->d_name);
        }
    }

    chdir("..");
    closedir(dirPtr);

}

void main(int argc, char * args[]) {

    /*
        How to execute

        ./<object name> <path>
        Ex: $ gcc -o Q2 Q2ListAllFiles.c
            $ ./Q2 /home/student/Documents
    */

    if (argc > 1)
        printFilesInDir(args[1]);
    else
        printf("Insufficient arguments\n");
}