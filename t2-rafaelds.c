/*	UNIVERSIDADE FEDERAL DE SAO CARLOS CAMPUS SOROCABA
*	TRABALHO 2 DE GRAFOS
*  	ALUNO RAFAEL DANILO DOS SANTOS RA 408654
* 	DESCRIÇAO: 	 INFORMA SE UM GRAFO EH BIPARTIDO 
* 	ULTIMA MODIFICAO DATA 10/ JUNHO / 2013
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX 200
#define NULO 0
#define TRUE 1
#define FALSE 0

//enum colors {livre=0, preto, branco};

typedef struct no {
	int vizinho;
	struct no *proximo;
	} Node;

typedef struct {
		Node *inicio;
		Node *fim;
	} grafo;

void iniciarVertice(grafo *p){
	p->inicio = NULL;
	p->fim = NULL;
}

void iniciarGrafo(grafo p[]){
	int i;
	for(i=0;i<MAX;i++) iniciarVertice(&p[i]);
}

int verticeVazio(grafo *p){
	if (p->inicio == NULL) return 1;
	return 0;
}

int inserirVizinho(grafo *p, int vizinho) {
		Node *pnovo = (Node *) malloc(sizeof(Node));
		if(pnovo == NULL) exit(1);
		pnovo->vizinho = vizinho;
		pnovo->proximo = NULL;
		if(verticeVazio(p)) {
			p->inicio = pnovo;
		} else {
			p->fim->proximo = pnovo;
		}
		p->fim = pnovo;
		return 1;
}

int encerraVertice(grafo *p){
	Node *paux = p->inicio;
	while(paux != NULL){
		Node *papg = paux;
		paux = paux->proximo;
		free(papg);
	}
	return 1;
}

int encerraGrafo(grafo p[]){
	int i;
	for(i=0;i<MAX;i++) encerraVertice(&p[i]);
}

int bfs(grafo p[], int atual, int anterior, int corA[]){
	
	if(!corA[atual]) corA[atual] = (corA[anterior] % 2)+1;
	else if (corA[atual] == corA[anterior]) return FALSE;
	
	int bipartido = TRUE;
	Node *vertice = p[atual].inicio;
	while (vertice != NULL){
		if(!corA[vertice->vizinho]) {
			if(bfs(p,vertice->vizinho,atual,corA)) return FALSE;
		}
		vertice = vertice->proximo; 
	}
	return bipartido;
	
}


int main () {
		int i, u, v, nA,mA, bipartido;
		grafo grafoA[MAX];
		int fila[MAX], inicio=0,fim=0;
		int corA[MAX];
		
		while(1){
		inicio=0,fim=1;
		bipartido = TRUE;
		iniciarGrafo(grafoA);
		
		//recebe grafo A
		scanf("%d %d",&nA, &mA);
		if (nA == 0 && mA == 0) break; 
		for(i=0;i<mA;i++) {
			scanf("%d %d", &u, &v); 
			inserirVizinho(&grafoA[u-1],v-1);
			inserirVizinho(&grafoA[v-1],u-1);	
		}
		
		for(i=0;i<nA;i++) {
			corA[i]=0;
			fila[i]=-1;
		}
		
		
		fila[inicio] = 0;
		
	for(i=0;i<nA && bipartido;i++){
		if(corA[i]) break;
		corA[i] = 1; 
		fila[inicio] = i;
		if(inicio==fim) fim++;
			while(fim!=inicio && bipartido){
			Node *vertice = grafoA[fila[inicio]].inicio;
			
			if(!corA[fila[inicio]]) corA[fila[inicio]] = 1;
			
			while(vertice != NULL) {
				if(!corA[vertice->vizinho]) {
					corA[vertice->vizinho] = (corA[fila[inicio]] % 2)+1;
					fila[fim++] = vertice->vizinho;
				}
				else if(corA[vertice->vizinho] == corA[fila[inicio]]){
					 bipartido = FALSE;
					 break;
				}
				 vertice = vertice->proximo;
			}
			inicio++;
		}
	}
		if(bipartido) {
			printf("SIM\n");
		} else {
			printf("NAO\n");
		}
		encerraGrafo(grafoA);
	}
	return 0; 
}
