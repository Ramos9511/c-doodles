CC=gcc
CFLAGS=-I. -Ilib/headers

fdb: main.o ./lib/implementation/record_utils.o ./lib/implementation/utils.o ./lib/implementation/index_utils.o ./lib/implementation/input_utils.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

allclean: clean
	$(RM) *~ records.bin rrn_list.bin 

