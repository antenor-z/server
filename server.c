#include "server.h"

/*
 * Waits for TCP connection, when something arrives, make the args structure
 * and create handleData thread passing args.
 * Uses select() to be able to timeout accept(), so that the threads
 * can be stopped on SIGINT or SIGUSR1
 */
bool breakLoop = false;

int server(char* port, char* filesLocation, char* logPath, char* statsPath, bool background) {
    pthread_t logThread;
    pthread_t threadsPool[MAX_NUM_THREADS];
    for (int i = 0; i < MAX_NUM_THREADS; i++) {
        threadsPool[i] = 0;
    }
    int currentThread = 0;

    Queue logQueue;
    Queue statsQueue;

    queueInit(&logQueue);
    queueInit(&statsQueue);

    signal(SIGINT, bye);
    signal(SIGUSR1, bye);
    int socketfd, conexaofd;
    insertLogArgs logArgs;
    logArgs.queue = &logQueue;
    logArgs.logPath = logPath;

    insertStatsArgs statsArgs;
    statsArgs.queue = &statsQueue;
    statsArgs.logPath = statsPath;

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
    int optval = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) == -1) {
        panic(1, "Error on reusing addr.");
    }

    /* Bind socket */
    if (bind(socketfd, enderecoHost->ai_addr, enderecoHost->ai_addrlen) == -1) {
        panic(1, "Error on socket binding\n");
    }

    /* Listen to port */
    if (listen(socketfd, MAXLISTEN) == -1) {
        panic(1, "Error when tried to listen to port %d", port);
    }
    
    if (logPath != NULL) {
        pthread_create(&logThread, NULL, insertLog, (void*)&logArgs);
    }

    if (background) {
        pid_t pid = fork();
        if (pid < 0) {
            panic(1, "Error when forking process");
        }
        if (pid > 0) {
            exit(0);
        }
    }

    printf("\n%s  This is A4-Server running on port %s.\n", LINE_1, port);
    printf("%s  Use 'kill -s SIGUSR1 %d' to close me.\n%s\n", LINE_2, getpid(), LINE_3);
    printf("%s  - Serving files from: '%s'\n", LINE_4, filesLocation);
    if (logPath != NULL) {
        printf("%s  - Log file is saved on '%s'\n", LINE_5, logPath);
    } else {
        printf("%s  - Log file not activated\n", LINE_5);
    }
    if (statsPath != NULL) {
        printf("%s  - Statistics file is saved on '%s'\n", LINE_6, statsPath);
    } else {
        printf("%s  - Statistics file not activated\n", LINE_6);
    }
    if (isVerbose) {
        printf("%s  - Verbose logs activated \n", LINE_6);
    } else {
        printf("%s  - Verbose logs not activated \n", LINE_6);
    }
    if (background) {
        printf("%s  - Background mode is set\n", LINE_6);
        int dev_null = open("/dev/null", O_RDWR);
        if (dev_null == -1) {
            panic(1, "Error opening /dev/null");
        }
        dup2(dev_null, STDIN_FILENO);
        dup2(dev_null, STDOUT_FILENO);
        dup2(dev_null, STDERR_FILENO);
    }

    while (!breakLoop) {
        conexaofd = 0;
        unsigned tamCliente;
        char hostname[NI_MAXHOST], hostaddr[NI_MAXHOST];
        tEndereco enderecoCliente;
        tamCliente = sizeof(tEndereco);

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
        conexaofd = accept(socketfd, (struct sockaddr*)&enderecoCliente, &tamCliente);
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

        struct handleDataArgs* args = malloque(sizeof(struct handleDataArgs));

        args->socket = conexaofd;
        args->filesLocation = filesLocation;
        args->queue = &logQueue;
        args->statsQueue = &statsQueue;
        args->hostname = strdup(hostname);  // Allocate memory for hostname
        args->hostaddr = strdup(hostaddr);  // Allocate memory for hostaddr

        debug(&logQueue, "--------------[ CONNECTION ]--------------");
        debug(&logQueue, "Socket: %d", args->socket);
        debug(&logQueue, "Host name: %s", args->hostname);
        debug(&logQueue, "Host addr: %s", args->hostaddr);

        if (threadsPool[currentThread] != 0) {
            pthread_join(threadsPool[currentThread], NULL);
            threadsPool[currentThread] = 0;
        }
        if (pthread_create(&threadsPool[currentThread], NULL, &handleData, (void*)args) != 0) {
            panic(1, "Could not create thread");
        }
        if (currentThread < MAX_NUM_THREADS - 1) {
            currentThread += 1;
        }
        else {
            currentThread = 0;
        }
    }

    debug(&logQueue, "[   Server   ] Inserting stats");
    puts("[   Server   ] Inserting stats");
    insertStats((void*)&statsArgs);

    puts("[  Server  ] Waiting for remaining threads to die");
    debug(&logQueue, "[   Server   ] Waiting for remaining threads to die");
    for (int i = 0; i < MAX_NUM_THREADS; i++) {
        if (threadsPool[i] != 0) {
            pthread_join(threadsPool[currentThread], NULL);
        }
    }
    // pthread_join(logThread, NULL);
    puts("\n[  Server  ] Bye");
    free(enderecoHost);
    return 0;
}
