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
    int arr[100], arrReceive[100];

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

    printf("\nEnter number of elements in array ");
    scanf("%d", &n);

    fflush(stdin);
    arr[0] = n;
    write(sockID, arr, 1);

    for (i = 0; i < n; i++) {
        printf("Enter arr[%d] ", i);
        scanf("%d", &arr[i]);
    }

    write(sockID, arr, n * sizeof(int));

    i = read(sockID, arr, 1);

    printf("Process id of server: %d\n", arr[0]);

    i = read(sockID, arrReceive, n * sizeof(int));

    printf("Received: \n");
    for (i = 0; i < n; i++) {
        printf("%d ", arrReceive[i]);
    }

    close(sockID);
}