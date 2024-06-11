/*
 * A4 - Server
 * Author: Antenor Barros
 */

#include "main.h"
/*
 * Get the args in short and/or long form and pass to the main code
 */

int main(int argc, char** argv) {
    char* port       = malloque(7);
    char* log        = malloque(PATH_MAX + 1);
    char* statistics = malloque(PATH_MAX + 1);
    bool background  = false;
    char* root       = malloque(PATH_MAX + 1);
    isVerbose        = false;

    struct option options[] = {
        {"port",       required_argument,   0, 'p'},
        {"log",        required_argument,   0, 'l'},
        {"statistics", required_argument,   0, 's'},
        {"background", no_argument,         0, 'b'},
        {"root ",      required_argument,   0, 'r'},
        {"verbose",    isVerbose,           0, 'v'},
        {"help",       no_argument,         0, 'h'},
        {0, 0, 0, 0}
    };

    int op;
    while ((op = getopt_long(argc, argv, ":p:l:s:bvr:h", options, NULL)) != -1) {
        switch (op) {
        case 'p':
            strncpy(port, optarg, 7);
            break;
        case 'l':
            strncpy(log, optarg, PATH_MAX);
            break;
        case 's':
            strncpy(statistics, optarg, PATH_MAX);
            break;
        case 'b':
            background = true;
            break;
        case 'v':
            isVerbose = true;
            break;
        case 'r':
            strncpy(root, optarg, PATH_MAX - 1);
            break;
        case 'h':
            help();
            break;
        default:
            panic(1, "Invalid arg: %c", optopt);
        }
    }

    /* Check for mandatory args */
    if (strlen(port) == 0) {
        panic(1, "You need to specify the port. E.g. -p 5000");
    }
    if (atoi(port) == 0) {
        panic(1, "Invalid port. E.g. -p 5000");
    }
    if (strlen(root) == 0) {
        panic(1, "You need to specify the root path. E.g. -r ./test");
    }
    if (strlen(statistics) == 0) {
        statistics = NULL;
    }
    if (strlen(log) == 0) {
        log = NULL;
    }

    /* Sanitization */
    char* s = port;
    while (*s) {
    	if (isdigit(*s++) == 0) panic(1, "Invalid port. Must be a number. E.g. -p 5000");
    }

    int portI = atoi(port);
    if (portI < 0 || portI >= 65535) {
        panic(1, "Invalid port. Must be between 0 and 65535. E.g. -p 5000");
    }

    DIR *dir;
    if ((dir = opendir(root)) == 0) {
	    panic(1, "Invalid root path. E.g. -r ./test");
    }
    closedir(dir);

    if (log != NULL && !isValidPath(log)) {
	    panic(1, "The log file folder path is invalid. Use ./ for local directory. E.g. ./log.log");
    }

    if (statistics != NULL && !isValidPath(statistics)) {
	    panic(1, "The statistics file folder path is invalid. Use ./ for local directory. Ex.: ./stats.txt");
    }
    
    server(port, root, log, statistics, background);

    free(port);
    free(log);
    free(statistics);
    free(root);
    return 0;
}
