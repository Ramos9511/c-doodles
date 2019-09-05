CC=gcc
CFLAGS=-I.

record_manager: main.o record_utils.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

mostlyclean: clean
	$(RM) *~


