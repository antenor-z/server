#include "utils.h"
/*
 * Get out of main loop on SIGINT or SIGUSR1
 */
void bye(){
    breakLoop = true;
}


bool isValidPath(char *path) {
    char* dirPath = malloque(PATH_MAX);
    strcpy(dirPath, path);
    char *lastSlash = strrchr(dirPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }

	DIR *dir;
    if ((dir = opendir(dirPath)) == 0) {
        free(dirPath);
	    return false;
    }
    closedir(dir);
    free(dirPath);
    return true;
}

/*
 * Get current formated datetime to put in the log
 */
char* datetime() {
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *ret = malloque(25);
    sprintf(ret, "%02d/%02d/%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return ret;
}

/*
 * Show help when using -h or --help
 */

void help() {
    puts("-p --port <porta> Número da porta do serviço");
    puts("-l --log <filename> Nome completo do arquivo de log");
    puts("-s --statistics <filename> Nome completo do arquivo de estatísticas");
    puts("-b --background O serviço deverá rodar em background (Desafio!)");
    puts("-v --verbose As informações de debug são mostradas");
    puts("-r --root Caminho da raiz do site");
    exit(0);
}

/*
 * Safe malloc
 */
void *malloque(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        panic(1, "malloc failed");
    }
    return ptr;
}

void panic(int statusCode, const char* message, ...) {
    fprintf(stderr, "[  PANIC  ] ");
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    fputs("\n", stderr);
    va_end(args);
    exit(statusCode);
}
