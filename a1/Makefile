CC = gcc
DEBUG=-g
OPT=-O0
PROGS = finds
OBJS = directory.o main.o wildcard.o
PRINTF = itoa.o my_printf.o
%.o:%.c
	$(CC) -c ${OPT} ${DEBUG} $< -o $@
.PHONY: all clean
.SILENT: clean
all: finds my_printf 
finds: $(OBJS)
	$(CC) ${OPT} ${DEBUG} $^ -o $@
my_printf: $(PRINTF)
	$(CC) ${OPT} ${DEBUG} $^ -o $@
clean:
	rm *.o finds test/link_test my_printf