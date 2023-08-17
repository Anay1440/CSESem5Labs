#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PORTNO 10200

void main() {
    int sockID, newSockID, clientAddrLen, n, i = 0;

    struct sockaddr_in serverAddr, clientAddr;

    sockID = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.16.59.71"); // replace IP
    serverAddr.sin_port = htons(PORTNO);
    bind(sockID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(sockID, 5);

    while(1) {

        newSockID = accept(sockID, (struct sockaddr *)&clientAddr, &clientAddrLen);
        
        if (fork() == 0) {
            time_t t;
            time(&t);
            char * st = ctime(&t);
            printf("%s", st);
            write(newSockID, st, strlen(st));
            close(newSockID);
            exit(0);
        }
        else
            close(newSockID);
    }

}