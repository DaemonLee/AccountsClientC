# Makefile for mineget - Licensed under Apache 2.0 - See LICENSE for more info

# Builds on Arch Linux with gcc 4.9.1

MAKEFLAGS += -j2

CC = gcc
# Don't ask me why make sometimes randomly decides to link with g++
CXX = gcc
CFLAGS = -c -ansi -Wall -Wextra -Wpedantic -O3 -march=native -flto -Ilib/
LDFLAGS = -flto -lcurl

SOURCES = src/main.c lib/AccountsClient.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = mineget


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
	rm -f core.*
	rm -f vgcore.*
	rm -f callgrind.out.*