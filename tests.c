#include <stdio.h>
#include <stdlib.h>

#include "kutils.h"

int test_error_control(void);

void
run_test(
        char *name,
        int (*test)(void))
{
    int e;

    printf("%s", name);
    e = test();
    printf("%40s\n", e ? "FAIL" : "OK");

    if (e) {
        abort();
    }
}

int
main(void)
{
    uint32_t required_size;
    if (ku_stream_from_file("example.txt", NULL, &required_size, KU_STREAM_FLAGS_NONE)) {
        printf("Failed to get required size: %s\n", ku_error_get());
    }

    uint8_t          buffer[required_size];
    struct ku_stream *stream = (struct ku_stream *) buffer;

    if (ku_stream_from_file("example.txt", stream, &required_size, KU_STREAM_FLAGS_NONE)) {
        printf("Failed to initialize stream: %s\n", ku_error_get());
    }

    run_test("test_error_control", test_error_control);

    return 0;
}
