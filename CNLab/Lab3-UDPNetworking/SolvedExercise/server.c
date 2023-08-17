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
    char buf[25];
    struct sockaddr_in sadd, cadd;
    // Create a UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    // Construct the address for use with sendto/recvfrom... */
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("172.16.59.71"); //**
    sadd.sin_port = htons(PORTNO);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    int m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &len);
    printf("the server send is\n");
    puts(buf);
    int n = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, len);
    return 0;
}