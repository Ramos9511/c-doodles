CC=gcc
CFLAGS=-I.

btree: drive.o insert.o drive.o btutil.o btio.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

allclean: clean
	$(RM) *~ btree btree.dat