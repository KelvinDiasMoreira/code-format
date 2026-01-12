CC = gcc
TARGET = compiled
SOURCES = main.c file.c

default: 
	cls
	$(CC) -Wall -Wextra $(SOURCES) -o $(TARGET)
	.\$(TARGET)