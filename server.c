#include "server.h"
#include "panic.h"
#include "bye.h"
#include "handleData.h"
#include "insertLog.h"
#include "countStats.h"

/*
 * Waits for TCP connection, when something arrives, make the args structure
 * and create handleData thread passing args.
 * Uses select() to be able to timeout accept(), so that the threads
 * can be stoped on SIGINT or SIGUSR1
 */
bool breakLoop = false;
pthread_t threads[NUM_THREADS];
LogQueue queue = { .head = NULL, .tail = NULL, .mutex = PTHREAD_MUTEX_INITIALIZER,
                    .cond_producer = PTHREAD_COND_INITIALIZER, .cond_consumer = PTHREAD_COND_INITIALIZER };
LogQueue statsQueue = { .head = NULL, .tail = NULL, .mutex = PTHREAD_MUTEX_INITIALIZER,
                    .cond_producer = PTHREAD_COND_INITIALIZER, .cond_consumer = PTHREAD_COND_INITIALIZER };
LogQueue threadsQueue = { .head = NULL, .tail = NULL, .mutex = PTHREAD_MUTEX_INITIALIZER,
                    .cond_producer = PTHREAD_COND_INITIALIZER, .cond_consumer = PTHREAD_COND_INITIALIZER };

int server(char* port, char* filesLocation, char* logPath, char* statsPath) {
    signal(SIGINT, bye);
    signal(SIGUSR1, bye);
    int socketfd, conexaofd;
    struct insertLogArgs logArgs;
    logArgs.queue = &queue;
    logArgs.logPath = logPath;

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
    printf("Use 'kill -s SIGUSR1 %d' to close me.\n", getpid());

    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[NUM_THREADS - 1], NULL, insertLog, (void*)&logArgs);
    pthread_create(&threads[NUM_THREADS - 2], NULL, insertStats, (void*)&statsQueue);


    while(!breakLoop) {
        conexaofd = 0;
        unsigned tamCliente;
        char hostname[NI_MAXHOST], hostaddr[NI_MAXHOST];
        tEndereco enderecoCliente;
        tamCliente = sizeof (tEndereco);

        /* Using select for accept() to "timeout" */
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(socketfd, &fds);

        /* Timeout 1 sec */
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        /* Wait for connection or timeout */
        int selectResult = select(socketfd + 1, &fds, NULL, NULL, &timeout);
        if (selectResult == -1 || selectResult == 0) {
            continue;
        }

        /* Accept connection */ 
        conexaofd = accept(socketfd, (struct sockaddr *)&enderecoCliente, &tamCliente);
        if (conexaofd == -1) {
            continue;
        }

        /* Get host information */
        getnameinfo((struct sockaddr*)&enderecoCliente, tamCliente,
                    hostname, sizeof hostname,
                    NULL, 0, 0);

        getnameinfo((struct sockaddr*)&enderecoCliente,
                    tamCliente, hostaddr, sizeof hostaddr,
                    NULL, 0, NI_NUMERICHOST);

        printf("Server connected to %s (%s)\n", hostname, hostaddr);

        struct handleDataArgs args;
        args.socket = conexaofd;
        args.filesLocation = filesLocation;
        args.queue = &queue;
        args.statsQueue = &statsQueue;

        pthread_t newThread;
        if (pthread_create(&newThread, NULL, &handleData, (void *)&args) != 0) {
            panic(1, "Could not create thread");
        }
        enqueue(&threadsQueue, &newThread);
    }
    
    printf("[  Server  ] Waiting to for threads to die\n");
    pthread_t* ptrThreadToBeWaited;
    while (threadsQueue.head != NULL) {
        ptrThreadToBeWaited = dequeue(&threadsQueue);
        printf(".");
        pthread_join(*ptrThreadToBeWaited, NULL);
    }
    printf("\n");
    puts("[  Server  ] Bye");
    return 0;
}


