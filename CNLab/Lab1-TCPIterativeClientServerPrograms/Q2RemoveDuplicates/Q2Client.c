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
    int addrLen, result, sockID, i = 0, n;
    struct sockaddr_in addr;
    char st[256], buf[256];

    sockID = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("172.16.59.71"); // replace IP
    addr.sin_port = htons(PORTNO);
    addrLen = sizeof(addr);

    result = connect(sockID, (struct sockaddr *)&addr, addrLen);

    if (result == -1) {
        perror("\nCould not connect\n");
        exit(1);
    }

    while(1) {
        printf("\nEnter string ");
        scanf("%[^\n]", st);

        printf("Sending : %s\n", st);

        write(sockID, st, strlen(st));

        if (strcmp(st, "STOP") == 0) {
            printf("Exiting.\n");
            exit(0);
        }

        n = read(sockID, buf, sizeof(buf));

        printf("Received : %s", buf);

    }

    close(sockID);
}