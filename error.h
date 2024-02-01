#pragma once

#include "consts.h"

/**
 * Gets the most recent error message.
 *
 * Gets a null terminating string that contains a message that describes the most recent error. If called before a
 * message has been set the return value will be an empty string.
 *
 * Example usage:
 * \code{.c}
 * printf("%s\n", ku_error_get());
 * \endcode
 *
 * @return a pointer to a null terminated string
 */
const char *ku_error_get(void);

/**
 * Sets the error message.
 *
 * Max error message length is 128 bytes. If an error message exceeds that length it will be truncated to fit. This
 * function guarantees that a null terminator is added.
 *
 * Errno may be modified by this function, but only on failure. If the function return a failure errno will be set.
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
