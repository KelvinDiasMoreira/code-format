CC = gcc
TARGET = compiled
SOURCES = main.c file.c

default: 
	cls
	$(CC) $(SOURCES) -o $(TARGET)
	.\$(TARGET)