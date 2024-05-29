#include "isValidPath.h"

bool isValidPath(char *path) {
    char* dirPath = malloque(4096);
    strcpy(dirPath, path);
    char *lastSlash = strrchr(dirPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';
    }
	
    if (opendir(dirPath) == 0) {
	return false;
    }
    return true;
}
