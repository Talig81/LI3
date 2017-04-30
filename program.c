#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

void menu_query(){
	printf("	Escolha uma das opções\n");
	printf("[1] Quantidade total de artigos\n");
	printf("[2] Quantidade de artigos únicos\n");
	printf("[3] Quantidade de revisões\n");
	printf("[4] Os 10 maiores contribuidores\n");
	printf("[5] Pesquisar o nome do contribuidor\n");
	printf("[6] Os 20 maiores artigos\n");
	printf("[7] Pesquisar nome do artigo\n");
	printf("[8] Artigos com mais palavras\n");
	printf("[9] Encontrar artigos por prefixo\n");
	printf("[10] Encontrar Timestamp de uma revisão\n");
	printf("[0] SAIR\n");

}

void menu_principal(){
	printf("		Bem Vindo\n");
	printf("[0] Sair\n");
	printf("[1] Iniciar o programa\n");
	printf("[2] Limpar o programa\n");
}

void interpretador(TAD_istruct qs){
		int q = -1;
		menu_query();
		while(scanf("%d\n",&q)){
			if(q ==  0){
				printf("Sair\n");	
				exit(0);	
			}
			if(q ==  1){
				printf("Artigos totais: %ld\n",all_articles(qs));
				
			}
			if(q ==  2){
				printf("Artigos únicos: %ld\n",unique_articles(qs));
				
			}
			if(q ==  3){
				printf("Revisões totais: %ld\n",all_revisions(qs));
				
			}
			if(q ==  4){
				long* aux = top_10_contributors(qs);
				for(int i = 0; i < 10;i++){
					printf("Id do contribuidor: %ld\n",aux[i]);
				}
				
			}
			if(q ==  5){
				long x = 0;
				printf("Insira o ID do contribuidor\n");
				scanf("%ld",&x);
				char * f = contributor_name(x,qs);
				if(f==NULL){
					printf("Não foi encontrado nenhum contribuidor\n");
					
				}	
				printf("ID do contribuidor: %ld  Contribuidor: %s",x,f);
				
			}
			if(q ==  6){
				long* aux = top_20_largest_articles(qs);
				for(int i = 1; i<20;i++) printf("%ld\n",aux[i]);
					
			}						
			if(q ==  7){
				long aux;
				printf("Insira o id do articulo desejado\n");
				scanf("%ld",&aux);
				char * string = NULL;
				string = article_title(aux,qs);
				if(string != NULL) printf("Artigo id%ld, Titulo: %s\n",aux,string);
				
			}
			if(q == 8){
				printf("Insira a quantidade de artigos com o maior numero de palavras\n");
				int j = 0;
				scanf("%d",&j);
				long* aux = top_N_articles_with_more_words(j,qs);
				for(int i = 1; i < j; i++)printf("%ld\n",aux[i]);
				
			}
			if(q ==  9){
				char c[30];
				char** f;
				printf("Insira o prefixo\n");
				scanf("%s\n",c);
				f = titles_with_prefix(c,qs);
				for(int i = 0; f[i]; i++){
					printf("Titulo:%s\n",f[i]);
				}
			}
			if(q ==  10){
				printf("Insira o id do artigo seguido do id da revisao\n");
				long f,c;
				scanf("%ld",&f);
				scanf("%ld",&c);
				char * aux = article_timestamp(f,c,qs);
				if(aux == NULL) printf("Não foi encontrado\n");
				
			}
			if(q>10){
				printf("Opção errada\n");
				return;
				
			}
			menu_query();
		}
	
}

void menuInt(TAD_istruct qs){
	menu_principal();
	int n = -1;
	scanf("%d\n",&n);
	return;
}

int main(int argc, char** argv){
	TAD_istruct qs = init();
	qs = load(qs,argc-1,argv+1);
	//menuInt(qs);
	interpretador(qs);
	printf("para ja nada");
	return 1;
}
