#include "kutils.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

enum stream_type {
    STREAM_TYPE_FILE
};

struct ku_stream {
    enum stream_type type;

    void (*close)(struct ku_stream *);
};

struct stream_file {
    struct ku_stream stream;

    FILE *fp;
};

void
file_stream_close(
    struct ku_stream *s)
{
    fclose(((struct stream_file *) s)->fp);
}

enum ku_success
ku_stream_from_file(
    const char *filename,
    void *buffer,
    uint32_t *buffer_size,
    enum ku_stream_flags flags)
{
    if (buffer == NULL) {
        *buffer_size = sizeof(struct stream_file);

        return 0;
    } else if (*buffer_size < sizeof(struct stream_file)) {
        ku_error_set("io_size too small");

        return -1;
    } else if (flags != KU_STREAM_FLAGS_NONE) {
        ku_error_set("unsupported flags");

        return -1;
    }

    struct stream_file *s = (struct stream_file *) buffer;
    s->fp = fopen(filename,"r+b");
    if (s->fp == NULL) {
        ku_error_set("could not open file: %s", strerror(errno));

        return -1;
    }


    s->stream.type  = STREAM_TYPE_FILE;
    s->stream.close = file_stream_close;

    return 0;
}

void
ku_stream_close(
    struct ku_stream *io)
{
    io->close(io);
}
