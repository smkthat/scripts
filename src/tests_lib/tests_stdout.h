/**
 * @file tests_stdout.h
 * @brief Module for redirecting and comparing stdout output.
 *
 * This module provides functionality to redirect stdout to a temporary file,
 * capture the output, and compare it with a reference file. It is useful for
 * testing functions that produce output to stdout.
 *
 * Example usage:
 * @code
 * #include "tests_stdout.h"
 *
 * int test_print_text() {
 *     int test_result = TEST_FAIL;
 *
 *     // Initialize the comparator with a buffer size and data type
 *     StdoutComparator *comparator = initialize_comparator(1024, CHAR_TYPE);
 *     if (redirect_stdout(comparator, "temp_output.tmp")) {
 *         // Perform operations that produce stdout output
 *         printf("Hello, World!");
 *
 *         // Capture the output
 *         if (catch_stdout(comparator)) {
 *             // Compare the captured output with the expected output file
 *             test_result = compare_with_file(comparator, "expected_output.txt");
 *         }
 *
 *         // Clean up resources
 *         destroy_comparator(comparator);
 *     }
 *
 *     return test_result;
 * }
 * @endcode
 */

#ifndef TESTS_STDOUT_H
#define TESTS_STDOUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/**
 * @brief Enum to specify the data type for comparison.
 *
 * This enum is used to determine whether the comparison should be done
 * using `char` or `wchar_t` data types. It helps in managing the buffer
 * and reading operations accordingly.
 */
typedef enum {
    CHAR_TYPE, /**< Use char for comparison. */
    WCHAR_TYPE /**< Use wchar_t for comparison. */
} StdoutDataType;

/**
 * @brief Structure to manage stdout redirection and comparison.
 *
 * This structure holds the necessary information to redirect stdout
 * to a temporary file, capture its output, and compare it with a
 * reference file. It includes a buffer for storing the captured output
 * and the original stdout stream for restoration.
 */
typedef struct {
    FILE *original_stdout;    /**< Pointer to the original stdout stream. */
    FILE *temp_file;          /**< Pointer to the temporary file used for stdout redirection. */
    void *buffer;             /**< Buffer for reading file contents. */
    int buffer_size;          /**< Size of the buffer. */
    StdoutDataType data_type; /**< Data type for comparison. */
} StdoutComparator;

/**
 * @brief Initializes a StdoutComparator structure.
 *
 * Allocates and initializes a StdoutComparator structure with the specified
 * buffer size and data type. The buffer is allocated based on the data type
 * (either `char` or `wchar_t`). If allocation fails, returns NULL.
 *
 * @param[in] buffer_size Size of the buffer to allocate.
 * @param[in] data_type Type of data for comparison (CHAR_TYPE or WCHAR_TYPE).
 * @return Pointer to the initialized StdoutComparator, or NULL on failure.
 */
StdoutComparator *init_comparator(int buffer_size, StdoutDataType data_type);

/**
 * @brief Redirects stdout to a temporary file.
 *
 * Redirects the standard output stream to a specified temporary file,
 * allowing the capture of output for later comparison. Returns non-zero
 * on success, zero on failure.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 * @param[in] tmp_path Path to the temporary file.
 * @return Non-zero on success, zero on failure.
 */
int redirect_stdout(StdoutComparator *comparator, const char *tmp);

/**
 * @brief Captures the current stdout output into the buffer.
 *
 * Reads the contents of the temporary file (where stdout was redirected)
 * into the buffer of the StdoutComparator. The reading is performed based
 * on the specified data type (CHAR_TYPE or WCHAR_TYPE). Restores the original
 * stdout after capturing.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 * @return Non-zero on success, zero on failure.
 */
int catch_stdout(StdoutComparator *comparator);

/**
 * @brief Compares the captured stdout output with the contents of a source file.
 *
 * Opens the specified source file and compares its contents with the buffer
 * of the StdoutComparator. The comparison is performed based on the specified
 * data type (CHAR_TYPE or WCHAR_TYPE). Returns non-zero if the contents match,
 * zero otherwise.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 * @param[in] src_path Path to the source file for comparison.
 * @return Non-zero if the contents match, zero otherwise.
 */
int compare_with_file(const StdoutComparator *comparator, const char *src_path);

/**
 * @brief Restores the original stdout stream.
 *
 * Closes the temporary file used for stdout redirection and restores the
 * standard output stream to its original state.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 */
void restore_origin_stdout(StdoutComparator *comparator);

/**
 * @brief Cleans up resources used by the StdoutComparator structure.
 *
 * Frees the allocated memory for the buffer and closes any open files
 * associated with the StdoutComparator. This function should be called
 * to prevent memory leaks.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 */
void destroy_comparator(StdoutComparator *comparator);

#endif  // TESTS_STDOUT_H
