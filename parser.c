#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>


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
        		printf("Artigo ID: %s, artigo numero : , %d \n",chr,  contador);
        		contador++;
        		}
        	child = xmlNextElementSibling(child);
    	}
    	parente = xmlNextElementSibling(parente);
    }  
    printf("contador %d\n",contador);
    return contador;
    }


int main(int argc,char** argv){
	if(argc != 2){
		 printf("falta argumentos\n");
		 return 0;
    }
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr dad;
    int contador = 0;
    doc = xmlParseFile(argv[1]);
    if(doc == NULL) return 0;
    dad = xmlDocGetRootElement(doc);
    cur = dad -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    printf("o cur é: %s\n",cur->parent->name);
 	contador = allArticles(doc,cur);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return contador;
}
