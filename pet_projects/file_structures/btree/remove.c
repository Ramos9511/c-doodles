#include "bt.h"
#include <stdio.h>
/*incluir as funcoes de busca aqui*/

/*
Eliminação de chave em árvores-B
(1) Se a chave não estiver em uma folha, troque-a com sua sucessora imediata.
(2) Elimine a chave da folha.
(3) Se a folha continuar com o número mínimo de chaves, fim.
(4) A folha tem uma chave a menos que o mínimo. Verifique as páginas irmãs a esquerda e a direita: 
	(4.1) se uma delas tiver mais do que o número mínimo de chaves, aplique redistribuição;
	(4.2) senão concatene a página com uma das irmãs e a chave separadora do pai.
(5) Se ocorreu concatenação, aplique os passos de 3 a 6 para a página pai.
(6) Se a última chave da raiz for removida, a altura da árvore diminui. 
*/

/*Remove segurado - only from btree index, not from db file (no enunciado do ex)*/

int remover(int codigo, int root, int pos_pagina, int pos_registro){
	BTPAGE pagina, irmaE, irmaD, pai; 
	int pos_pagina_sucessor, pos_registro_sucessor, pos_pag_pai, pos_reg_pai, pos_pag_irmaE, pos_pag_irmaD;
	char sucessor[1]; //codigo do sucessor
	
	//pega a pagina do alvo
	btread(pos_pagina, &pagina);
//	printf("\npagina atual:");
//	printf("\ncodigo: %d   ponteiro e: %d   ponteiro d: %d", pagina.key[0], pagina.child[0], pagina.child[1]);
//	getch();
	
	//Verifica se a pagina tem o minimo de elementos obrigatórios para a remoção
	if(pagina.child[1] == NIL){	//verifica se a pagina é folha. obs: tem q ser o segundo filho para o tratamento da propagação funcionar
		if((pagina.keycount > MINKEYS)){
			remover_caso1(pos_registro, pos_pagina, &pagina);
			printf("\nCodigo %d removido, Caso 1", codigo);
		}else{
			achar_pag_irmas(pos_pagina, root, codigo, &pos_pag_pai, &pos_reg_pai, &pos_pag_irmaE, &pos_pag_irmaD);
					
			btread(pos_pag_pai, &pai); //pega a pagina pai
			btread(pos_pag_irmaE, &irmaE); //pega a pagina irma esquerda
			btread(pos_pag_irmaD, &irmaD); //pega a pagina irma direita
			
			//verifica se ha irmao a esquerda e se ele pode dar elementos
			if((pos_pag_irmaE != -1)  && (irmaE.keycount > MINKEYS)){ //criar contador de irmas a esquerda
				//efetua a redistribuição a direita			
				redistribuicao(pos_reg_pai - 1, &pai, pos_pag_irmaE, &irmaE, &pagina, 0); //faz a redistribuição 
				//escreve paginas atualizadas na arvore
				btwrite(pos_pag_pai, &pai);
				btwrite(pos_pag_irmaE, &irmaE);
				btwrite(pos_pagina, &pagina);
				
				printf("\nRedistribuicao, caso 3", codigo);
				return 1;
			}
			
			//verifica se ha irmao a direita e se ele pode dar elementos
			if((pos_pag_irmaD != -1) && (irmaD.keycount > MINKEYS)){ //criar contador a direita
				//efetua a redistribuição a direita	
				redistribuicao(pos_reg_pai, &pai, pos_pag_irmaD, &irmaD, &pagina, 1); //faz a redistribuição 
				//escreve paginas atualizadas na arvore
				btwrite(pos_pag_pai, &pai);
////			btwrite(pos_pag_irmaD, &irmaD);
				btwrite(pos_pagina, &pagina);
				
				printf("\nRedistribuicao, caso 3", codigo);
				return 1;
				
			}
			
			//se nenhum dos irmãos pode emprestar chama a concatenação
			concatenacao(pos_reg_pai, pos_pag_pai, &pai, pos_pag_irmaE, &irmaE, pos_pag_irmaD, &irmaD, pos_pagina, &pagina);
			printf("\nConcatenacao, caso 4");
			getch();
			
			//verifica se propagou para cima
			if(pai.keycount == 0){
				printf("\nPropagou para cima!!!");
				if(pos_pag_pai == root){   //se o pai for a raiz da arvore é só reescrever a raiz
					putroot(pai.child[0]);
					printf("\nReescrevendo Raiz");
					return 1;
				}
				remover(pai.key[0], root, pos_pag_pai, 0, NIL);  //removendo o elemento do pai
			}
		}
	}else{ //caso 2
		//acha elemento que ira substituir o codigo alvo na arvore B
		achar_sucessor_imediato(pagina.child[pos_registro], sucessor, &pos_pagina_sucessor, &pos_registro_sucessor); 
		substituir_elemento_caso2(pos_pagina, pos_registro, sucessor);
		printf("\nCodigo %d substituido pelo codigo %d, caso 2", codigo, sucessor);
		//removendo o sucessor de sua pagina antiga 
		remover(sucessor, root, pos_pagina_sucessor, pos_registro_sucessor);
		
	}
	return 1;
}

//remoção simples da arvore B
void remover_caso1(int pos_registro, int pos_pagina, BTPAGE *p_pag){
	int j; 
	for(j = pos_registro; j < (p_pag->keycount - 1) ; j++){ 
		strcpy(p_pag->key[j],p_pag->key[j+1]);
	    p_pag->child[j] = p_pag->child[j+1];
	} 
	p_pag->child[j] = p_pag->child[j+1];
	p_pag->keycount--;
	btwrite(pos_pagina, p_pag);  //escrevendo pagina atualizada na arvore
}


//acha o sucessor imediato a ESQUERDA do elemento removido
int achar_sucessor_imediato(int rrn, char sucessor[], int *pos_pag_suc, int *pos_reg_suc){
	BTPAGE pagina;
	
	btread(rrn, &pagina); //le pagina atual
	
	if(pagina.child[pagina.keycount] == NIL) {
		//*sucessor = pagina.key[pagina.keycount - 1];
		strcpy(sucessor, pagina.key[pagina.keycount - 1]);
		*pos_pag_suc = rrn;
		*pos_reg_suc = pagina.keycount - 1;
		return 1;
	};

	achar_sucessor_imediato(pagina.child[pagina.keycount], sucessor, pos_pag_suc, pos_reg_suc );
	return 1;
}

//substituir chave alvo pelo sucessor imediato, caso 2
void substituir_elemento_caso2(int pos_pagina, int pos_registro, char sucessor[]){
	BTPAGE pagina;
	
	btread(pos_pagina, &pagina); //pegando pagina do sucessor
	
	strcpy(pagina.key[pos_registro], sucessor); //trocando chave a ser removida pelo sucessor 
	
	btwrite(pos_pagina, &pagina);   //escrevendo pagina com novo elemento no arquivo
}

//acha as paginas irmãs da pagina do registro a ser removido
int achar_pag_irmas(int pos_pagina, int root, int codigo, int *pos_pag_pai, int *pos_reg_pai, int *pos_pag_irmaE, int *pos_pag_irmaD){
	BTPAGE pagina;
	int j, pos;
	
	btread(root, &pagina); //pega a raiz da arvore
	
	procurar_no(codigo, &pagina, &pos);
	//verifica se alguem da pagina é pai do elemento a ser removido
	// pos_pag_irmaE = pagina irmã a esquerda
	// pos_pag_irmaD = pagina irmã a direita
	if(pagina.child[pos] == pos_pagina){
		*pos_pag_pai = root; 
		*pos_reg_pai = pos;
		if(pos == 0){		//se a pos = 0, só tem irmão a direita
			*pos_pag_irmaE = NIL;
			*pos_pag_irmaD = pagina.child[pos + 1];		
		}else if(pos == pagina.keycount){	//se a pos for igual a quantidade de elementos na pag só tem irmão a esquerda
			*pos_pag_irmaE = pagina.child[pos - 1];
			*pos_pag_irmaD = NIL;
		}else{							//duas pag irmãs
			*pos_pag_irmaE = pagina.child[pos - 1];
			*pos_pag_irmaD = pagina.child[pos + 1];
		}
		return 1;
	}
	achar_pag_irmas(pos_pagina, pagina.child[pos], codigo, pos_pag_pai, pos_reg_pai, pos_pag_irmaE, pos_pag_irmaD);
	return 0;
}

//faz a redistribuição de registros de uma pagina para outra
void redistribuicao(int pos_reg_pai, BTPAGE *pai, int pos_pag_irmao, BTPAGE *irmao, BTPAGE *alvo, int tipo_redist){
	int posicao_chave_irmao;
	int j;
	
	//definindo a chave que sera passada do irmao
	if(tipo_redist == 0){
		posicao_chave_irmao = irmao->keycount - 1; 
	}else{
		posicao_chave_irmao = 0;
	}
	
	//relizando a redistribuicao
	strcpy(alvo->key[0], pai->key[pos_reg_pai]);
	strcpy(pai->key[pos_reg_pai], irmao->key[posicao_chave_irmao]);
	
	if(alvo->keycount == 0) (alvo->keycount)++;		//caso a redistribuição ocorra na propagação o cont do alvo vai estar zero
											//sendo assim, incrementa o contador da pag do alvo			
	if(tipo_redist == 0){
		//arrumando os ponteiros, necessario para a restribuições de nós que não são folhas
		alvo->child[1] = alvo->child[0];
		alvo->child[0] = irmao->child[irmao->keycount];
		//retirando da pag irmã a chave que foi passada para o pai
		(irmao->keycount)--; 
	}else{
		//arrumando os ponteiros, necessario para a restribuições de nós que não são folhas
		alvo->child[1] = irmao->child[0];
		//retirando da pag irmã a chave que foi passada para o pai
		remover_caso1(0, pos_pag_irmao, irmao);																			
	}
	
}

//Efetua a concatenação de paginas da arvore B
int concatenacao(int pos_reg_pai, int pos_pag_pai, BTPAGE *pai, int pos_pag_irmaE, BTPAGE *irmaE, int pos_pag_irmaD, BTPAGE *irmaD, int pos_pag_alvo, BTPAGE *pag_alvo){
	//se pagina irma a esquerda for -1, a irma a direita será utilizada para fazer a
	//concatenação, com a pagina do elemento a ser removido (pag_alvo) sendo a pagina que ira conter os registros
	// e a irma a direita será  a pagina deletada, caso a irma esquerda não for -1 ela será utilizada para conter os 
	//registros e a pagina alvo será eliminada.
	if(pos_pag_irmaE == NIL){
		//copiando primeiro e segundo elemento do irmao para a pagina em que está o elemento a ser removido
		strcpy(pag_alvo->key[0], pai->key[0]);
		
		strcpy(pag_alvo->key[1], irmaD->key[0]);
		
		//pegando os filhos da pagina irma
		pag_alvo->child[1] = irmaD->child[0];
		pag_alvo->child[2] = irmaD->child[1];
		//incrementando contador de elementos da pagina 
		pag_alvo->keycount = 2;
		
		//reorganizando pagina pai	
		reorganiza_pai(pai, 0);
		
		pageinit(irmaD);
		
		//escrevendo paginas atualizadas na arvore
		btwrite(pos_pag_pai, pai);
		btwrite(pos_pag_alvo, pag_alvo);
		btwrite(pos_pag_irmaD, irmaD);
		
	}else{
		//inserindo na pagina irma a esquerda a chave do pai
		strcpy(irmaE->key[1], pai->key[pos_reg_pai - 1]);
		
		//aponta para a pagina filha da pagina que será apagada
		irmaE->key[2] = pag_alvo->key[0];
		
		//incremantando contador da pagina irma esquerda
		irmaE->keycount = 2;
		
		pageinit(pag_alvo);
		
		//reorganizando pagina pai
		reorganiza_pai(pai, pos_reg_pai - 1);
		
		//escrevendo paginas atualizadas na arvore
		btwrite(pos_pag_pai, pai);
		btwrite(pos_pag_irmaE, irmaE);
		btwrite(pos_pag_alvo, pag_alvo);
	} 
}

//reorganiza pagina pai da concatenação
void reorganiza_pai(BTPAGE *pai, int pos_pai){
	int i;
	if(pai->keycount != 1){   
		for(i = pos_pai; i < (pai->keycount); i++){
			strcpy(pai->key[i], pai->key[i+1]);
			pai->child[i+1] = pai->child[i+2];
		} 
	}else{
		pai->child[1] = NIL;
	}
	(pai->keycount)--;	
}
