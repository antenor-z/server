#include "getFileType.h"

/*
 * Used to set Content-Type header
 */
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
        strcpy(ret, "Content-Type: image/png");
    }
    else if (strcmp(strFileExtension, "jpg") == 0 || strcmp(strFileExtension, "jpeg") == 0) {
        strcpy(ret, "Content-Type: image/jpeg");
    }
    else if (strcmp(strFileExtension, "htm") == 0 || strcmp(strFileExtension, "html") == 0) {
        strcpy(ret, "Content-Type: text/html");
    }
    else if (strcmp(strFileExtension, "gif") == 0) {
        strcpy(ret, "Content-Type: image/gif");
    }
    else if (strcmp(strFileExtension, "js") == 0) {
        strcpy(ret, "Content-Type: application/javascript");
    }
    else if (strcmp(strFileExtension, "css") == 0) {
        strcpy(ret, "Content-Type: text/css");
    }
    else if (strcmp(strFileExtension, "svg") == 0) {
        strcpy(ret, "Content-Type: image/svg+xml");
    }
    else if (strcmp(strFileExtension, "txt") == 0) {
        strcpy(ret, "Content-Type: text/plain");
    }
    else if (strcmp(strFileExtension, "ico") == 0) {
        strcpy(ret, "Content-Type: image/x-icon");
    }
    else if (strcmp(strFileExtension, "pdf") == 0) {
        strcpy(ret, "Content-Type: application/pdf");
    }
    else {
        strcpy(ret, "Content-Type: text/plain");
    }
}