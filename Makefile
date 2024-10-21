# Variables
VERSION=0.0.1
STAGE=all # debug | release | tests | all

# Define project paths
PWD:=$(dir $(realpath $(firstword $(MAKEFILE_LIST))))
SRC_DIR=$(PWD)src/
TESTS_DIR=$(PWD)tests/
BUILD_DIR=$(PWD)build/
BUILD_TESTS_DIR=$(PWD)build/tests/
LOGS_DIR=$(PWD)logs/

# Check gcc installing
CC:=$(shell which gcc 2>/dev/null)
ifeq ($(CC),)
$(error "gcc not found. Please install gcc or ensure it is in your PATH.")
endif

# Options
CC_FLAGS=-Wall -Werror -Wextra -std=c11
CC_DEBUG_FLAGSS=-g -O0 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
CPPCHECK_FLAGS=--enable=all --std=c11 --suppress=missingIncludeSystem --suppress=unusedFunction

# Run clang and cpp checks
check:
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n\n" "💅 clang check"
	@if clang-format -n $(SRC_DIR)**/*.[ch]; then \
		echo "\033[0;32mNo style errors found.\033[0m\n\n"; \
	else \
		"\033[0;31mStyle errors detected! Please run `make format` to fix them.\033[0m\n\n"; \
		exit 1; \
	fi
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n\n" "📋 cpp check"
	cppcheck $(CPPCHECK_FLAGS) --checkers-report=$(LOGS_DIR)cppcheck_src.log $(SRC_DIR)
	cppcheck $(CPPCHECK_FLAGS) --suppress=ignoredReturnValue --checkers-report=$(LOGS_DIR)cppcheck_tests.log $(TESTS_DIR)
	@echo "\n\033[0;32mAll checks complete.\033[0m";

# Run clang formatting
format:
	@printf "+--------------------+\n│ %-20s │\n+--------------------+\n" "💅 clang format"
	@echo clang-format -i $(SRC_DIR)**/*.[ch]
	@echo clang-format -i $(TESTS_DIR)*.[ch] $(TESTS_DIR)**/*.[ch]
	@find $(SRC_DIR) -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
	@find $(TESTS_DIR) -type f \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} +
	@echo "\n\033[0;32mFormat complete.\033[0m\n\n";


# Show current Makefile version
v:
	@echo $(VERSION)

# Show current configuration
config:
	@echo "\n\033[0;32mMakefile $(VERSION)\033[0m"
	@echo
	@echo "\033[0;32mCommands\033[0m:"
	@printf "  %-15s %s\n" "make check" "- Run clang and cpp checks"
	@printf "  %-15s %s\n" "make format" "- Run clang formatting"
	@printf "  %-15s %s\n" "make config" "- Show current Makefile configuration"
	@printf "  %-15s %s\n" "make v" "- Show current Makefile version"
	@echo
	@echo "\033[0;32mCompiler\033[0m:"
	@printf "  %-15s %s\n" "gcc" "$(CC)"
	@printf "  %-15s %s\n" "build_flags" "$(CC_FLAGS)"
	@printf "  %-15s %s\n" "debug_flags" "$(CC_DEBUG_FLAGSS)"
	@echo
	@echo "\033[0;32mPaths\033[0m:"
	@printf "  %-15s %s\n" "root" "$(PWD)"
	@printf "  %-15s %s\n" "src" "$(SRC_DIR)"
	@printf "  %-15s %s\n" "tests" "$(TESTS_DIR)"
	@printf "  %-15s %s\n" "logs" "$(LOGS_DIR)"
	@printf "  %-15s %s\n" "build" "$(BUILD_DIR)"
	@printf "  %-15s %s\n" "build/tests" "$(BUILD_TESTS_DIR)"
