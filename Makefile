CC=gcc
CFLAGS=-Wall -std=c99 -g -pg
LDLIBS=-lm
SOURCES = stack.c rpn.c calc.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = stack.h rpn.h
EXECS = calc

all: $(EXECS)

calc: stack.o rpn.o calc.o
	$(CC) $(CFLAGS) -o calc stack.o rpn.o calc.o $(LDLIBS)

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm -f *.o
	
.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(EXECS)