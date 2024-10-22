#ifndef INPUT_LIB_H
#define INPUT_LIB_H

/**
 * @brief Default initial size for character array allocation.
 *
 * This constant defines the default size used for the initial allocation of a character array.
 * It is utilized when dynamically allocating memory for storing input strings, ensuring that
 * there is sufficient space to accommodate typical input lengths.
 *
 * @note The value can be adjusted based on expected input size requirements.
 */
#define INPUT_DEFAULT_SIZE 11

/**
 * @brief Reads a line of text from standard input and returns it as a dynamically allocated string.
 *
 * This function reads a line of text from the standard input stream (stdin) and stores it in a dynamically
 * allocated buffer. The buffer is resized as needed to accommodate the input. The newline character at the
 * end of the input is replaced with a null terminator. If the input is successfully read, the function
 * returns a pointer to the buffer containing the input string. If memory allocation fails at any point,
 * the function returns `NULL`.
 *
 * @param[in] str A pointer to a previously allocated string that will be freed before reading new input.
 *                   This parameter can be `NULL` if no previous string needs to be freed.
 *
 * @return A pointer to the dynamically allocated string containing the input, or `NULL` if an error occurs.
 *
 * @note The caller is responsible for freeing the returned string to avoid memory leaks.
 *
 * @example
 * char *str = NULL;
 * str = input_string(str);
 * if (str != NULL) {
 *     printf("String: %s\n", str);
 *     free(str);
 * } else {
 *     printf("Failed to allocate memory.\n");
 * }
 */
char *input_str(char *str);

/**
 * @brief Reads an integer from standard input and stores it in the provided variable.
 *
 * This function reads a line of text from the standard input stream (stdin) and attempts to convert it
 * to an integer. The converted integer is stored in the variable pointed to by the `digit` parameter.
 * The function returns `1` if the input is a valid integer and `0` otherwise. If the input is not a valid
 * integer, the value pointed to by `digit` is not modified.
 *
 * @param[in] digit A pointer to an integer variable where the converted input will be stored if valid.
 *
 * @return An integer indicating the validity of the input:
 *         `1` if the input is a valid integer, `0` otherwise.
 *
 * @example
 * int number;
 * if (input_digit(&number)) {
 *     printf("Valid input: %d\n", number);
 * } else {
 *     printf("Invalid input. Please enter a valid integer.\n");
 * }
 */
int input_digit(int *digit);

#endif
