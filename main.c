#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "help.h"
#include "panic.h"
#include "server.h"
#define MAX_PATH_SIZE 2048

int main(int argc, char** argv) {
    char port[7];
    char log[MAX_PATH_SIZE + 1];
    char statistics[MAX_PATH_SIZE + 1];
    bool background = false;
    char root[MAX_PATH_SIZE + 1];

    struct option options[] = {
        {"port", required_argument,         0, 'p'},
        {"log", required_argument,          0, 'l'},
        {"statistics ", required_argument,  0, 's'},
        {"background", no_argument,         0, 'b'},
        {"root ", required_argument,        0, 'r'},
        {"help", no_argument,               0, 'h'},
        {0, 0, 0, 0}
    };

    int op;
    while ((op = getopt_long(argc, argv, ":p:l:s:br:h", options, NULL)) != -1) {
        switch (op) {
        case 'p':
            strncpy(port, optarg, 7);
            break;
        case 'l':
            strncpy(log, optarg, MAX_PATH_SIZE - 1);
            break;
        case 's':
            strncpy(statistics, optarg, MAX_PATH_SIZE - 1);
            break;
        case 'b':
            background = true;
            break;
        case 'r':
            strncpy(root, optarg, MAX_PATH_SIZE - 1);
            break;
        case 'h':
                help();
                break;
        default:
            panic(1, "Argumento inválido: %c", optopt);
        }
    }


    // printf("PORTA: %s;\n", port);
    // printf("LOG: %s;\n", log);
    // printf("STAT: %s;\n", statistics);
    // printf("BACKGROUND?: %d;\n", background);
    // printf("ROOT: %s;\n", root);
    
    server(port, root);
    return 0;
}