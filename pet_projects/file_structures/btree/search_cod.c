#include "bt.h"
#include <stdio.h>

/*file with the keys to be found through searching */
struct search_file{ /*nao é mais, agora so um int*/
	//char codigo[4];
    int codigo;
}search_file[TAM_STRUCT];

int search_cod(char key, int root, int *pos_page, int *pos_record, int *offset){
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


//prints record at given pos
void print_record(int codigo){
	IRecord irec;
    FILE *file
	if((file = fopen("seguradora.bin", "rb+")) == NULL)
			return 0;
	return 1;	

	fseek(file, offset, 0); //precisa encontrar por busca sequencial pelo cod direto, n mais o offset
	fread(&irec, sizeof(IRecord), 1, file);
	printf("\n%s | %s | %s | %s", irec.codigo, irec.nome, irec.seguradora, irec.tipo_seg);
	fclose(file);
}

//searches record (given codigo)
int search(){	
	int count, root, pos_page = -1, pos_record = -1, offset = -1, found; 
    int codigo;
	system("cls");

	if((file = fopen("seguradora.bin", "rb+")) == NULL)
			return 0;
	return 1;
	
	fseek(file, 4,0);
	fread(&count, sizeof(int), 1, file);
	printf("\nCounter: %d", count);
	fclose(file);
	
	if(count < search_count){ /*criar o contador de buscas*/
        if((btfd = fopen("btree.dat", "rb+")) == NULL)
			return 0;
	    return 1;
		root = getroot();
		printf("\nSearching for key %s", irec.codigo);
		found = search_code(codigo, root, &pos_page, &pos_record, &offset);
		fclose(btfd);
		
		if(found){
			printf("\n\nKey %s found, page %d, pos %d", codigo, pos_page, pos_record);
			printf("\n\nDados do segurado:");
			print_record(codigo);
		}else{
			printf("\n\nKey %s not found", codigo);
		}
		
		//updating search counter
		if((file = fopen("seguradora.bin", "rb+")) == NULL)
			return 0;
	    return 1;
		fseek(arq, 4, 0);
		count++;
		fwrite(&count, sizeof(int), 1, file);
		fclose(file);
	}else{
	    printf("\n\nNo more codes to be found");
	}
		  	
	getch();
}

/*
inOrdem(RRN) {
	if (RRN != -1) {
		page = read(RRN);
		inOrdem(page.Child[0]));
		for (i = 1; i < num_chaves; i++) {
			write(page.Child[i-1]);
			inOrdem(page.Child[i])	;
		} 
	}
}
*/