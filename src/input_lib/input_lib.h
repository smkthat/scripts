#ifndef INPUT_LIB_H
#define INPUT_LIB_H

/**
 * @brief Reads characters from standard input into a dynamically allocated array.
 *
 * This function reads characters from the standard input stream into the provided array.
 * It dynamically resizes the array as needed to accommodate the input. The input is
 * terminated by a newline character or EOF. The function ensures that the array is
 * null-terminated.
 *
 * @param[in,out] array A pointer to the initial memory allocated for storing input characters.
 *                      Must not be NULL.
 * @param[in] size A pointer to an integer representing the initial size of the allocated memory.
 *                 This value is used to determine when to resize the array.
 *
 * @return Returns a pointer to the array containing the input characters. The array is
 *         dynamically resized as needed. Returns NULL if memory reallocation fails.
 *
 * @note This function uses `realloc` to resize the array and assumes that the caller
 *       has initially allocated memory for the array. The caller is responsible for
 *       freeing the allocated memory.
 *
 * @example
 * int size = 10;
 * char *input = (char *)calloc(size, sizeof(char));
 * if (input != NULL) {
 *     input = scan_input_characters(input, &size);
 *     if (input != NULL) {
 *         printf("Input: %s\n", input);
 *         free(input);
 *     } else {
 *         printf("Failed to read input.\n");
 *     }
 * } else {
 *     printf("Failed to allocate initial memory.\n");
 * }
 */
char *scan_input_characters(char *array, const int *size);

/**
 * @brief Allocates memory for a string and reads input from standard input.
 *
 * This function allocates memory for a string based on the specified `default_size`.
 * It then reads characters from the standard input stream into the allocated memory.
 * The input is terminated by a newline character or EOF.
 *
 * @param[in] default_size The initial size of the memory to allocate for the input string.
 *                         Must be greater than 1 to accommodate the input and null terminator.
 *
 * @return Returns a pointer to the allocated string containing the input characters.
 *         Returns NULL if memory allocation fails or if `default_size` is not greater than 1.
 *
 * @note This function uses `calloc` to allocate memory and assumes that `scan_input_characters`
 *       is a helper function that reads characters into the allocated memory.
 *       The caller is responsible for freeing the allocated memory.
 *
 * @example
 * int size = 10;
 * char *input = input_string(size);
 * if (input != NULL) {
 *     printf("Input: %s\n", input);
 *     free(input);
 * } else {
 *     printf("Failed to allocate memory or invalid size.\n");
 * }
 */
char *input_sting(int size);

/**
 * @brief Reads an single integer from standard input and validates it.
 *
 * This function attempts to read an integer value from the standard input stream.
 * It checks if the input is a valid integer followed by a newline character.
 * If the input is valid, the integer is stored in the location pointed to by `digit`.
 * If the input is invalid, the function clears the input buffer up to the next newline or EOF.
 *
 * @param[out] digit A pointer to an integer where the input value will be stored if valid.
 *
 * @return Returns `1` if the input is a valid integer followed by a newline character.
 *         Returns `0` if the input is invalid.
 *
 * @note This function uses `scanf` for input and `getchar` to clear the input buffer.
 *       It is designed to handle simple integer input validation and should be used
 *       with caution in environments where input validation is critical.
 *
 * @example
 * int number;
 * if (input_digit(&number)) {
 *     printf("Valid input: %d\n", number);
 * } else {
 *     printf("Invalid input. Please enter a valid integer.\n");
 * }
 */
int input_single_digit(int *dst);

#endif
