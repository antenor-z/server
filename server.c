#include "server.h"
#include "panic.h"
#include "handleData.h"

int server(char* port, char* filesLocation) {
    int socketfd, conexaofd;

    /* Get endereço host */
    struct addrinfo *enderecoHost, dicas;
    memset(&dicas, 0, sizeof dicas);
    dicas.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
    dicas.ai_family = AF_INET;
    dicas.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL, port, &dicas, &enderecoHost) != 0) {
        panic(1, "No information from server");
    }

    /* Socket */
    socketfd = socket(enderecoHost->ai_family,
    enderecoHost->ai_socktype,
    enderecoHost->ai_protocol);
    if (socketfd == -1) {
        panic(1, "Error on socket creation.");
    }

    /* Set mode */
    int optval=1;
    if (setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof optval)==-1) {
        panic(1, "Error on reusing addr.");
    }

    /* Bind socket */
    if (bind(socketfd,enderecoHost->ai_addr,enderecoHost->ai_addrlen)==-1) {
        panic(1, "Error on socket binding\n");
    }

    /* Listen to port */
    if (listen(socketfd, MAXLISTEN) == -1) {
        panic(1, "Error when tried to listen to port %d", port);
    }
    printf("Listening on port %s\n", port);

    while(1) {
        conexaofd = 0;
        unsigned tamCliente;
        char hostname[NI_MAXHOST], hostaddr[NI_MAXHOST];
        tEndereco enderecoCliente;
        tamCliente = sizeof (tEndereco);

        conexaofd = accept(socketfd, (struct sockaddr *)&enderecoCliente, &tamCliente);
        getnameinfo((struct sockaddr*)&enderecoCliente, tamCliente,
        hostname, sizeof hostname,
        NULL, 0, 0);

        getnameinfo((struct sockaddr*)&enderecoCliente,
        tamCliente, hostaddr, sizeof hostaddr,
        NULL, 0, NI_NUMERICHOST);

        printf("Server connected to %s (%s)\n", hostname, hostaddr);

        if (conexaofd == -1)
            continue;
        
        handleData(conexaofd, filesLocation);
    }
}


