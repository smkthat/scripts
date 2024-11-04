#include <ctype.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define BORDER_TYPE_CUSTOM 0
#define BORDER_TYPE_SIMPLE 1
#define BORDER_TYPE_ASCII_SINGLE 2
#define BORDER_TYPE_ASCII_DOUBLE 3

typedef struct {
    int max_width;
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

PrintBox* init_print_box(int line_width, const int border_type, int word_wrap, ...) {
    setlocale(LC_CTYPE, "");
    PrintBox* box = (PrintBox*)malloc(sizeof(PrintBox));

    if (box) {
        box->max_width = line_width;
        box->word_wrap = word_wrap;

        va_list args;
        va_start(args, word_wrap);

        switch (border_type) {
            case BORDER_TYPE_CUSTOM: {
                box->tl_corner = va_arg(args, int);
                box->tr_corner = va_arg(args, int);
                box->mr_corner = va_arg(args, int);
                box->ml_corner = va_arg(args, int);
                box->br_corner = va_arg(args, int);
                box->bl_corner = va_arg(args, int);
                box->h_corner = va_arg(args, int);
                box->v_corner = va_arg(args, int);
                break;
            }
            case BORDER_TYPE_ASCII_SINGLE: {
                box->tl_corner = L'┌';
                box->tr_corner = L'┐';
                box->mr_corner = L'┤';
                box->ml_corner = L'├';
                box->br_corner = L'┘';
                box->bl_corner = L'└';
                box->h_corner = L'─';
                box->v_corner = L'│';
                break;
            }
            case BORDER_TYPE_ASCII_DOUBLE: {
                box->tl_corner = L'╔';
                box->tr_corner = L'╗';
                box->ml_corner = L'╠';
                box->mr_corner = L'╣';
                box->br_corner = L'╝';
                box->bl_corner = L'╚';
                box->h_corner = L'═';
                box->v_corner = L'║';
                break;
            }
            case BORDER_TYPE_SIMPLE:
            default: {
                box->tl_corner = L'+';
                box->tr_corner = L'+';
                box->mr_corner = L'+';
                box->ml_corner = L'+';
                box->br_corner = L'+';
                box->bl_corner = L'+';
                box->h_corner = L'-';
                box->v_corner = L'|';
                break;
            }
        }
    }

    return box;
}

void print_header(PrintBox* box) {
    wprintf(L"%lc", box->tl_corner);
    for (int i = 0; i < box->max_width + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->tr_corner);
}

void print_header_with_text(PrintBox* box, const char* header_text) {
    int padding = (int)(box->max_width - strlen(header_text) + 2) / 2;
    wprintf(L"%lc", box->tl_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    printf("%s", header_text);
    for (int i = 0; i < box->max_width - padding - (int)strlen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->tr_corner);
}

void print_devider_with_text(PrintBox* box, const char* header_text) {
    int padding = (int)(box->max_width - strlen(header_text) + 2) / 2;
    wprintf(L"%lc", box->ml_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    printf("%s", header_text);
    for (int i = 0; i < box->max_width - padding - (int)strlen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->mr_corner);
}

void print_footer(PrintBox* box) {
    wprintf(L"%lc", box->bl_corner);
    for (int i = 0; i < box->max_width + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->br_corner);
}

void print_footer_with_text(PrintBox* box, const char* header_text) {
    int padding = (int)(box->max_width - strlen(header_text) + 2) / 2;
    wprintf(L"%lc", box->bl_corner);
    for (int i = 0; i < padding; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    printf("%s", header_text);
    for (int i = 0; i < box->max_width - padding - (int)strlen(header_text) + 2; i++) {
        wprintf(L"%lc", box->h_corner);
    }
    wprintf(L"%lc\n", box->br_corner);
}

void print_line(PrintBox* box, const char* text, unsigned long start_index) {
    wprintf(L"%lc ", box->v_corner);
    unsigned long text_len = strlen(text);
    unsigned long i = start_index;
    unsigned long printed_chars = 0;
    unsigned long last_space_index = start_index;

    while (i < text_len && printed_chars < box->max_width) {
        if (text[i] == '\n') {
            break;
        }
        if (isspace(text[i])) {
            last_space_index = i;
        }
        printf("%c", text[i]);
        i++;
        printed_chars++;
    }

    if (box->word_wrap && i < text_len && !isspace(text[i]) && last_space_index > start_index) {
        i = last_space_index + 1;
        printed_chars = last_space_index - start_index;
        wprintf(L"\r%lc ", box->v_corner);
        for (unsigned long j = start_index; j < i - 1; j++) {
            printf("%c", text[j]);
        }
    }

    for (unsigned long j = printed_chars; j < box->max_width; j++) {
        printf(" ");
    }
    wprintf(L" %lc\n", box->v_corner);

    if (i < text_len && text[i] == '\n') {
        i++;
    }

    if (i < text_len) {
        print_line(box, text, i);
    }
}

void print_text(PrintBox* box, const char* text) { print_line(box, text, 0); }

void destroy_print_box(PrintBox* box) {
    if (box) {
        free(box);
    }
}

int main() {
    char* text =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n\nNunc quis nulla et orci sagittis "
        "sodales egestas vehicula nulla. Cras sollicitudin maximus libero, eu vehicula tellus luctus non. "
        "Donec sit amet libero ut ipsum ornare scelerisque. Proin nec sapien vitae diam rhoncus convallis. "
        "Est nec leo lacinia mattis. Duis ornare auctor massa quis tincidunt. Curabitur egestas odio id "
        "pulvinar rhoncus. Ut sed ante a eros aliquet efficitur. Phasellus eget felis tristique, bibendum "
        "diam sodales, maximus urna.\n\n\n"
        "Etiam gravida gravida mauris a finibus. Suspendisse suscipit dolor eget venenatis convallis. Nam "
        "maximus elit nec quam congue lobortis. Sed sit amet maximus erat, eget hendrerit diam. Etiam "
        "molestie molestie nisl non euismod. Nullam sed auctor quam, eu iaculis enim. Ut tempus metus vitae "
        "dui tristique rhoncus.\n\n";
    PrintBox* box = init_print_box(80, BORDER_TYPE_SIMPLE, 1, L'*', L'*', L'+', L'+', L'*', L'*', L'-', L'|');

    if (!box) {
        fprintf(stderr, "Failed to initialize PrintBox\n");
        return 1;
    }

    print_header_with_text(box, " This is header text ");
    print_text(box, text);
    print_devider_with_text(box, " This is middle text ");
    print_text(box, text);
    print_footer_with_text(box, " This is footer text ");

    destroy_print_box(box);
    return 0;
}
