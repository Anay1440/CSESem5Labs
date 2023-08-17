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
    struct sockaddr_in addr;
    int sockID = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("172.16.59.71"); // replace IP
    addr.sin_port = htons(PORTNO);

    int rows, cols;
    printf("Enter rows and columns of the matrix ");
    scanf("%d %d", &rows, &cols);

    int temp[2];
    temp[0] = rows;
    temp[1] = cols;

    sendto(sockID, temp, sizeof(temp), 0, (struct sockaddr *)&addr, sizeof(addr));

    int * arr = (int *) malloc(cols * sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter a[%d][%d] ", i, j);
            scanf("%d", &arr[j]);
        }
        sendto(sockID, arr, cols * sizeof(int), 0, (struct sockaddr *)&addr, sizeof(addr));
    }
}