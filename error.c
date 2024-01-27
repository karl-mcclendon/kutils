#include "kutils.h"
#include "kutils_internal.h"

#include <stdio.h>
#include <stdarg.h>

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
    e = vsnprintf(error_message, sizeof(error_message), err_message_fmt, ap);
    va_end(ap);

    return e < 0 ? KU_ERROR : KU_SUCCESS;
}
