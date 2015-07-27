#include "print_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

static int lock = 0;

#define LOCK(l) while (__sync_lock_test_and_set(&lock, 1)) {};
#define UNLOCK(l) __sync_lock_release(&lock);

void err_print(const char * str)
{
    LOCK(lock);

    // 内存复制
    size_t len = strlen(str);
    char * buf = (char *)malloc(len + 2);
    memcpy(buf, str, len);
    buf[len] = '\n';
    buf[len + 1] = '\0';

    fputs(buf, stderr);
    fflush(stderr);

    free(buf);

    UNLOCK(lock);
}

void std_print(const char * str)
{
    LOCK(lock)

    // 内存复制
    size_t len = strlen(str);
    char * buf = (char *)malloc(len + 2);
    memcpy(buf, str, len);
    buf[len] = '\n';
    buf[len + 1] = '\0';

    fputs(buf, stdout);
    fflush(stdout);

    free(buf);

    UNLOCK(lock);
}

void trace(const char * format, ...)
{
    LOCK(lock)

    va_list pArgList;

    va_start(pArgList, format);
    
    char tmp[256] = {0, };
    vsnprintf(tmp, sizeof(tmp), format, pArgList);
    fputs(tmp, stdout);
    fputc('\n', stdout);
    fflush(stdout);

    va_end(pArgList);

     UNLOCK(lock)
}
