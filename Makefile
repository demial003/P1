CC=gcc
CFLAGS=-Wall -g -fsanitize=address



memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) -o  memtest memtest.o mymalloc.o

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o  memgrind memgrind.o mymalloc.o
	
memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c


memtest.o: memtest.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm -f $(OBJS) $(TARGET)