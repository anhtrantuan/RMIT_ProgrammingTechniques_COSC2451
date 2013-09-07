CC=gcc
CFLAGS=-Wall -std=c99 -g -pg
LDLIBS=-lm
HEADERS = utility.h stack.h rpn.h in.h
SOURCES = $(patsubst %.h,%.c,$(HEADERS)) calc.c
OBJS = $(patsubst %.c,%.o,$(SOURCES))
EXEC = calc

all: $(EXEC)

calc: $(OBJS)
	$(CC) $(CFLAGS) -o calc utility.o stack.o rpn.o in.o calc.o $(LDLIBS)

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm -f *.o
	
.PHONY: cleanall
cleanall:
	rm -f *.o *~ $(EXEC)
