/* btio.c
 Contains btree functions that directly involve file I/O:
 */

#include "bt.h"
#include "fileio.h"
#include <stdio.h>

int btfd; // global file descriptor for "btree.dat"

btopen()
{
  btfd = open("btree.dat", O_RDWR);
  return (btfd > 0);
}

btclose()
{
  close(btfd);
}

short getroot()
{
  short root;
  long lseek();

  lseek(btfd, 0L, 0);
  if (read(btfd, &root, 2) == 0) {
    printf("Error: Unable to get root. \007\n");
    exit(1);
  }
  return (root);
}

putroot(short root)
{
  lseek(btfd, 0L, 0);
  write(btfd, &root, 2);
}

short create_tree()
{
  char key;

  btfd = creat("btree.dat", PMODE);
  close(btfd);
  btopen();
  key = getchar();
  return (create_root(key, NIL, NIL));
}

short getpage()
{
  long lseek(), addr;
  addr = lseek(btfd, 0L, 2) - 2L;
  return ((short)addr / PAGESIZE);
}

btread(short rrn, BTPAGE* page_ptr)
{
  long lseek(), add;

  addr = (long)rrn * (long)PAGESIZE + 2L;
  lseek(btfd, addr, 0);
  return (read(btfd, page_ptr, PAGESIZE));
}

btwrite(short rrn, BTPAGE* page_ptr)
{
  long lseek(), addr;

  addr = (long)rrn * (long)PAGESIZE + 2L;
  lseek(btfd, addr, 0);
  return (write(btfd, page_ptr, PAGESIZE));
}