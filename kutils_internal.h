#pragma once

#define KU_ERROR_MESSAGE_SIZE 1024

/**
 * Only to be modified though `ku_error_set`.
 */
extern __thread char error_message[KU_ERROR_MESSAGE_SIZE];
