CC = gcc
PROGS = finds
OBJS = directory.o main.o file.o
%.o:%.c
	$(CC) -c $< -o $@

finds: $(OBJS)
	$(CC) $^ -o $@
clean:
	rm *.o finds