#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main(int argc,char** argv){
	if(argc != 3){ 
		 printf("falta argumentos\n");
		 return 0; 
    }
    xmlDocPtr doc;
    xmlNodePtr cur;
    

    doc = xmlParseFile(argv[1]);
    if(doc == NULL) return 0;
    cur = xmlDocGetRootElement(doc);
    xmlChar* test;
    while(cur != NULL){
        if((!xmlStrCmp(cur->name,(const xmlChar*)"title"))){
            test = xmlNodeListGetString(doc, cur-> xmlChildrenNode,1);
            break;}
        else cur = cur->next;
    }
    fprintf(argv[2],"%s",test);
    xmlFree(test);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
    
            
