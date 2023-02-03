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
