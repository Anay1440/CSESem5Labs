#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main() {
    char fileName[100];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    printf("Inode: %ld\n", fileStat.st_ino);
}