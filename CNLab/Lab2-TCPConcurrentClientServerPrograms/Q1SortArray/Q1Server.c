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

            int arr[100];

            n = read(newSockID, arr, 1);
            int len = arr[0];

            n = read(newSockID, arr, sizeof(arr));

            for (i = 0; i < len - 1; i++) {
                for (j = 0; j < len - i - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        k = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = k;
                    }
                }
            }

            int pid = getpid();

            int arr2[1] = {pid};

            write(newSockID, arr2, 1);

            write(newSockID, arr, n * sizeof(int));

            close(newSockID);
            exit(0);
        }
        else
            close(newSockID);
    }
}