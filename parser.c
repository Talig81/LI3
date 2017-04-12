#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


void parsingTitleS(xmlDocPtr doc, xmlNodePtr cur, xmlChar* cena){
	while(cur != NULL){
        if((!xmlStrcmp(cur->name,(const xmlChar*)"title"))){
            cena = xmlNodeListGetString(doc, cur-> xmlChildrenNode,1);
            printf("%s",cena);
            break;
        	}
        else cur = cur->next;
    }
}


int main(int argc,char** argv){
	if(argc != 2){ 
		 printf("falta argumentos\n");
		 return 0; 
    }
    xmlDocPtr doc;
    xmlNodePtr cur;
    FILE *f;
    f = fopen(argv[2],"w");

    doc = xmlParseFile(argv[1]);
    if(doc == NULL) return 0;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    xmlChar* test;
 	parsingTitleS(doc,cur,test);
 	xmlFree(test);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
    
            
