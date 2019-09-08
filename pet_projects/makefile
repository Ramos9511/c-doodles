CC=gcc
CFLAGS=-I.

fdb: main.o record_utils.o utils.o index_utils.o input_utils.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

allclean: clean
	$(RM) *~ records.bin rrn_list.bin 

