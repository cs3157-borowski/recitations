#
# Notes: 
# - This is just one Makefile that works for this single-source project
# - There are other, perhaps better, ways to write a Makefile
# - This Makefile may not work for your projects
# - Ensure you understand each line of the code and make necessary changes 
#   if you want to adopt this Makefile for your projects
# - Feel free to improve this Makefile and share your way on Ed!
#
CC     = gcc
C_FILE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(C_FILE))
OBJ    = $(patsubst %.c,%.o,$(C_FILE))
CFLAGS = -g -Wall -Werror -pedantic-errors
DEPS   = bitoperators-solutions.h

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe
