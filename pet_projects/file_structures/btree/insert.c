/* insert.c...
        Contains insert() function to insert a key into a btree.
	Calls itself recursively until bottom of tree is reached.
	Then inserts key in node.
	If node is out of room, 
	    - calls split() to split node
	    - promotes middle key and rrn of new node  
*/

#include "bt.h"
#include <stdio.h>

/* insert() ...
Arguments:
	rrn:            rrn of page to make insertion in          
	*promo_r_child: child promoted up from here to next level 
	key:            key to be inserted here or lower  
	*promo_key:     key promoted up from here to next level   
*/

int insert(short rrn, char key[], int offset, short* promo_r_child, char promo_key[], int *promo_offset)
{
  BTPAGE page; /* current page                      */
  BTPAGE newpage; /* new page created if split occurs  */
  int found, promoted; /* boolean values                    */
  short pos;
  short p_b_rrn, p_b_offset; /* rrn promoted from below           */
  char p_b_key[4]; /* key promoted from below           */

  if (rrn == NIL) { /* past bottom of tree... "promote" */
    //*promo_key = key; /* original key so that it will be  */
    strcpy(promo_key, key);
		*promo_offset = offset; 
    *promo_r_child = NIL; /* inserted at leaf level           */
    return (YES);
  }

  btread(rrn, &page);
  /*checks if key[]s duplicated*/
  found = search_node(key, &page, &pos);
  if (found) {
    printf("Error: attempt to insert duplicate key: %s \n\007", key);
    return (0);
  }

  promoted = insert(page.child[pos], key, offset, &p_b_rrn, p_b_key, &p_b_offset);
  if (!promoted)
    return (NO); /* no promotion */

  if (page.keycount < MAXKEYS) {
    ins_in_page(p_b_key, p_b_offset, p_b_rrn, &page); /* OK to insert key and  */
    btwrite(rrn, &page); /* pointer in this page. */
    printf("\nKey %s inserted successfully", p_b_chave);
    return (NO); /* no promotion */
  } else {
    split(p_b_key, p_b_offset, p_b_rrn, &page, promo_key, promo_offset, promo_r_child, &newpage);
    btwrite(rrn, &page);
    btwrite(*promo_r_child, &newpage);
    return (YES); /* promotion */
  }
}
