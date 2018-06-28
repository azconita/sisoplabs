CFLAGS := -m32 -g -std=c99 -Wall -Wextra -Wpedantic
CFLAGS += -O1 -fno-pic -fno-omit-frame-pointer -no-pie
ASFLAGS = $(CFLAGS)

ASMS := $(wildcard *.S)  # wildcard *.S
SRCS := $(wildcard *.c)  # wildcard *.c

# Como en este lab el código de cada programa reside en un
# único archivo, los wildcard transformarán prog.c o prog.S
# directamente a "prog", sin usar compilación intermedia; esto
# es, sin que make llegue a recibir prog.o como objetivo.
PROG := $(ASMS:%.S=%)  # patsubst %.S → %
PROG += $(SRCS:%.c=%)  # patsubst %.c → %

all: $(PROG)

clean:
	rm -f $(PROG) *.o core

.PHONY: clean all

