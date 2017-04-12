#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>


void parsingTitleS(xmlDocPtr doc, xmlNodePtr cur){
    cur = cur -> xmlChildrenNode;
    xmlChar* cena;
	while(cur != NULL){
        if((!xmlStrcmp(cur->name,(const xmlChar*)"title"))){
            cena = xmlNodeListGetString(doc, cur-> xmlChildrenNode,1);
            printf("OI %s",cena);
            xmlFree(cena);
            break;
        	}
        else cur = cur->next;
    }
    return;
}


int main(int argc,char** argv){
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
    printf("%s\n",dad->name );
 //	parsingTitleS(doc,dad);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;
}
