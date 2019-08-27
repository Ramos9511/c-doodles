CC=gcc
CFLAGS=-I/home/gfvante/hd/dev/c/c_lab/queue/queue_list

binary_tree: ../queue/queue_list/queue_list.o binary_tree.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o

mostlyclean: clean
	$(RM) *~


