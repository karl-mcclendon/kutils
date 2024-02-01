#pragma once

#include <stdint.h>

#include "consts.h"

/**
 * Stream flags.
 */
enum ku_stream_flags {
    KU_STREAM_FLAGS_NONE = 0
};

/**
 * Encapsulates stream data. This structure is intentionally opaque.
 */
struct ku_stream;



/**
 * Closes a stream.
 *
 * This function must be called to close any opened stream.
 *
 * @param io the stream to close
 */
void ku_stream_close(struct ku_stream *io);

/**
 * Initializes a stream for reading from a specified file.
 *
 * This function can be used in two modes:
 * 1. To query the required buffer size for a stream:
 *    Pass NULL as `stream_buffer` and a pointer to a variable to hold the size as `stream_buffer_size`. The required
 *    size will be stored in the variable pointed by `stream_buffer_size`.
 *
 *    Example:
 *    @code{.c}
 *    uint32_t required_size;
 *    if (ku_stream_from_file("example.txt", NULL, &required_size, KU_STREAM_FLAGS_NONE)) {
 *        printf("Failed to get required size: %s\n", ku_error_get());
 *    }
 *    @endcode
 *
 * 2. To initialize the stream with a provided buffer:
 *    Pass a pre-allocated buffer and its size. The function initializes the stream for the file's content.
 *
 *    Example:
 *    @code{.c}
 *    uint32_t required_size;
 *    if (ku_stream_from_file("example.txt", NULL, &required_size, KU_STREAM_FLAGS_NONE)) {
 *        printf("Failed to get required size: %s\n", ku_error_get());
 *    }
 *
 *    uint8_t buffer[required_size];
 *    struct ku_stream *stream = (struct ku_stream *) buffer;
 *
 *    if (ku_stream_from_file("example.txt", stream, &required_size, KU_STREAM_FLAGS_NONE)) {
 *        printf("Failed to initialize stream: %s\n", ku_error_get());
 *    }
 *    @endcode
 *
 * @param filename The path to the file to be opened for the stream.
 * @param stream_buffer A pointer to the pre-allocated buffer for the stream, or NULL to query the required size.
 * @param stream_buffer_size A pointer to the size of `stream_buffer`. On  return, this will be set to the actual size
 *        used or required.
 * @param ops Bitwise OR of flags from `ku_stream_flags` to control stream behavior.
 *
 * @return KU_SUCCESS if the operation is successful, or KU_ERROR if an error occurs.
 */
enum ku_success ku_stream_from_file(const char *filename, struct ku_stream *stream_buffer, uint32_t *stream_buffer_size, enum ku_stream_flags flags);
