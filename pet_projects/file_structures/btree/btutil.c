/* btutil.c...
	Contains utility functions for btree program:

	create_root() -- get and initialize root node and insert one key
	pageinit() -- put NOKEY in all "key" slots and NIL in "child" slots
	search_node() -- return YES if key in node, else NO. In either case,
			 put key's correct position in pos.
	ins_in_page() -- insert key and right child in page
	split() -- split node by creating new node and moving half of keys to
		         new node. Promote middle key and rrn of new node.
 */

#include "bt.h"
#include <stdio.h>

short create_root(char key, short left, short right)
{
  BTPAGE page;
  short rrn;
  rrn = getpage();
  pageinit(&page);
  page.key[0] = key;
  page.child[0] = left;
  page.child[1] = right;
  page.keycount = 1;
  btwrite(rrn, &page);
  putroot(rrn);
  return (rrn);
}

void pageinit(BTPAGE* p_page) /* p_page: pointer to a page  */
{
  int j;

  for (j = 0; j < MAXKEYS; j++) {
    p_page->key[j] = NOKEY;
    p_page->child[j] = NIL;
  }
  p_page->child[MAXKEYS] = NIL;
}

int search_node(char key, BTPAGE* p_page, short* pos)
/* pos: position where key is or should be inserted  */
{
  int i;
  for (i = 0; i < p_page->keycount && key > p_page->key[i]; i++)
    ;
  *pos = i;
  if (*pos < p_page->keycount && key == p_page->key[*pos])
    return (YES); /* key is in page */
  else
    return (NO); /* key is not in page */
}

void ins_in_page(char key, short r_child, BTPAGE* p_page)
{
  int i;

  for (i = p_page->keycount; key < p_page->key[i - 1] && i > 0; i--) {
    p_page->key[i] = p_page->key[i - 1];
    p_page->child[i + 1] = p_page->child[i];
  }
  p_page->keycount++;
  p_page->key[i] = key;
  p_page->child[i + 1] = r_child;
}

/* split ()
Arguments:
	key:           key to be inserted 
	promo_key:     key to be promoted up from here
	r_child:       child rrn to be inserted
	promo_r_child: rrn to be promoted up from here
	p_oldpage:     pointer to old page structure
	p_newpage:     pointer to new page structure
*/

void split(char key, short r_child, BTPAGE* p_oldpage, char* promo_key, short* promo_r_child, BTPAGE* p_newpage)
{
  int i;
  short mid; /* tells where split is to occur            */
  char workkeys[MAXKEYS + 1]; /* temporarily holds keys, before split     */
  short workch[MAXKEYS + 2]; /* temporarily holds children, before split */

  for (i = 0; i < MAXKEYS; i++) { /* move keys and children from  */
    workkeys[i] = p_oldpage->key[i]; /* old page into work arrays    */
    workch[i] = p_oldpage->child[i];
  }

  workch[i] = p_oldpage->child[i];
  for (i = MAXKEYS; key < workkeys[i - 1] && i > 0; i--) { /* insert new key */
    workkeys[i] = workkeys[i - 1];
    workch[i + 1] = workch[i];
  }

  workkeys[i] = key;
  workch[i + 1] = r_child;

  *promo_r_child = getpage(); /* create new page for split,   */
  pageinit(p_newpage); /* and promote rrn of new page  */

  for (i = 0; i < MINKEYS; i++) { /* move first half of keys and  */
    p_oldpage->key[i] = workkeys[i]; /* children to old page, second */
    p_oldpage->child[i] = workch[i]; /*  half to new page            */
    p_newpage->key[i] = workkeys[i + 1 + MINKEYS];
    p_newpage->child[i] = workch[i + 1 + MINKEYS];
    p_oldpage->key[i + MINKEYS] = NOKEY; /* mark second half of old  */
    p_oldpage->child[i + 1 + MINKEYS] = NIL; /* page as empty            */
  }

  p_oldpage->child[MINKEYS] = workch[MINKEYS];
  p_newpage->child[MINKEYS] = workch[i + 1 + MINKEYS];
  p_newpage->keycount = MAXKEYS - MINKEYS;
  p_oldpage->keycount = MINKEYS;
  *promo_key = workkeys[MINKEYS]; /* promote middle key */
}