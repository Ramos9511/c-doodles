#include "bt.h"
#include <stdio.h>

int search_cod(char key[], int root, int *pos_page, int *pos_record, int *offset){
	BTPAGE page;
	int found, pos;
	
	if(root == NIL) return NO;
	
	btread(root, &page);
	
	if(search_node(key, &page, &pos)){
		*pos_page = root;
		*pos_record = pos;
		*offset = page.offset[pos];
		return YES;
	}
	found = search_cod(key, page.child[pos], pos_page, pos_record, offset);
	return found;
}