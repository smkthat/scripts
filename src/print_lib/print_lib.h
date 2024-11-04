#ifndef PRINT_LIB_H
#define PRINT_LIB_H

#include <ctype.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define PRINTBOX_DEFAULT_LOCALE "ru_RU.UTF-8"
#define PRINTBOX_BORDER_CUSTOM 0
#define PRINTBOX_BORDER_SIMPLE 1
#define PRINTBOX_BORDER_SINGLE 2
#define PRINTBOX_BORDER_DOUBLE 3

typedef struct {
    int max_width;
    const char* locale;
    int word_wrap;
    wchar_t tl_corner;
    wchar_t tr_corner;
    wchar_t ml_corner;
    wchar_t mr_corner;
    wchar_t br_corner;
    wchar_t bl_corner;
    wchar_t h_corner;
    wchar_t v_corner;
} PrintBox;

PrintBox* init_print_box(int line_width, const char* locale, const int border_type, int word_wrap, ...);
void print_header(PrintBox* box);
void print_divider(PrintBox* box);
void print_footer(PrintBox* box);
void print_header_with_text(PrintBox* box, const wchar_t* header_text);
void print_divider_with_text(PrintBox* box, const wchar_t* header_text);
void print_footer_with_text(PrintBox* box, const wchar_t* header_text);
void print_line(PrintBox* box, const wchar_t* text, unsigned long start_index);
void print_text(PrintBox* box, const wchar_t* text);
void destroy_print_box(PrintBox* box);

#endif  // PRINT_LIB_H
