Name                    Purpose
AF_UNIX,                AF_LOCALLocal communication
AF_INET                 IPv4 Internet protocols
AF_INET6                IPv6 Internet protocols
AF_IPX                  IPX - Novell protocols

# Socket Address Struct
```
    struct sockaddr_in {
        short int sin_family; // Address family unsigned short int sin_port; // Port number
        struct in_addr sin_addr; // Internet address
    };
```

# IP Address Struct
```
    struct in_addr {
        unsigned long int s_addr;
    };
```
htons() -- "Host to Network Short"
htonl() -- "Host to Network Long"
ntohs() -- "Network to Host Short"
ntohl() -- "Network to Host Long"
inet_addr() / inet_aton() -- converts the Internet host address from the standard numbers-and-dots
notation into binary data. It returns nonzero if the address is valid, zero if not.

# Socket creation
int sockid = socket(family, type, protocol);

# Assign address to socket
int status = bind(sockid, &addrport, size);

# Listen to connection requests
int status = listen(sockid, queueLimit);

# Establish connection to server from client
int status = connect(sockid, &foreignAddr, addrlen);

# Accept incoming request
int newsockid = accept(sockid, &clientAddr, &addrLen);

# Send and receive in stream socket
int count = send(sockid, msg, msgLen, flags);
int count = recv(sockid, recvBuf, bufLen, flags);

# Closing socket
int status = close(sockid);