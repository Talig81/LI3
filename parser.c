#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "avl.h"

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
    printf("contador %d\n",contador);
    return contador;
    }

int unique(xmlDocPtr doc,xmlNodePtr cur, node* t){
    int numr = 0;
    int flagie = 0;
	xmlChar* title;
    xmlChar* ids;
	xmlNodePtr parente = cur;
	xmlNodePtr child = parente->xmlChildrenNode;
    while(parente != NULL){
    	child = parente -> xmlChildrenNode;
		while(child != NULL){
        	if((!xmlStrcmp(child->name,(const xmlChar*)"title"))){
        		title = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
                flagie += 1;

        	}
            if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
                ids = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
                numr = atoi(ids);
                flagie += 1;
            }
            if(flagie == 2 && numr != 0){
                t = insert(numr,t,title);
                xmlFree(title);
                xmlFree(ids);
                numr=0;
                flagie=0;
            }
        	child = xmlNextElementSibling(child);
    	}
    	parente = xmlNextElementSibling(parente);
    }
    return countNodes(t);
}  

int main(int argc,char** argv){
    node* t = NULL;
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
    unicos = unique(doc,cur,t);
    todos = allArticles(doc,cur);
    printf("todos: %d\n unicos: %d\n",todos,unicos);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    dispose(t);
    return 0;
}
