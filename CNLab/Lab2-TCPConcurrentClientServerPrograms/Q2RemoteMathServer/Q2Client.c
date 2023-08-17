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
    int addrLen, result, sockID, i = 0, n, x, y;
    struct sockaddr_in addr;
    int arr[2], arrReceive;

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

    printf("Enter both numbers separated by space ");
    scanf("%d %d", &x, &y);

    printf("Read: %d %d\n", x, y);

    char op;
    scanf("%c", &op);

    arr[0] = x;
    arr[1] = y;
    write(sockID, arr, 2 * sizeof(int));


    printf("Enter operator (+, -, * or /) ");
    scanf("%c", &op);

    write(sockID, &op, 1);

    i = read(sockID, arr, 1);

    printf("Result: %d\n", arr[0]);

    close(sockID);
}