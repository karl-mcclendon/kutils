#include "kutils.h"

#include <stdio.h>
#include <stdarg.h>

struct error {
    char *message;
    int message_len;
};

struct error *
error_get_global(void)
{
    static char global_error_message[128] = {0};
    static struct error global_error = {
        .message = global_error_message,
        .message_len = sizeof(global_error_message)
    };

    return &global_error;
}

const char *
ku_error_get(void)
{
    return error_get_global()->message;
}

enum ku_success
ku_error_set(
        char *err_message_fmt,
        ...)
{
    va_list      ap;
    int          e;
    struct error *err;

    err = error_get_global();

    va_start(ap, err_message_fmt);
    e = vsnprintf(err->message, err->message_len, err_message_fmt, ap);
    va_end(ap);

    return e < 0 ? KU_ERROR : KU_SUCCESS;
}
