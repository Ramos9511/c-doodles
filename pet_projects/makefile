CC=gcc
CFLAGS=-I.

record_manager: main.o record_utils.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

allclean: clean
	$(RM) *~ records.bin rrn_list.bin 


