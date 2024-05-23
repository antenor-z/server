#include "datetime.h"

char* datetime() {
    /*
     * Get current formated datetime
     */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *ret = malloque(25);
    sprintf(ret, "%02d/%02d/%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return ret;
}