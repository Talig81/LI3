#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "avl.h"
#include "linklist.h"

typedef struct TCD_istruct* TAD_istruct;

TAD_istruct init(){
}

//TAD_istruct load(TAD_istruct qs , int nsnaps , char* snaps_paths[]){
int main(int argc,char** argv){
	llink* l = primeiro(l);
	node* t = NULL;
	long* i = (long*)malloc(sizeof(long));
	*i = 0;
    t = parseDocs(argv[1],&l,&i);
    t = parseDocs(argv[2],&l,&i);
    t = parseDocs(argv[3],&l,&i);
    printf("quantidade de paginas:%ld\n",*i);
    int f = countNodes(t);
    printf("Quantidade de nos:%d\n",f);
    printf("Quantidade de revisoes:%d\n",qtRevisoes(t));
    printf("%s\n%d\n",l->author,l->id);
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