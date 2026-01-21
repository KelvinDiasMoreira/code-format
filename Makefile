CC = gcc
TARGET = build/c-format
SOURCES = main.c file.c alloc.c format.c

default: 
	cls
	$(CC) -Wall -Wextra -Werror $(SOURCES) -o $(TARGET)
	.\$(TARGET)