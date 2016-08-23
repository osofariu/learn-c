SHELL = /bin/sh
CFLAGS=-Wall -g
LDFLAGS= -Wall -L/usr/lib/x86_64-linux-gnu -L/lib/x86_64-linux-gnu -L /lib64  
LIBS= -l:libcheck.a  -lm -lrt -lpthread -lsubunit

.SUFFIXES:
.SUFFIXES: .c .o

TARGETS=hello
ARGS ?= 123

OBJDIR := obj
SRCDIR := src

_SRCS := hello.c types.c
SRCS := $(patsubst %,$(SRCDIR)/%,$(_SRCS))
OBJS := $(patsubst %,$(OBJDIR)/%,$(_SRCS:c=o))

all: types

types: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@ 

createdir:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | createdir
	$(CC) $(CFLAGS) -c -o $@ $<

valgrind: hello
	valgrind --track-origins=yes ./hello ${ARGS}

clean:
	rm -f $(TARGETS) $(OBJDIR)/*.o
