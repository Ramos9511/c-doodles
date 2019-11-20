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

short create_root(char key[], int offset, short left, short right)
{
  BTPAGE page;
  short rrn;
  rrn = getpage();
  pageinit(&page);
  strcpy(page.key[0], key);
  page.offset[0] = offset;
  page.child[0] = left;
  page.child[1] = right;
  page.keycount = 1;
  btwrite(rrn, &page);
  putroot(rrn);
  printf("\nRoot created with key %s", key);
  return (rrn);
}

void pageinit(BTPAGE* p_page) /* p_page: pointer to a page, init page with null values*/
{
  int j;

  for (j = 0; j < MAXKEYS; j++) {
    //p_page->key[j] = NOKEY;
    strcpy(p_page->key[j],NOKEY); 
    p_page->child[j] = NIL;
    p_page->offset[j] = NIL;
  }
  p_page->child[MAXKEYS] = NIL;
}

int search_node(char key[], BTPAGE* p_page, short* pos)
/* pos: position where key is or should be inserted  */
{
  int i;
  for (i = 0; i < p_page->keycount && key > (strcmp(key,p_page->key[i])>0); i++);
  *pos = i;
  if (*pos < p_page->keycount && (strcmp(key,p_page->key[*pos])==0))
    return (YES); /* key is in page */
  else
    return (NO); /* key is not in page */
}

void ins_in_page(char key[], int offset, short r_child, BTPAGE* p_page)
{
  int i;

  for (i = p_page->keycount; (strcmp(key, p_page->key[i-1]) < 0) && i > 0; i--) {
    //p_page->key[i] = p_page->key[i - 1];
    strcpy(p_page->key[i],p_page->  key[i-1]); 
    p_page->child[i + 1] = p_page->child[i];
    p_page->offset[i] = p_page->offset[i-1];
  }
  p_page->keycount++;
  //p_page->key[i] = key;
  strcpy(p_page->key[i], key); 
  p_page->child[i + 1] = r_child;
  p_page->offset[i] = offset;
}

/* split ()
Arguments:
	key:           key to be inserted 
	promo_key:     key to be promoted up from here
  promo_offset:  offset to be promoted up from here
	r_child:       child rrn to be inserted
	promo_r_child: rrn to be promoted up from here
	p_oldpage:     pointer to old page structure
	p_newpage:     pointer to new page structure
*/

/*split page when necessary*/
void split(char key[], int offset, short r_child, BTPAGE* p_oldpage, char* promo_key, int *promo_offset, short* promo_r_child, BTPAGE* p_newpage)
{
  int i;
  short mid; /* tells where split is to occur            */
  char workkeys[MAXKEYS + 1][4]; /* temporarily holds keys, before split     */
  short workch[MAXKEYS + 2]; /* temporarily holds children, before split */
  int workoffset[MAXKEYS+1];
  printf("\n\nNode split!\n");
  /*put page elements into temp array*/
  for (i = 0; i < MAXKEYS; i++) { /* move keys and children from  */
    strcpy(workkeys[i], p_oldpage->key[i]);
    //workkeys[i] = p_oldpage->key[i]; /* old page into work arrays    */
    workch[i] = p_oldpage->child[i];
    workoffset[i] = p_oldpage->offset[i];
  }

  workch[i] = p_oldpage->child[i];
  //workch[3] = p_oldpage->child[3]; /*deveria deixar estatico para facilitar*/
  /*will reorder and find spot where new key[] must be inserted*/
  for (i = MAXKEYS; (strcmp(key, workkeys[i-1]) < 0) && i > 0; i--) { /* insert new key */
    //workkeys[i] = workkeys[i - 1];
    strcpy(workkeys[i], workkeys[i-1]);
    workch[i + 1] = workch[i];
    workoffset[i] = p_oldpage->offset[i-1];
  }

  /*inserts key[] where it should be placed and puts key[] in old child*/
  //workkeys[i] = key;
  strcpy(workkeys[i], key); 
  workch[i + 1] = r_child;
  workoffset[i] = offset;

/*creates new page with the promoted*/
  *promo_r_child = getpage(); /* create new page for split,   */
  pageinit(p_newpage); /* and promote rrn of new page  */
  pageinit(p_oldpage);

/*putting pages into their right places*/ 
/*poderiamos deixar td estatico p facilitar a vida, menos paus T_T */

  /*estático
  p_oldpage->cont = 2; //ja tenho esse contador?

	strcpy(p_oldpage->key[0],workkeys[0]);
	strcpy(p_oldpage->key[1],workkeys[1]);
  
  p_oldpage->offset[0] = workoffset[0];
	p_oldpage->offset[1] = workoffset[1];

  p_oldpage->child[0] = workch[0]; 	
	p_oldpage->child[1] = workch[1]; 	
	p_oldpage->child[2] = workch[2];

  strcpy(p_oldpage->key[2],NOKEY);
	p_oldpage->offset[2] = NIL;  

  */
  for (i = 0; i < MINKEYS; i++) { /* move first half of keys and  */
	
    strcpy(p_oldpage->key[i],workkeys[i]);
    //p_oldpage->key[i] = workkeys[i]; /* children to old page, second */
    p_oldpage->child[i] = workch[i]; /*  half to new page            */
    p_oldpage->offset[i] = workoffset[i];

    strcpy(p_newpage->key[i],workkeys[i + 1 + MINKEYS]);
    //p_newpage->key[i] = workkeys[i + 1 + MINKEYS];
    p_newpage->child[i] = workch[i + 1 + MINKEYS];
    p_newpage->offset[i] = workoffset[i + 1 + MINKEYS];
    
    p_oldpage->key[i + MINKEYS] = NOKEY; /* mark second half of old  */
    p_oldpage->child[i + 1 + MINKEYS] = NIL; /* page as empty            */
    p_oldpage->offset[[i + 1 + MINKEYS] = NIL;
  }

  /*new page receives the third one (promoteds spot)*/
  p_oldpage->child[MINKEYS] = workch[MINKEYS];
  p_oldpage->offset[MINKEYS] = workoffset[MINKEYS];

  p_newpage->child[MINKEYS] = workch[i + 1 + MINKEYS];
  p_newpage->offset[MINKEYS] = workoffset[i + 1 + MINKEYS];

  p_newpage->keycount = MAXKEYS - MINKEYS;
  p_oldpage->keycount = MINKEYS;
  //*promo_key = workkeys[MINKEYS]; /* promote middle key */ /*string??*/
  strcpy(promo_key, workkeys[MINKEYS]);
  *promo_offset = workoffset[MINKEYS];
  printf("\nPromoted key: %s", promo_key);
}