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
  char promo_key; /* key promoted from below                  */
  char key; /* next key to insert in tree               */

  if (btopen()) /* try to open btree.dat and get root       */
    root = getroot();
  else /* if btree.dat not there, create it        */
    root = create_tree();

  while ((key = getchar()) != 'q') {
    if (key == '\n') continue;
    promoted = insert(root, key, &promo_rrn, &promo_key);
    if (promoted)
      root = create_root(promo_key, root, promo_rrn);
  }


  btclose();

  return 0;
}
