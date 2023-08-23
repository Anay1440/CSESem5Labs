#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void main() {

    /*
        How to execute

        Create 2 folders Temp1 and Temp2 in Documents, and create a Text.txt inside Temp1 folder
        Execute this file and put the pathnames as shown
        After execution, you will see in the File Explorer that Text.txt is shifted from Temp1 to Temp2

        *Note*
        If you comment out the unlink part, then you will be able to see the Text.txt from both Temp1 and Temp2 folders
    */

    char oldPath[100], newPath[100];
    printf("Enter old path ");
    scanf("%s", oldPath); //    /home/student/Documents/Temp1/Text.txt
    printf("Enter new path "); //    /home/student/Documents/Temp2/Text.txt
    scanf("%s", newPath);
    int res = link(oldPath, newPath);
    if (res == 0) {
        res = unlink(oldPath);
        if (res == 0)
            printf("New path to the file: %s\n", newPath);
        else
            printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}