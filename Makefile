# Makefile for mineget - Licensed under Apache 2.0 - See LICENSE for more info

CFLAGS = -c -ansi -Wall -Wextra -Wpedantic -Ilib/ $(shell pkg-config libcurl --cflags)
LDFLAGS = $(shell pkg-config libcurl --libs)

SOURCES = src/main.c lib/AccountsClient.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mineget


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
	rm -f core.* vgcore.* callgrind.out.*
