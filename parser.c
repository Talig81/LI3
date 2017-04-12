#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>


void allArticles(xmlDocPtr doc, xmlNodePtr cur,int contador){
    cur = cur -> xmlChildrenNode;
    xmlChar* cena;
	while(cur != NULL){
        if((!xmlStrcmp(cur->name,(const xmlChar*)"id"))){
        	contador++;
            cena = xmlNodeListGetString(doc, cur-> xmlChildrenNode,1);
            xmlFree(cena);
        	}
        else cur = cur->next;
    }
    return;
}


int main(int argc,char** argv){
	int contador = 0;
	if(argc != 2){
		 printf("falta argumentos\n");
		 return 0;
    }
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr dad;

    doc = xmlParseFile(argv[1]);
    if(doc == NULL) return 0;
    dad = xmlDocGetRootElement(doc);
    dad = dad -> xmlChildrenNode;
    dad = dad -> next;
  //  dad = dad -> next;
  //  dad = dad -> next;
    //cur = cur -> next;
    //cur = cur -> next;
    dad = xmlNextElementSibling(dad);
 	allArticles(doc,dad,contador);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return contador;
}
