CC = gcc
TARGET = build/code-format
SOURCES = main.c file.c alloc.c format.c
BUILD_FOLDER=build
DEFAULT_FILE_TEST=program.c

ifeq ($(OS),Windows_NT)
	CURR_OS := Windows
	CLEAR_TAG := cls
else
	OS_NAME := $(shell uname -s)
	ifeq ($(OS_NAME),Linux)
		CURR_OS := Linux
		CLEAR_TAG := clear
	endif
endif

ifeq ($($(wildcard $(DEFAULT_FILE_TEST))),)
ifeq ($(CURR_OS),Linux)
$(shell echo -e "#include <stdio.h>\nint main()           {\nint size = 200;\n           int buffer_pos = 20;\n\nreturn 0;\n   }" > program.c)
else
$(error cant create automatically, you need create a initial file to test -> program.c)
endif
endif

default:
	@if [ ! -d "$(BUILD_FOLDER)" ]; then \
		mkdir -p "$(BUILD_FOLDER)"; \
	fi
	$(CLEAR_TAG)
	@echo $(CHECK_RESULT)
	@echo "CURR_OS -> $(CURR_OS)"
	$(CC) -Wall -Wextra -Werror $(SOURCES) -o $(TARGET)
	./$(TARGET)
