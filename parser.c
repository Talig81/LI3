#include "parser.h"

void parseContributor(xmlDocPtr doc, xmlNodePtr contributor,llink** l){
    xmlChar* user;
    xmlChar* idC;
    int numb=0;
    while(contributor != NULL){
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"username"))){
            user = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);
            
        }
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"id"))){
            idC = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);  
            numb = atoi(idC);
            (*l) = insertUno((*l),numb,user);      
        }    
        contributor = xmlNextElementSibling(contributor);
    }
}

void parseRevision(xmlDocPtr doc, xmlNodePtr revision,llink** l){
    xmlNodePtr contributor;
    while(revision != NULL){
        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
            contributor = revision -> xmlChildrenNode;
            parseContributor(doc,contributor,l);
        }
        revision = xmlNextElementSibling(revision);
    }
}

node* parsePage(llink** l,xmlDocPtr doc, xmlNodePtr child, node* t){
    xmlChar* title;
    xmlChar* idD;
    xmlNodePtr revision;
    int numr=0;
    while(child != NULL){
        if((!xmlStrcmp(child->name,(const xmlChar*)"title"))){
            title=xmlNodeListGetString(doc,child->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
            idD = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
            numr = atoi(idD);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"revision"))){
            revision = child -> xmlChildrenNode;
            parseRevision(doc,revision,l);
        }
        if(numr != 0){
            t = insert(numr,t,title);
            numr = 0;
        }
        child = xmlNextElementSibling(child);
    }
    return t;

}

node* oneParse(llink** l,xmlDocPtr doc, xmlNodePtr cur, node* t,long** j){
    xmlNodePtr child;
    while(cur != NULL){
        child = cur -> xmlChildrenNode;
        t = parsePage(l,doc,child,t);
        (**j)++;
        printf("%ld\n",**j);
        cur = xmlNextElementSibling(cur);


    }
    return t;
}

node* parseDocs(char* ficheiro,llink** l,long** i){
    node* t = NULL;
    xmlDocPtr doc;
    long* j = *i;
    llink* f = *l;
    doc = xmlParseFile(ficheiro);
    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    t = oneParse(&f,doc,cur,t,&j);
    *l=f;
    *i=j;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return t;
}