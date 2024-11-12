#include "print_box.h"

void set_border_characters(PrintBox* box, int border_type, va_list args) {
    if (box) {
        switch (border_type) {
            case PRINTBOX_BORDER_CUSTOM:
                box->tl_corner = va_arg(args, wchar_t);
                box->tr_corner = va_arg(args, wchar_t);
                box->ml_corner = va_arg(args, wchar_t);
                box->mr_corner = va_arg(args, wchar_t);
                box->bl_corner = va_arg(args, wchar_t);
                box->br_corner = va_arg(args, wchar_t);
                box->h_corner = va_arg(args, wchar_t);
                box->v_corner = va_arg(args, wchar_t);
                break;
            case PRINTBOX_BORDER_SINGLE:
                box->tl_corner = L'┌';
                box->tr_corner = L'┐';
                box->ml_corner = L'├';
                box->mr_corner = L'┤';
                box->bl_corner = L'└';
                box->br_corner = L'┘';
                box->h_corner = L'─';
                box->v_corner = L'│';
                break;
            case PRINTBOX_BORDER_DOUBLE:
                box->tl_corner = L'╔';
                box->tr_corner = L'╗';
                box->ml_corner = L'╠';
                box->mr_corner = L'╣';
                box->bl_corner = L'╚';
                box->br_corner = L'╝';
                box->h_corner = L'═';
                box->v_corner = L'║';
                break;
            case PRINTBOX_BORDER_SIMPLE:
            default:
                box->tl_corner = L'+';
                box->tr_corner = L'+';
                box->ml_corner = L'+';
                box->mr_corner = L'+';
                box->bl_corner = L'+';
                box->br_corner = L'+';
                box->h_corner = L'–';
                box->v_corner = L'|';
                break;
        }
    }
}

PrintBox* init_print_box(const unsigned long width, const char* locale, const int border_type, int word_wrap,
                         ...) {
    PrintBox* box = malloc(sizeof(PrintBox));

    if (box) {
        box->width = width;
        box->locale = locale ? locale : PRINTBOX_DEFAULT_LOCALE;
        box->word_wrap = word_wrap;

        va_list args;
        va_start(args, word_wrap);
        set_border_characters(box, border_type, args);
        va_end(args);

        if (!setlocale(LC_CTYPE, box->locale)) {
            fprintf(stderr, "Locale setting failed for %s\n", box->locale);
            free(box);
            box = NULL;
        }
    }

    return box;
}

void print_line_with_text(PrintBox* box, wchar_t start_corner, wchar_t end_corner, wchar_t h_corner,
                          const wchar_t* text) {
    int total_padding = (int)(box->width - wcslen(text) + 2);
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding;

    wprintf(L"%lc", start_corner);
    for (int i = 0; i < left_padding - 1; i++) {
        wprintf(L"%lc", h_corner);
    }
    wprintf(L" %ls ", text);
    for (int i = 0; i < right_padding - 1; i++) {
        wprintf(L"%lc", h_corner);
    }
    wprintf(L"%lc\n", end_corner);
}

void print_line_no_text(PrintBox* box, const wchar_t start_corner, const wchar_t end_corner,
                        const wchar_t h_corner) {
    wprintf(L"%lc", start_corner);
    for (int i = 0; i < (int)box->width + 2; i++) {
        wprintf(L"%lc", h_corner);
    }
    wprintf(L"%lc\n", end_corner);
}

void print_header_line(PrintBox* box) {
    print_line_no_text(box, box->tl_corner, box->tr_corner, box->h_corner);
}

void print_divider_line(PrintBox* box) {
    print_line_no_text(box, box->ml_corner, box->mr_corner, box->h_corner);
}

void print_footer_line(PrintBox* box) {
    print_line_no_text(box, box->bl_corner, box->br_corner, box->h_corner);
}

void print_header_line_with_text(PrintBox* box, const wchar_t* header_text) {
    print_line_with_text(box, box->tl_corner, box->tr_corner, box->h_corner, header_text);
}

void print_divider_line_with_text(PrintBox* box, const wchar_t* header_text) {
    print_line_with_text(box, box->ml_corner, box->mr_corner, box->h_corner, header_text);
}

void print_footer_line_with_text(PrintBox* box, const wchar_t* header_text) {
    print_line_with_text(box, box->bl_corner, box->br_corner, box->h_corner, header_text);
}

void print_text_line(PrintBox* box, const wchar_t* text, unsigned long start_index) {
    wprintf(L"%lc ", box->v_corner);
    unsigned long text_len = wcslen(text);
    unsigned long current_index = start_index;
    unsigned long printed_chars = 0;
    unsigned long last_space_index = start_index;
    int is_found_space = 0;

    while (current_index < text_len && printed_chars < box->width) {
        if (text[current_index] == '\n') {
            break;
        }
        if (isspace(text[current_index])) {
            last_space_index = current_index;
            is_found_space = 1;
        }
        wprintf(L"%lc", text[current_index]);
        current_index++;
        printed_chars++;
    }

    if (box->word_wrap && current_index < text_len && !isspace(text[current_index]) && is_found_space) {
        current_index = last_space_index + 1;
        printed_chars = last_space_index - start_index;
        wprintf(L"\r%lc ", box->v_corner);
        for (unsigned long j = start_index; j < current_index - 1; j++) {
            wprintf(L"%lc", text[j]);
        }
    }

    for (unsigned long j = printed_chars; j < box->width; j++) {
        wprintf(L" ");
    }
    wprintf(L" %lc\n", box->v_corner);

    if (current_index < text_len && text[current_index] == '\n') {
        current_index++;
    }

    if (current_index < text_len) {
        print_text_line(box, text, current_index);
    }
}

void print_text(PrintBox* box, const wchar_t* text) { print_text_line(box, text, 0); }

void printf_text(PrintBox* box, const wchar_t* format, ...) {
    wchar_t buffer[PRINTBOX_DEFAULT_BUFFER];
    va_list args;
    va_start(args, format);
    vswprintf(buffer, PRINTBOX_DEFAULT_BUFFER, format, args);
    va_end(args);
    print_text(box, buffer);
}

void print_header_multiline(PrintBox* box, const wchar_t* header_text) {
    print_header_line(box);
    print_text(box, header_text);
    print_divider_line(box);
}

void print_divider_multiline(PrintBox* box, const wchar_t* divider_text) {
    print_divider_line(box);
    print_text(box, divider_text);
    print_divider_line(box);
}

void print_footer_multiline(PrintBox* box, const wchar_t* footer_text) {
    print_divider_line(box);
    print_text(box, footer_text);
    print_footer_line(box);
}

void destroy_print_box(PrintBox* box) {
    if (box) {
        setlocale(LC_CTYPE, NULL);
        free(box);
        box = NULL;
    }
}