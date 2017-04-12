#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>


int allArticles(xmlDocPtr doc, xmlNodePtr cur){
	int contador = 0;
	xmlNodePtr parente = cur;
	xmlNodePtr child = parente->xmlChildrenNode;
    while(parente != NULL){
    	child = parente -> xmlChildrenNode;
		while(child != NULL){
        	if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
        		contador++;
        		}
        	else child = xmlNextElementSibling(child);
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
    printf("o cur é: %s\n",cur->name);
 	contador = allArticles(doc,cur);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return contador;
}
