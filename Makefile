CC=gcc
CFLAGS=-Wall -g -fsanitize=address

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o  memgrind memgrind.o mymalloc.o

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) -o  memtest memtest.o mymalloc.o

memtest2: memtest2.o mymalloc.o
	$(CC) $(CFLAGS) -o  memtest2 memtest2.o mymalloc.o

errorTest1: errorTest1.o mymalloc.o
	$(CC) $(CFLAGS) -o  errorTest1 errorTest1.o mymalloc.o

errorTest2: errorTest2.o mymalloc.o
	$(CC) $(CFLAGS) -o  errorTest2 errorTest2.o mymalloc.o

errorTest3: errorTest3.o mymalloc.o
	$(CC) $(CFLAGS) -o  errorTest3 errorTest3.o mymalloc.o
	
memgrind.o: memgrind.c mymalloc.h
	$(CC) $(CFLAGS) -c memgrind.c

errorTest1.o: errorTest1.c mymalloc.h
	$(CC) $(CFLAGS) -c errorTest1.c

errorTest2.o: errorTest2.c mymalloc.h
	$(CC) $(CFLAGS) -c errorTest2.c

errorTest3.o: errorTest3.c mymalloc.h
	$(CC) $(CFLAGS) -c errorTest3.c

memtest.o: memtest.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest.c

memtest2.o: memtest2.c mymalloc.h
	$(CC) $(CFLAGS) -c memtest2.c

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean:
	rm -f $(OBJS) $(TARGET)