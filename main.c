/*
 * A4 - Server
 * Author: Antenor Barros
 */
#include <getopt.h>
#include <stdbool.h>
#include <string.h>
#include "help.h"
#include "panic.h"
#include "server.h"
#include <unistd.h>
/*
 * Get the args in short and/or long form and pass to the main code
 */
#define MAX_PATH_SIZE 4096

int main(int argc, char** argv) {
    char* port = malloque(7);
    char* log = malloque(MAX_PATH_SIZE + 1);
    char* statistics = malloque(MAX_PATH_SIZE + 1);
    bool background = false;
    char* root = malloque(MAX_PATH_SIZE + 1);
    bool isVerbose = false;

    struct option options[] = {
        {"port", required_argument,         0, 'p'},
        {"log", required_argument,          0, 'l'},
        {"statistics", required_argument,   0, 's'},
        {"background", no_argument,         0, 'b'},
        {"root ", required_argument,        0, 'r'},
        {"verbose", isVerbose,              0, 'v'},
        {"help", no_argument,               0, 'h'},
        {0, 0, 0, 0}
    };

    int op;
    while ((op = getopt_long(argc, argv, ":p:l:s:bvr:h", options, NULL)) != -1) {
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
        case 'v':
            isVerbose = true;
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

    if (strlen(port) == 0) {
        panic(1, "É necessário informar a porta. Use -p");
    }
    if (atoi(port) == 0) {
        panic(1, "Porta inválida.");
    }
    if (strlen(root) == 0) {
        panic(1, "É necessário informar o caminho da pasta fonte. Use -r");
    }
    if (strlen(statistics) == 0) {
        panic(1, "É necessário informar o caminho do arquivo de estatística. Use -s");
    }
    if (strlen(log) == 0) {
        panic(1, "É necessário informar o caminho do arquivo de logs. Use -l");
    }
    
    server(port, root, log, statistics, background);
    return 0;
}
