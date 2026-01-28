CC = gcc
TARGET = build/code-format
SOURCES = main.c file.c alloc.c format.c

default: 
	cls
	$(CC) -Wall -Wextra -Werror $(SOURCES) -o $(TARGET)
	.\$(TARGET)