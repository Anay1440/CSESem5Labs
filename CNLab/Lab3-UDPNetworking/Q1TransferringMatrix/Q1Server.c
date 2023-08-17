#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PORTNO 10200

void main() {
    int status, rows, cols, clientAddrLen;
    struct sockaddr_in serverAddr, clientAddr;
    int sockID = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.16.59.71"); // replace IP
    serverAddr.sin_port = htons(PORTNO);
    bind(sockID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    int arr[100];

    recvfrom(sockID, arr, sizeof(arr), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);

    rows = arr[0];
    cols = arr[1];

    int ** mat = (int **) malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        recvfrom(sockID, arr, sizeof(arr), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        mat[i] = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++)
            mat[i][j] = arr[j];
    }

    printf("The matrix formed is: \n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }

}