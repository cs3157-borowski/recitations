CC = gcc
CFLAGS = -g -Wall -Wno-unused-variable -Wpedantic -std=c17
LDFLAGs =
LDLIBS =

STARS = \
		starfork-s1 \
		starfork-s2 \
		starfork-s3 \
		starfork-s4 \
		starfork-s5 \
		starfork-s6 \
		starfork-s7 \

.PHONY: default
default: $(STARS)

$(STARS):

starfork-s1.o: starfork.c
	$(CC) $(CFLAGS) -D S1 -c -o $@ $<

starfork-s2.o: starfork.c
	$(CC) $(CFLAGS) -D S2 -c -o $@ $<

starfork-s3.o: starfork.c
	$(CC) $(CFLAGS) -D S3 -c -o $@ $<

starfork-s4.o: starfork.c
	$(CC) $(CFLAGS) -D S4 -c -o $@ $<

starfork-s5.o: starfork.c
	$(CC) $(CFLAGS) -D S5 -c -o $@ $<

starfork-s6.o: starfork.c
	$(CC) $(CFLAGS) -D S6 -c -o $@ $<

starfork-s7.o: starfork.c
	$(CC) $(CFLAGS) -D S7 -c -o $@ $<

.PHONY: clean
clean:
	rm -rf a.out *.o starfork-s*
