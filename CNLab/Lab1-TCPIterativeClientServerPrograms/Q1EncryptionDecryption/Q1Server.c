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
    int sockID, newSockID, clientAddrLen, n, i = 0;
    struct sockaddr_in serverAddr, clientAddr;

    sockID = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("172.16.59.25"); // replace IP
    serverAddr.sin_port = htons(PORTNO);
    bind(sockID, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    listen(sockID, 5);

    char buf[256];

    newSockID = accept(sockID, (struct sockaddr *)&clientAddr, &clientAddrLen);

    n = read(newSockID, buf, sizeof(buf));
    printf("\nMessage from Client : %s \n", buf);

    while (buf[i] != '\0')
        buf[i++] -= 4;

    printf("Decrypted message : %s \n", buf);

    close(newSockID);
    close(sockID);

}