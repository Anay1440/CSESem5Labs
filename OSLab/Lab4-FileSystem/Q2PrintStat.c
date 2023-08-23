#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

void main() {
    char fileName[100], timeStr[32], fileMode[11];
    printf("Enter filename ");
    scanf("%s", fileName);
    struct stat fileStat;
    stat(fileName, &fileStat);
    time_t t = fileStat.st_atime;
    struct tm * timeStamp = localtime(&t);
    strftime(timeStr, sizeof(timeStr), "%a %Y-%m-%d %H:%M:%S", timeStamp);
    fileMode[0] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
    fileMode[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    fileMode[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    fileMode[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    fileMode[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    fileMode[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    fileMode[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    fileMode[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    fileMode[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    fileMode[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    fileMode[10] = '\0';
    printf("Device ID: %ld\nFile Serial No: %ld\nMode of file: %s\nNo. of hard links: %ld\nTime of last access: %s\n", fileStat.st_dev, fileStat.st_ino, fileMode, fileStat.st_nlink, timeStr);
}