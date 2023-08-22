#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main(int argc, char * args[]) {

    /*
        How to execute

        ./<object name> <path>
        Ex: $ gcc -o Q1 Q1SimpleLS.c
            $ ./Q1 /home/student/Documents
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
    
    while ((dirEntry = readdir(dirPtr)) != NULL) {
        if (strcmp(".", dirEntry->d_name) == 0 || strcmp("..", dirEntry->d_name) == 0)
            continue;
        stat(dirEntry->d_name, &fileStat);
        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\t%s\n", dirEntry->d_name);
    }
    chdir("..");
    closedir(dirPtr);
}