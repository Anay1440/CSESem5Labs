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

    while (1) {
        newSockID = accept(sockID, (struct sockaddr *)&clientAddr, &clientAddrLen);

        if (fork() == 0) {

            int arr[2];

            char op;

            n = read(newSockID, arr, 2 * sizeof(int));
            int x = arr[0];
            int y = arr[1];
            int res = -1;

            printf("Read %d %d\n", x, y);

            n = read(newSockID, &op, 1);

            if (op == '+')
                res = x + y;
            else if (op == '*')
                res = x * y;
            else if (op == '-')
                res = x - y;
            else if (op == '/')
                res = x / y;

            arr[0] = res;

            write(newSockID, arr, 1);

            close(newSockID);
            exit(0);
        }
        else
            close(newSockID);
    }
}