CC = gcc
TARGET = build/code-format
SOURCES = main.c file.c alloc.c format.c
BUILD_FOLDER=build

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

default:
	@if [ ! -d "build" ]; then \
		mkdir -p "build"; \
	fi
	$(CLEAR_TAG)
	@echo $(CHECK_RESULT)
	@echo "CURR_OS -> $(CURR_OS)"
	$(CC) -Wall -Wextra -Werror $(SOURCES) -o $(TARGET)
	./$(TARGET)
