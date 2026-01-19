CC = gcc
TARGET = build/c-format
SOURCES = main.c file.c alloc.c

default: 
	cls
	$(CC) -Wall -Wextra $(SOURCES) -o $(TARGET)
	.\$(TARGET)