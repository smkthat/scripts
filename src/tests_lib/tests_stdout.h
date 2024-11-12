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
 * Allocates memory for a new StdoutComparator and initializes its fields
 * based on the provided buffer size and data type. The buffer is allocated
 * according to the specified data type.
 *
 * @param[in] buffer_size Size of the buffer to allocate.
 * @param[in] data_type Type of data for comparison.
 * @return Pointer to the initialized StdoutComparator, or NULL on failure.
 *
 * @example
 * StdoutComparator *comparator = initialize_comparator(1024, CHAR_TYPE);
 * if (comparator == NULL) {
 *     // Handle allocation failure
 * }
 */
StdoutComparator *initialize_comparator(int buffer_size, StdoutDataType data_type);

/**
 * @brief Redirects stdout to a temporary file.
 *
 * Redirects the standard output stream to a specified temporary file.
 * This allows capturing the output for later comparison.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 * @param[in] tmp_path Path to the temporary file.
 * @return Non-zero on success, zero on failure.
 *
 * @example
 * if (!redirect_stdout(comparator, "temp_output.txt")) {
 *     // Handle redirection failure
 * }
 */
int redirect_stdout(StdoutComparator *comparator, const char *tmp_path);

/**
 * @brief Captures the current stdout output into the buffer.
 *
 * Reads the contents of the temporary file (where stdout was redirected)
 * into the buffer of the StdoutComparator. The reading is done based on
 * the specified data type.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 */
void catch_stdout(StdoutComparator *comparator);

/**
 * @brief Compares the captured stdout output with the contents of a source file.
 *
 * Opens the specified source file and compares its contents with the buffer
 * of the StdoutComparator. The comparison is done based on the specified
 * data type.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 * @param[in] src_path Path to the source file for comparison.
 * @return Non-zero if the contents match, zero otherwise.
 *
 * @example
 * if (compare_files(comparator, "expected_output.txt")) {
 *     // The outputs match
 * } else {
 *     // The outputs do not match
 * }
 */
int compare_files(StdoutComparator *comparator, const char *src_path);

/**
 * @brief Restores the original stdout stream.
 *
 * Restores the standard output stream to its original state, undoing
 * the redirection to the temporary file.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 */
void restore_stdout(StdoutComparator *comparator);

/**
 * @brief Cleans up resources used by the StdoutComparator structure.
 *
 * Frees the allocated memory for the buffer and closes any open files
 * associated with the StdoutComparator. It should be called to prevent
 * memory leaks.
 *
 * @param[in,out] comparator Pointer to the StdoutComparator structure.
 */
void cleanup(StdoutComparator *comparator);

#endif  // TESTS_STDOUT_H
