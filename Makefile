CC = gcc
TARGET = build/code-format
SOURCES = main.c file.c alloc.c format.c

# TODO: create build folder if not exist

default: 
	cls
	$(CC) -Wall -Wextra -Werror $(SOURCES) -o $(TARGET)
	.\$(TARGET)