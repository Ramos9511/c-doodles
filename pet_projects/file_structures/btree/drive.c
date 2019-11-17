/* driver.c
  Driver for btree tests
  Open or creates b-tree file.
  Get next key and calls insert to insert key in tree.
  If necessary creates new root.
*/

#include "bt.h"
#include <stdio.h>

int main()
{
  int promoted; // boolean: tells if a promotion from below
  short root, // rrn of root page
      promo_rrn; // rrn promoted from below
  char promo_key, // key promoted from below
      key; // next key to insert in tree

  if (btopen()) {
    root = getroot();
  } else {
    root = create_tree();
  }

  while ((key = getchar()) != 'q') {
    promoted = insert(root, key, &promo_rrn, &promo_key);
    if (promoted)
      root = create_root(promo_key, root, promo_rrn);
  }

  btclose();
}