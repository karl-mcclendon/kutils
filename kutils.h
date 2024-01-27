#pragma once

#include <stdint.h>

/**
 * Used by kutils to indicate success or failure.
 */
enum ku_success {
    KU_ERROR = -1,
    KU_SUCCESS = 0
};

enum ku_stream_flags {
    KU_STREAM_FLAGS_NONE = 0
};

/**
 * Encapsulates stream data. This structure is intentionally opaque.
 */
struct ku_stream;

/**
 * Gets the error message.
 *
 * The error message is in a thread local variable. The variable has been initialized to zero, but it is bad practice to
 * access the variable before an error has been set.
 *
 * Example usage:
 * \code{.c}
 * printf("%s\n", ku_error_get());
 * \endcode
 *
 * @return a pointer to a null terminated string describing the most recent error
 */
const char *ku_error_get(void);

/**
 * Sets the error message.
 *
 * The error message is in a thread local variable of size KU_ERROR_MESSAGE_SIZE. If an error message exceeds that
 * length it will be truncated to fit and the null terminator will be added.
 *
 * Errno may be modified by this function, but only on failure. If the function return a failure errno will be set.
 *
 * Error message onventions:
 *     * keep brief but searchable
 *     * start error messages with a lower case
 *     * do not append a newline or period
 *
 * Example usage:
 * \code{.c}
 * if (!operation_successful) {
 *     ku_error_set("operation failed with error code: %d", error_code);
 * }
 * \endcode
 *
 * @param err_message_fmt a format string describing the error
 * @param ... the values for the format string
 *
 * @return KU_SUCCESS if the operation is successful, or KU_ERROR if an error occurs.
 */
enum ku_success ku_error_set(char *err_message_fmt, ...);

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
enum ku_success ku_stream_from_file(const char *filename, void *stream_buffer, uint32_t *stream_buffer_size, enum ku_stream_flags flags);
