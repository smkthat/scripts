#!/bin/bash

log_info() {
    echo "INFO: $1"
}

log_error() {
    echo "ERROR: $1" >&2
}

check_dependencies() {
    command -v clang-format >/dev/null 2>&1 || { log_error "clang-format не установлен."; exit 1; }
    command -v gcc >/dev/null 2>&1 || { log_error "gcc не установлен."; exit 1; }
}

format_code() {
    if [ "$SHOULD_FORMAT" = true ]; then
        log_info "Форматирование..."
        clang-format -n "$1" || { log_error "clang-format обнаружил проблемы."; exit 1; }
        clang-format -i "$1"
        log_info "Готово"
    else
        log_info "Форматирование пропущено из-за флага --no-format"
    fi
}

compile_code() {
    log_info "Компиляция..."
    if [ "$SHOULD_MEM_CHECK" = true ]; then
        gcc -g -O0 -Wall -Werror -Wextra -fsanitize=address "$1" -o "build/$2" || { log_error "Ошибка компиляции."; exit 1; }
    else
        gcc -g -O0 -Wall -Werror -Wextra "$1" -o "build/$2" || { log_error "Ошибка компиляции."; exit 1; }
    fi
    log_info "Готово"
}

run_program() {
    if [ "$SHOULD_START" = true ]; then
        log_info "Запуск $1"
        echo "(для отмены запуска нажмите Ctrl + C)"
        "./build/$1"
    else
        log_info "Запуск пропущен из-за флага --no-start"
    fi
}

main() {
    log_info "Старт сборки"

    SHOULD_START=true
    SHOULD_FORMAT=true
    SHOULD_MEM_CHECK=true

    while [[ $# -gt 0 ]]; do
        case $1 in
            --no-start)
                SHOULD_START=false
                shift
                ;;
            --no-format)
                SHOULD_FORMAT=false
                shift
                ;;
            --no-mem-check)
                SHOULD_MEM_CHECK=false
                shift
                ;;
            *)
                TARGET_FILE=$1
                shift
                ;;
        esac
    done

    if [ -z "$TARGET_FILE" ]; then
        log_error "Файл не указан"
        exit 1
    fi

    TARGET_FILE_WITHOUT_EXTENSION=$(basename "$TARGET_FILE" .c)

    if [[ ! "$TARGET_FILE" =~ \.c$ ]]; then
        log_error "Файл $TARGET_FILE не является C-файлом."
        exit 1
    fi

    check_dependencies

    format_code "$TARGET_FILE"

    if ! [ -d ./build ]; then
        mkdir build
    fi

    compile_code "$TARGET_FILE" "$TARGET_FILE_WITHOUT_EXTENSION"

    run_program "$TARGET_FILE_WITHOUT_EXTENSION"
}

main "$@"
