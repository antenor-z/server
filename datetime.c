#include "datetime.h"

char* datetime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *ret = malloque(25);
    sprintf(ret, "%d/%d/%d %d:%d:%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return ret;
}