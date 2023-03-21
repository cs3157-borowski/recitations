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
		starfork-s8 \
		starfork-s9 \

.PHONY: default
default: $(STARS)

$(STARS):

starfork-s1.o: starfork.c
	$(CC) $(CFLAGS) -DS1 -c -o $@ $<

starfork-s2.o: starfork.c
	$(CC) $(CFLAGS) -DS2 -c -o $@ $<

starfork-s3.o: starfork.c
	$(CC) $(CFLAGS) -DS3 -c -o $@ $<

starfork-s4.o: starfork.c
	$(CC) $(CFLAGS) -DS4 -c -o $@ $<

starfork-s5.o: starfork.c
	$(CC) $(CFLAGS) -DS5 -c -o $@ $<

starfork-s6.o: starfork.c
	$(CC) $(CFLAGS) -DS6 -c -o $@ $<

starfork-s7.o: starfork.c
	$(CC) $(CFLAGS) -DS7 -c -o $@ $<

starfork-s8.o: starfork.c
	$(CC) $(CFLAGS) -DS8 -c -o $@ $<

starfork-s9.o: starfork.c
	$(CC) $(CFLAGS) -DS9 -c -o $@ $<

.PHONY: clean
clean:
	rm -rf a.out *.o starfork-s*
