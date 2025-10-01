CC=gcc
CFLAGS=-Wall -g -fsanitize=address

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) -o  memtest memtest.o mymalloc.o

memtest2: memtest2.o mymalloc.o
	$(CC) $(CFLAGS) -o  memtest2 memtest2.o mymalloc.o

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o  memgrind memgrind.o mymalloc.o
	
memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c


memtest.o: memtest.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest.c

memtest2.o: memtest2.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest2.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm -f $(OBJS) $(TARGET)