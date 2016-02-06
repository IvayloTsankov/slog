# simple Makefile

CC=g++
CFLAGS=-std=c++11 -DSLOGGING -DSLOGGING_DEBUG

all: slog

slog: test.cpp
	${CC} ${CFLAGS} $< -o $@

clean:
	rm slog
