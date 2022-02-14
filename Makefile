CC = gcc
# CFLAGS = -Wall -pedantic -std=gnu99
CFLAGS = -Wall -pedantic -std=gnu99
LDFLAGS = -pthread 

all: prs thr

thr : thread
prs : process


clean: rm -f *.o 

.PHONY: all clean

