/* btio.c...
	Contains btree functions that directly involve file i/o:

	btopen() -- open file "btree.dat" to hold the btree.
	btclose() -- close "btree.dat"
	getroot() -- get rrn of root node from first two bytes of btree.dat
	putroot() -- put rrn of root node in first two bytes of btree.dat
	create_tree() -- create "btree.dat" and root node
	getpage() -- get next available block in "btree.dat" for a new page
	btread() -- read page number rrn from "btree.dat"
	btwrite() -- write page number rrn to "btree.dat"
*/
#include "bt.h"
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int btfd; /* global file descriptor for "btree.dat"  */

int btopen()
{
  btfd = open("btree.dat", O_RDWR);
  return (btfd > 0);
}

void btclose()
{
  close(btfd);
}

short getroot()
{
  short root;

  lseek(btfd, 0L, 0);
  if (read(btfd, &root, 2) == 0) {
    printf("Error: Unable to get root.\007\n");
    exit(1);
  }
  return (root);
}

void putroot(short root)
{
  lseek(btfd, 0L, 0);
  write(btfd, &root, 2);
}

short create_tree(char key[], int offset)
{
  //char key;
  btfd = creat("btree.dat", PMODE); /*seria o fopen(btree.bin "wt+")*/
  printf("\nTree created");
  putroot(NIL);
  close(btfd); /* Have to close and reopen to insure  */
  btopen(); /* read/write access on many systems.  */
  //key = getchar(); /* Get first key.  */
  return (create_root(key, offset, NIL, NIL));
}

short getpage()
{
  long addr;
  addr = lseek(btfd, 0L, 2) - 2L;
  return ((short)addr / PAGESIZE);
}

/*read btree page*/
int btread(short rrn, BTPAGE* page_ptr)
{
  long addr;

  addr = (long)rrn * (long)PAGESIZE + 2L;
  lseek(btfd, addr, 0);
  return (read(btfd, page_ptr, PAGESIZE));
}

int btwrite(short rrn, BTPAGE* page_ptr)
{
  long addr;
  addr = (long)rrn * (long)PAGESIZE + 2L;
  lseek(btfd, addr, 0);
  return (write(btfd, page_ptr, PAGESIZE));
}
