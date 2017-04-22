#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "avl.h"
#include "linklist.h"
#include "interface.h"


struct TCD_istruct{
	struct node* NODE;
	struct llink* LLINK;
};

TAD_istruct init(){
	TAD_istruct t = malloc(sizeof(struct TCD_istruct));
	t -> NODE = NULL;
	t -> LLINK = initLL();
	return t;
}

//TAD_istruct load(TAD_istruct qs , int nsnaps , char* snaps_paths[]){
int main(int argc,char** argv){
	long* i = (long*)malloc(sizeof(long));
	*i = 0;
	TAD_istruct t = init();
    t->NODE = parseDocs(argv[1],t->LLINK,&i,t->NODE);
    t->NODE = parseDocs(argv[2],t->LLINK,&i,t->NODE);
    t->NODE = parseDocs(argv[3],t->LLINK,&i,t->NODE);
    printf("cheguei aqui\n");
    printf("quantidade de paginas:%ld\n",*i);
    int f = countNodes(t->NODE);
    printf("numeroRevs %d,uniq%d\n",qtRevisoes(t->NODE),f);
    free(i);
    
    return 1;
}

long all_articles(TAD_istruct qs){
}

long unique_articles(TAD_istruct qs){

}

long all_revisions(TAD_istruct qs){

}

long* top_10_contributors(TAD_istruct qs){

}

char* contributor_name(long contributor_id, TAD_istruct qs){

}

long* top_20_largest_articles(TAD_istruct qs){

}

char* article_title(long article_id, TAD_istruct qs){
}

long* top_N_articles_with_more_words(int n, TAD_istruct qs){
}
 
char** titles_with_prefix(char* prefix, TAD_istruct qs){
}

char* article_timestamp(long article_id, long revision_id, TAD_istruct qs){

}