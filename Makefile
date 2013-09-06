CC=gcc
CFLAGS=-Wall -std=c99 -g -pg
LDLIBS=-lm
SOURCES = utility.c stack.c rpn.c in.c calc.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = utility.h stack.h rpn.h in.h
EXECS = calc

all: $(EXECS)

calc: utility.o stack.o rpn.o in.o calc.o
	$(CC) $(CFLAGS) -o calc utility.o stack.o rpn.o in.o calc.o $(LDLIBS)

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm -f *.o
	
.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(EXECS)
