#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORTNO 10200

void main() {
    int sockID, newSockID, clientAddrLen, n, i = 0, j = 0, k = 0;
    struct sockaddr_in serverAddr, clientAddr;

    sockID = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.16.59.71"); // replace IP
    serverAddr.sin_port = htons(PORTNO);
    bind(sockID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(sockID, 5);

    while(1) {

        char buf[256];

        newSockID = accept(sockID, (struct sockaddr *)&clientAddr, &clientAddrLen);

        n = read(newSockID, buf, sizeof(buf));

        if (strcmp(buf, "STOP") == 0) {
            printf("Exiting\n");
            close(newSockID);
            close(sockID);
            exit(0);
        }
        
        char mat[20][256], res[256] = "";

        while (buf[i] != '\0') {
            if (buf[i] == ' ') {
                mat[k][j] = '\0';
                k++;
                j = 0;
            }
            else {
                mat[k][j] = buf[i];
                j++;
            }
            i++;
        }

        printf("J is: %d\n", j);

        mat[k][j] = '\0';

        printf("last: %s\n", mat[k]);

        for (i = 0; i < k; i++) {
            for (j = 1; j < k + 1; j++) {
                if (mat[j][0] == '\0')
                    continue;
                if (strcmp (mat[i], mat[j]) == 0)
                    mat[j][0] = '\0';
            }
        }

        for (i = 0; i < k + 1; i++) {
            if (mat[i][0] != '\0') {
                strcat(res, mat[i]);
                strcat(res, " ");
            }
        }

        if (mat[k][0] != '\0')
            strcat(res, mat[k]);

        write(newSockID, res, strlen(res));
    }
}