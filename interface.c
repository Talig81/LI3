#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "avl.h"
#include "linklist.h"
#include "interface.h"
#include "heap.h"

struct TCD_istruct{
	struct node* NODE;
	struct llink* LLINK;
	struct heap_t* HEAP;
	long all;
	struct heap_t * HEAP_W;
	long* auxiliar;
};

TAD_istruct init(){
	TAD_istruct t = malloc(sizeof(struct TCD_istruct));
	t -> NODE = NULL;
	t -> LLINK = initLL();
	t -> HEAP = initHeap();
	t -> HEAP_W = initHeap();
	t -> auxiliar = malloc(sizeof(long)*20);
	t -> all = 0;
	return t;
}

TAD_istruct load(TAD_istruct qs , int nsnaps , char* snaps_paths[]){
	long* i = (long*)malloc(sizeof(long));
	*i = 0;
	for(int iter = 0; iter < nsnaps ;iter++){
    	qs->NODE = parseDocs(snaps_paths[iter],&(qs->LLINK),&i,&(qs->NODE));
    }
    qs -> HEAP = constroi(qs->HEAP,qs->NODE);
    qs -> HEAP_W = constroiWord(qs->HEAP_W,qs->NODE);
   	qs -> all = *i+2;
    return qs;
}

long all_articles(TAD_istruct qs){
		printf("%d\n",getTotal(qs->NODE));
		return qs -> all;
}
long unique_articles(TAD_istruct qs){
	return countNodes(qs->NODE);
}
long all_revisions(TAD_istruct qs){
		return qtRevisoes(qs->NODE);
}

long* top_10_contributors(TAD_istruct qs){
	LLINK f = qs -> LLINK;
	qs->auxiliar = giveFirst(f);
	return qs->auxiliar;
}
char* contributor_name(long contributor_id, TAD_istruct qs){
	char * aux = findContr(contributor_id,qs->LLINK);
	if(aux != NULL) return aux;
	return NULL;
}
long* top_20_largest_articles(TAD_istruct qs){
	qs -> auxiliar = printasHEAP(qs->HEAP_W,20,qs->auxiliar);
	return qs->auxiliar;
}

char* article_title(long article_id, TAD_istruct qs){
	char*s= NULL;
	s = encontraTimestamp(qs->NODE,article_id);
	if( s == NULL) return NULL;
	return s;	
}
long* top_N_articles_with_more_words(int n, TAD_istruct qs){
	long* aux = (long*)malloc(sizeof(long)*n);
	aux = printasHEAP(qs->HEAP,n,aux);
	return aux;
}
char** titles_with_prefix(char* prefix, TAD_istruct qs){
	char** arr = malloc(sizeof(char*)*19000);
	int f = 0;
	f = preFixes(qs->NODE,arr,f,prefix);
    arr[f] = NULL;
	return arr;
}
char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){
	char * s = NULL;
	s = encontraTitulo(qs->NODE,article_id,revision_id);
	if(s ==NULL) return NULL;
	return s;
}

void apaga(long* aux){
	free(aux);
	return;
}

TAD_istruct clean(TAD_istruct qs){
	dispose(qs->NODE);
	deletas(&(qs->LLINK));
	qs->NODE = NULL;
	qs -> HEAP_W = NULL;
	qs -> HEAP = NULL;
	free(qs);
	return NULL;
}
/*
int main(int argc,char** argv){
	TAD_istruct t = init();
	t = load(t , argc-1 , argv+1);
	
	printf("unique: %ld\n\n",unique_articles(t));
	printf("revisions: %ld\n\n",all_revisions(t));
	printf("titulo %s\n\n4Query:\n",article_title(25,t));
	printas(t->LLINK);
	printf("contribuidor_id: 28903366 %s\n",contributor_name(28903366,t));
	long* coise = top_20_largest_articles(t);
	long* fds = top_N_articles_with_more_words(10,t);
	for(int i = 0; i<10;i++){
		printf("TOPNContribuidor id: %ld\n",fds[i]);
	}
	printf("Artigo: 25| Titulo:%s\n\n",article_title(25,t));
	for(int i = 0; i<10;i++) printf("TOP20 %ld\n\n",coise[i]);
	char* prefix = malloc(sizeof(char)*19);
	prefix = "Aut";
	char** nf = titles_with_prefix(prefix,t);
	if(nf == NULL) return 0;
	for(int i = 0; i<2;i++){
		printf("%s\n",nf[i]);
	}
	printf("Timestamptas: %s\n",article_timestamp(25,751028090,t));
	t = clean(t);
	if(t==NULL) printf("DID IT\n");
	return 1;
}*/
