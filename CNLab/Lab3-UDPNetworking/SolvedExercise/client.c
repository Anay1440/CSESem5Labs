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

int main() {
    int sd;
    struct sockaddr_in address;
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.59.71"); //**
    address.sin_port = htons(PORTNO);
    char buf[25], buf1[25];
    printf("enter buf\n");
    scanf("%[^\n]", buf);
    int len = sizeof(address);
    int m = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&address, len);
    int n = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&address, &len);
    printf("the server echo is\n");
    puts(buf);
    return 0;
}