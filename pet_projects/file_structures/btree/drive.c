/* driver.c...
	Driver for btree tests:

		Opens or creates b-tree file.
		Gets next key and calls insert to insert key in tree.
		If necessary, creates a new root.
*/
#include "bt.h"
#include <stdio.h>

int main()
{
  int promoted; /* boolean: tells if a promotion from below */
  short root; /* rrn of root page                         */
  short promo_rrn; /* rrn promoted from below                  */
  short promo_offset;
  char promo_key[4]; /* key promoted from below                  */
  //char key; /* next key to insert in tree               */

  if (btopen()) /* try to open btree.dat and get root       */
    root = getroot();
  else /* if btree.dat not there, create it        */
    root = create_tree(key, offset);

 /* while ((key = getchar()) != 'q') {
    if (key == '\n') continue;
    printf("\n\nBTree insertion\n");
		printf("\nInserting key %s", key);
    promoted = insert(root, key, offset, &promo_rrn, promo_key, &promo_offset);
    if (promoted)
      root = create_root(promo_key, promo_offset, root, promo_rrn);
  }*/

//if its the first insertion, cod had already been registered so skips the code below
if(insertion_count!= 0){ /*criar o contador*/
  //inserting key and offset into BTree
  printf("\nInserting into BTree\n");
  printf("\nInserting key %s", key);
  promoted = insert(root, key, offset, &promo_rrn, promo_key, &promo_offset);
    if (promoted)
      root = create_root(promo_key, promo_offset, root, promo_rrn);
  }
}


  btclose();

  return 0;
}
