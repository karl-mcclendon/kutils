#include <string.h>
#include "kutils.h"

int
test_error_control(void)
{
    int e;

    ku_error_clear();

    if (ku_error_get() != NULL) {
        return -1;
    }

    e = ku_error_set("test %s", "me");
    if (e) {
        return -1;
    }

    e = strcmp(ku_error_get(), "test me");
    if (e) {
        return -1;
    }

    return 0;
}
