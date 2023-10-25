CC = gcc
CFLAGS = -fsanitize=address

MYMALLOC_H = mymalloc.h
MYMALLOC_C = mymalloc.c
MEMGRIND_C = memgrind.c

all: memgrind

memgrind: $(MYMALLOC_O) $(MEMGRIND_O)
	$(CC) $(CFLAGS) -o $@ $^

# Object files
$(MYMALLOC_O): $(MYMALLOC_C) $(MYMALLOC_H)
	$(CC) $(CFLAGS) -c $<

$(MEMGRIND_O): $(MEMGRIND_C) $(MYMALLOC_H)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f memgrind *.o