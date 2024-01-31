#include "kutils.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <libc.h>

#define MAX_ERROR_MESSAGE_LENGTH 256

char *error_message   = NULL;
int error_message_len = 0;

void
ku_error_clear(void)
{
    if (error_message != NULL) {
        free(error_message);
    }

    error_message     = NULL;
    error_message_len = 0;
}

const char *
ku_error_get(void)
{
    return error_message;
}

enum ku_success
ku_error_set(
        char *err_message_fmt,
        ...)
{
    va_list ap;
    int     e;

    va_start(ap, err_message_fmt);
    e = vsnprintf(NULL, 0, err_message_fmt, ap);
    va_end(ap);

    if (e < 0) {
        return KU_ERROR;
    }

    e = MIN(e, MAX_ERROR_MESSAGE_LENGTH - 1);

    if (e >= error_message_len) {
        if (error_message != NULL) {
            free(error_message);
        }

        error_message_len = e + 1;
        error_message     = malloc(error_message_len);

        if (error_message == NULL) {
            return KU_ERROR;
        }
    }

    va_start(ap, err_message_fmt);
    e = vsnprintf(error_message, error_message_len, err_message_fmt, ap);
    va_end(ap);

    return e < 0 ? KU_ERROR : KU_SUCCESS;
}
