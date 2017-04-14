#include <stdio.h>
#include "linklist.h"
#include <stdlib.h>
#include <string.h>

void deletas(llink** l){
		llink* current = *l;
		llink* next;
		while(current != NULL){
			next = current -> next;
			free(current -> author);
			free(current);
			current->next = NULL;
			current = next;
		}
		*l = NULL;
	}


llink* encontra(int ids, llink* l){
	llink* t = l;
	llink* c = l;
	t = t -> next;
	while(t!=NULL){
		if(t->id == ids) return c;
		c = t;
		t = t->next;
	}
	return NULL;
}

llink* cria(int ids, char* string){
	llink* l = (llink*) malloc(sizeof(llink));
	l -> id = ids;
	l -> author = (char*)malloc(sizeof(char)*strlen(string)+1);
	strcpy(l->author, string);
	l -> times = 1;
	l -> next = NULL;
	return l;
}

int encontraPrimeiro(int ids,llink* l){
	if(ids == l->id) return 1;
	else return 0;
}

llink* lasti(llink* l){
	while(l->next != NULL){
		l = l -> next;
	}
	return l;
}

llink* insertUno(llink* l, int ids,char* string){
	if(l==NULL){
		l = cria(ids,string);
		return l;
	}			
	llink* test;
	llink* aux = l;
	if(encontraPrimeiro(ids,l)==1){
		l -> times += 1;
		return l;
	}
	test = encontra(ids,l);
	if(test!=NULL){
		test->next->times += 1;
		l = ordenador(aux,test);
		return l;
	}
	else{
		aux = lasti(aux);
		llink* nodo = cria(ids,string);
		aux -> next = nodo;
		return l;
	}
}

llink* ordenador(llink* l,llink* f){
		llink* c = f -> next;
		llink* aux = l;
		if(c -> times > f -> times){
			f -> next = c -> next;
			c -> next = NULL;
			if(aux -> times <= c -> times){
				c -> next =aux;
				l = c;
				return l;
			}
			else{
				while(aux -> next-> times > c -> times){
					aux = aux -> next;
					}
				c -> next = aux -> next;
				aux -> next = c;
				}
			}
			return l;
		}

void printas(llink* l){
		while(l!=NULL){
			printf("Id: %d(%d)\n",l->id,l->times);
			l = l->next;
		}
	}


int main(int argc,char** argv){
	int n = 6;
	llink* l = cria(10,"fuck");
	l -> next = cria(11,"fuck");
	l -> next -> next = cria(12,"fucki");

		l = insertUno(l,10,"stringas");
		l = insertUno(l,11,"stringas");
		l = insertUno(l,11,"stringas");
		l = insertUno(l,10,"stringas");
		l = insertUno(l,12,"stringas");
		l = insertUno(l,3,"stringas");
	
	

	printas(l);
	return 1;
}