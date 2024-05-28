#include "getFileType.h"

void getFileType(char* pathWithBase, char* ret) {
    char* strFileExtension;
    char *dot = strrchr(pathWithBase, '.');
    if(!dot || dot == pathWithBase) {
        strFileExtension = "html";
    }
    else {
        strFileExtension = dot + 1;
    }
    if (strcmp(strFileExtension, "png") == 0) {
        strcpy(ret, "Content-Type: image/png\n");
    }
    else if (strcmp(strFileExtension, "jpg") == 0 || strcmp(strFileExtension, "jpeg") == 0) {
        strcpy(ret, "Content-Type: image/jpeg\n");
    }
    else if (strcmp(strFileExtension, "gif") == 0) {
        strcpy(ret, "Content-Type: image/gif\n");
    }
    else if (strcmp(strFileExtension, "js") == 0) {
        strcpy(ret, "Content-Type: application/javascript\n");
    }
    else if (strcmp(strFileExtension, "css") == 0) {
        strcpy(ret, "Content-Type: text/css\n");
    }
    else if (strcmp(strFileExtension, "txt") == 0) {
        strcpy(ret, "Content-Type: text/plain\n");
    }
    else if (strcmp(strFileExtension, "ico") == 0) {
        strcpy(ret, "Content-Type: image/x-icon\n");
    }
    else {
        strcpy(ret, "Content-Type: text/html\n");
    }
}