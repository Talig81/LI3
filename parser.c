#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "avl.h"
#include "linklist.h"

int allArticles(xmlDocPtr doc, xmlNodePtr cur){
	int contador = 0;
	xmlChar* chr;
	xmlNodePtr parente = cur;
	xmlNodePtr child = parente->xmlChildrenNode;
    while(parente != NULL){
    	child = parente -> xmlChildrenNode;
		while(child != NULL){
			//printf("Tou num ciclo e : %s ,contador %d: \n", child->name, contador);
        	if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
        		chr = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
        		contador++;
        		xmlFree(chr);
        		}
        	child = xmlNextElementSibling(child);
    	}
    	parente = xmlNextElementSibling(parente);
    }  
    return contador;
    }


node* unique(xmlDocPtr doc,xmlNodePtr cur, node* t,llink**bl){
    int numr = 0;
    int contas=0;
    int atois;
    llink* l = *bl;
	xmlChar* title;
    xmlChar* ids;
    xmlChar* contrids;
    xmlChar* contribuidor;
	xmlNodePtr parente = cur;
	xmlNodePtr child = parente->xmlChildrenNode;
    xmlNodePtr revision;
    xmlNodePtr contrs;
    printf("%d\n",l->times);
    while(parente != NULL){
    	child = parente -> xmlChildrenNode;
		while(child != NULL){
        	if((!xmlStrcmp(child->name,(const xmlChar*)"title"))){
        		title = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
        	}
            if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
                ids = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
                numr = atoi(ids);
            }
            if(numr != 0){
                t = insert(numr,t,title);
                printf("Arvorezita: %d\n",t->data);
                numr=0;
            }
            if((!xmlStrcmp(child->name,(const xmlChar*)"revision"))){
                revision = child->xmlChildrenNode;
                    while(revision != NULL){
                        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
                            contrs = revision -> xmlChildrenNode;
                                while(contrs!=NULL){
                                    if((!xmlStrcmp(contrs->name,(const xmlChar*)"username"))){
                                        contribuidor = xmlNodeListGetString(doc,contrs->xmlChildrenNode,1);
                                    }
                                    if((!xmlStrcmp(contrs->name,(const xmlChar*)"id"))){
                                        contrids = xmlNodeListGetString(doc,contrs->xmlChildrenNode,1);
                                      //  printf("contrids: %s\n",contrids);
                                        if(contrids != NULL){
                                            atois = atoi(contrids);
                                            l = insertUno(l,atois,contribuidor);
                                            printf("%d\n",l->id);
                                        }
                                    }
                                    contrs = xmlNextElementSibling(contrs);
                                }
                        }
                        revision = xmlNextElementSibling(revision);
                    }

            }
        	child = xmlNextElementSibling(child);
    	}
    	parente = xmlNextElementSibling(parente);
    }
    if(t==NULL) printf("arvore vazia\n");
    if(t!=NULL) printf("lista vazia\n");
    xmlFree(title);
    xmlFree(ids);
    xmlFree(contrids);
    xmlFree(contribuidor);
    return t;
} 


int main(int argc,char** argv){
    node* t = NULL;
    llink* l = (llink*)malloc(sizeof(llink));
	if(argc != 2){
		 printf("falta argumentos\n");
		 return 0;
    }
    int sa = 10;
    char* s = "teste";
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr dad;
    int todos = 0;
    int unicos = 0;
    doc = xmlParseFile(argv[1]);
    if(doc == NULL) return 0;
    dad = xmlDocGetRootElement(doc);
    cur = dad -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
 	//contador = allArticles(doc,cur);
    t = unique(doc,cur,t,&l);
     if(t==NULL) printf("Continua a foder gui\n");
     if(l==NULL) printf("quaaaaase que funcionava\n");
   // todos = allArticles(doc,cur);
   // printf("todos: %d\n unicos: %d\n",todos,unicos);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
