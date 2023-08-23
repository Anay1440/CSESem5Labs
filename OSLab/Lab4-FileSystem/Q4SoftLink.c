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
        After execution, you will see in the File Explorer that theres a shortcut to Text.txt from Temp2 folder

        *Note*
        If you uncomment the unlink part, you will see a broken symlink,
        because the Text.txt file gets deleted because the only hard link to it gets deleted.
    */

    char oldPath[100], newPath[100];
    printf("Enter old path ");
    scanf("%s", oldPath); //    /home/student/Documents/Temp1/Text.txt
    printf("Enter new path "); //    /home/student/Documents/Temp2/Text.txt
    scanf("%s", newPath);
    int res = symlink(oldPath, newPath);
    if (res == 0) {
        printf("Symbolic link created\n");

        // res = unlink(oldPath);
        // if (res != 0)
        //     printf("Error unlinking\n");
    }
    else
        printf("Error linking\n");
}