CC=gcc
LDFLAGS=-pthread

all: COVID_test

COVID_test: COVID_test.c
	$(CC) COVID_test.c -g $(LDFLAGS) -o COVID_test
.PHONY: clean

clean:
	rm -f COVID_test
