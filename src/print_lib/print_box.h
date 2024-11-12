#ifndef PRINT_LIB_H
#define PRINT_LIB_H

#include <ctype.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

/**
 * @brief Default locale setting for PrintBox operations.
 *
 * This constant defines the default locale used for PrintBox operations, specifically
 * for character type functions. It is set to "ru_RU.UTF-8" to support Russian language
 * and UTF-8 encoding.
 */
#define PRINTBOX_DEFAULT_LOCALE "ru_RU.UTF-8"

/**
 * @brief Default buffer size for PrintBox operations.
 *
 * This constant defines the default size of the buffer used in PrintBox operations,
 * such as formatting and printing text. It is set to 1024 to provide sufficient space
 * for handling typical text content while maintaining performance.
 */
#define PRINTBOX_DEFAULT_BUFFER 1024

/**
 * @brief Enum for border types in PrintBox.
 *
 * This enum represents the different border type options for a PrintBox. It includes
 * options for custom, simple, single-line, and double-line borders.
 */
typedef enum {
    PRINTBOX_BORDER_CUSTOM, /**< Custom border type. */
    PRINTBOX_BORDER_SIMPLE, /**< Simple border type using basic ASCII characters. */
    PRINTBOX_BORDER_SINGLE, /**< Single-line border type using box-drawing characters. */
    PRINTBOX_BORDER_DOUBLE  /**< Double-line border type using box-drawing characters. */
} BorderType;

/**
 * @brief Structure representing a printable box with customizable borders.
 *
 * The PrintBox structure defines a printable box with customizable borders and text
 * formatting options. It includes parameters for the box's width, locale, word wrap
 * setting, and characters for each border element.
 */
typedef struct {
    unsigned long width; /**< The width of the line in PrintBox. */
    const char* locale;  /**< The locale used for character type functions. */
    int word_wrap;       /**< Flag indicating whether word wrap is enabled. */
    wchar_t tl_corner;   /**< Character for the top-left corner of the border. */
    wchar_t tr_corner;   /**< Character for the top-right corner of the border. */
    wchar_t ml_corner;   /**< Character for the middle-left corner of the border. */
    wchar_t mr_corner;   /**< Character for the middle-right corner of the border. */
    wchar_t br_corner;   /**< Character for the bottom-right corner of the border. */
    wchar_t bl_corner;   /**< Character for the bottom-left corner of the border. */
    wchar_t h_corner;    /**< Character for the horizontal border. */
    wchar_t v_corner;    /**< Character for the vertical border. */
} PrintBox;

/**
 * @brief Sets the border characters for a PrintBox based on the specified border type.
 *
 * This function configures the border characters of a PrintBox structure according to the
 * specified border type. It supports custom borders by accepting additional arguments
 * for each border character.
 *
 * @param[in] box A pointer to the PrintBox structure to configure.
 * @param[in] border_type The type of border to set (e.g., custom, single, double, simple):
 *                        PRINTBOX_BORDER_CUSTOM 0, PRINTBOX_BORDER_SIMPLE 1,
 *                        PRINTBOX_BORDER_SINGLE 2, PRINTBOX_BORDER_DOUBLE 3.
 * @param[in] args A va_list of additional arguments for custom border (wchar_t) corners:
 *                 top-left, top-right, middle-left, middle-right, bottom-left, bottom-right,
 *                 horizontal, vertical.
 */
void set_border_characters(PrintBox* box, BorderType border_type, va_list args);

/**
 * @brief Initializes a PrintBox structure with specified parameters.
 *
 * This function allocates and initializes a PrintBox structure with the given width,
 * locale, border type, and word wrap setting. It also sets the locale for character
 * type functions.
 *
 * @param[in] width The width of the PrintBox.
 * @param[in] locale The locale to use for character type functions (can be NULL for default).
 * @param[in] border_type The type of border to use for the PrintBox.
 * @param[in] word_wrap A flag indicating whether word wrap is enabled.
 * @param[in] ... Additional arguments for custom border (wchar_t) corners if needed:
 *                top-left, top-right, middle-left, middle-right, bottom-left, bottom-right,
 *                horizontal, vertical.
 *
 * @return A pointer to the initialized PrintBox, or NULL if allocation fails.
 */
PrintBox* init_print_box(unsigned long width, const char* locale, BorderType border_type, int word_wrap, ...);

/**
 * @brief Prints a line with text centered between border corners.
 *
 * This function prints a line with text centered between specified start and end
 * border corners, using a horizontal border character for padding.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] start_corner The character for the starting corner of the line.
 * @param[in] end_corner The character for the ending corner of the line.
 * @param[in] h_corner The character used for horizontal padding.
 * @param[in] text The text to be centered and printed.
 */
void print_line_with_text(const PrintBox* box, wchar_t start_corner, wchar_t end_corner, wchar_t h_corner,
                          const wchar_t* text);

/**
 * @brief Prints a line without text, using specified border corners.
 *
 * This function prints a line without any text, using specified start and end
 * border corners and a horizontal border character for the line.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] start_corner The character for the starting corner of the line.
 * @param[in] end_corner The character for the ending corner of the line.
 * @param[in] h_corner The character used for the horizontal line.
 */
void print_line_no_text(const PrintBox* box, wchar_t start_corner, wchar_t end_corner, wchar_t h_corner);

/**
 * @brief Prints the header line of the PrintBox.
 *
 * This function prints the header line of the PrintBox using the top-left and
 * top-right corner characters and the horizontal border character.
 *
 * @param[in] box A pointer to the PrintBox structure.
 */
void print_header_line(const PrintBox* box);

/**
 * @brief Prints a divider line within the PrintBox.
 *
 * This function prints a divider line within the PrintBox using the middle-left
 * and middle-right corner characters and the horizontal border character.
 *
 * @param[in] box A pointer to the PrintBox structure.
 */
void print_divider_line(const PrintBox* box);

/**
 * @brief Prints the footer line of the PrintBox.
 *
 * This function prints the footer line of the PrintBox using the bottom-left and
 * bottom-right corner characters and the horizontal border character.
 *
 * @param[in] box A pointer to the PrintBox structure.
 */
void print_footer_line(const PrintBox* box);

/**
 * @brief Prints a header line with centered text.
 *
 * This function prints a header line with text centered between the top-left and
 * top-right corner characters, using the horizontal border character for padding.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] header_text The text to be centered and printed in the header line.
 */
void print_header_line_with_text(const PrintBox* box, const wchar_t* header_text);

/**
 * @brief Prints a divider line with centered text.
 *
 * This function prints a divider line with text centered between the middle-left
 * and middle-right corner characters, using the horizontal border character for padding.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] header_text The text to be centered and printed in the divider line.
 */
void print_divider_line_with_text(const PrintBox* box, const wchar_t* header_text);

/**
 * @brief Prints a footer line with centered text.
 *
 * This function prints a footer line with text centered between the bottom-left and
 * bottom-right corner characters, using the horizontal border character for padding.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] header_text The text to be centered and printed in the footer line.
 */
void print_footer_line_with_text(const PrintBox* box, const wchar_t* header_text);

/**
 * @brief Prints a line of text within the PrintBox, handling word wrapping.
 *
 * This function prints a line of text within the PrintBox, starting from a specified
 * index. It handles word wrapping if enabled, ensuring text fits within the box width.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] text The text to be printed.
 * @param[in] start_index The starting index in the text for printing.
 */
void print_text_line(PrintBox* box, const wchar_t* text, unsigned long start_index);

/**
 * @brief Prints text within the PrintBox, starting from the beginning.
 *
 * This function prints text within the PrintBox, starting from the beginning of the
 * text. It handles word wrapping if enabled.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] text The text to be printed.
 */
void print_text(PrintBox* box, const wchar_t* text);

/**
 * @brief Formats and prints text within a PrintBox.
 *
 * This function formats a string using a specified format and additional arguments,
 * then prints the formatted text within the given PrintBox. It utilizes a buffer
 * defined by `PRINTBOX_DEFAULT_BUFFER` to store the formatted string.
 *
 * @param[in] box A pointer to the PrintBox structure where the text will be printed.
 * @param[in] format A wide-character string that contains the text to be written,
 *                   optionally embedded with format specifiers.
 * @param[in] ... Additional arguments providing data to be formatted according to
 *                the format specifiers in the format string.
 */
void print_formatted_text(PrintBox* box, const wchar_t* format, ...);

/**
 * @brief Prints a multiline header with text within the PrintBox.
 *
 * This function prints a multiline header with text within the PrintBox, including
 * a header line, the text, and a divider line.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] header_text The text to be printed in the header.
 */
void print_header_multiline(PrintBox* box, const wchar_t* header_text);

/**
 * @brief Prints a multiline divider with text within the PrintBox.
 *
 * This function prints a multiline divider with text within the PrintBox, including
 * a divider line, the text, and another divider line.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] divider_text The text to be printed in the divider.
 */
void print_divider_multiline(PrintBox* box, const wchar_t* divider_text);

/**
 * @brief Prints a multiline footer with text within the PrintBox.
 *
 * This function prints a multiline footer with text within the PrintBox, including
 * a divider line, the text, and a footer line.
 *
 * @param[in] box A pointer to the PrintBox structure.
 * @param[in] footer_text The text to be printed in the footer.
 */
void print_footer_multiline(PrintBox* box, const wchar_t* footer_text);

/**
 * @brief Destroys a PrintBox structure and frees its resources.
 *
 * This function frees the memory allocated for a PrintBox structure and resets
 * the locale setting for character type functions.
 *
 * @param[in] box A pointer to the PrintBox structure to be destroyed.
 */
void destroy_print_box(PrintBox* box);

#endif  // PRINT_LIB_H
