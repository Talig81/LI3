#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void interpretador(TAD_istruct qs, char q){
	switch(q){
		case '0':
			printf("Sair\n");
			break;
		case '1':
			printf("Artigos totais: %ld\n",all_articles(qs));
			break;
		case '2':
			printf("Artigos únicos: %ld\n",unique_articles(qs));
			break;
		case '3':
			printf("Revisões totais: %ld\n",all_revisions(qs));
			break;/*
		case '4':
			long* aux = top_10_contributors(qs);
			for(int i = 0; i < 10;i++){
				printf("Id do contribuidor: %ld",aux[i]);
			}
			break;
		case '5':
			long x = 0;
			printf("Insira o ID do contribuidor\n");
			scanf("%ld",&x);
			char * f = contributor_name(x,qs);
			if(f==NULL){
				printf("Não foi encontrado nenhum contribuidor\n");
				break;
			}
			printf("ID do contribuidor: %ld  Contribuidor: %s",x,f);
			break;
		case '6':
			long* aux = top_20_largest_articles(qs);
			for(int i = 0; i<20;i++) printf("%ld\n",aux[i]);
			break;							
		case '7':
			long aux;
			printf("Insira o id do articulo desejado\n");
			scanf("%ld",&aux);
			char * string = NULL;
			string = article_title(aux,qs);
			if(string != NULL) printf("Artigo id%ld, Titulo: %s\n",aux,string);
			break;
		case'8':
			printf("Insira a quantidade de artigos com o maior numero de palavras\n");
			int j = 0;
			scanf("%d",&j);
			long* aux = top_N_articles_with_more_words(j,qs);
			for(int i = 0; i < j; i++)printf("%s\n",aux[i]);
			break;
		case '9':
			printf("Ainda nao implementada\n");
			break;
		case '10':
			printf("Insira o id do artigo seguido do id da revisao\n");
			long f,c;
			scanf("%ld",&f);
			scanf("%ld",&c);
			char * aux = article_timestamp(f,c,qs);
			if(aux == NULL) printf("Não foi encontrado\n");
			break;*/
		default:
			printf("Opção errada\n");
			break;
		}
	return;
}

int main(int argc, char** argv){
	int a=1;
	TAD_istruct qs = init();
	qs = load(qs,argc-1,argv+1);
	while(a != 0){
		char f;
		scanf("%c",&f);
		interpretador(qs,f);
		printf("escreva\n");
		scanf("%d",&a);
	}
	printf("para ja nada");
	return 1;
}