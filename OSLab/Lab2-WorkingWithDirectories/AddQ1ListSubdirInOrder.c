#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printSorted(char ** dirNames, int n) {

    char temp[100];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(dirNames[j], dirNames[j + 1]) < 0) {
                strcpy(temp, dirNames[j]);
                strcpy(dirNames[j], dirNames[j + 1]);
                strcpy(dirNames[j + 1], temp);
            }
        }
		printf("%s\n", dirNames[n - i - 1]);
    }

    printf("%s\n", dirNames[0]);

}

void main(int argc, char * args[]) {

    /*
        How to execute

        ./<object name> <path>
        Ex: $ gcc -o AddQ1 AddQ1ListSubdirInOrder.c
            $ ./AddQ1 /home/student/Documents
    */

    if (argc <= 1) {
        printf("Insufficient arguments\n");
        exit(1);
    }
    DIR * dirPtr;
    struct dirent *dirEntry;
    struct stat fileStat;

    if ((dirPtr = opendir(args[1])) == NULL) {
        printf("Cannot open directory: %s\n", args[1]);
        exit(1);
    }
    chdir(args[1]);

    char ** dirNames = (char **) malloc(40 * sizeof(char *));

    int i = 0;
    
    while ((dirEntry = readdir(dirPtr)) != NULL) {
        if (strcmp(".", dirEntry->d_name) == 0 || strcmp("..", dirEntry->d_name) == 0)
            continue;
        stat(dirEntry->d_name, &fileStat);
        if (S_ISDIR(fileStat.st_mode)) {
            dirNames[i] = (char *) malloc(100 * sizeof(char));
            strcpy(dirNames[i], dirEntry->d_name);
            i++;
        }
    }

    printSorted(dirNames, i);

    chdir("..");
    closedir(dirPtr);
}