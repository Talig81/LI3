#include "parser.h"


void parseContributor(xmlDocPtr doc, xmlNodePtr contributor,llink** l){
    xmlChar* user='\0';
    xmlChar* idC=NULL;
    int numb=0;
    while(contributor != NULL){
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"username"))){
            if(contributor->xmlChildrenNode=='\0')return;
            user = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"id"))){
            idC = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);  
            numb = atoi(idC);
            (*l) = insertUno((*l),numb,user);
            xmlFree(user);
            xmlFree(idC);
        }    
        contributor = xmlNextElementSibling(contributor);
    }
}

void parseRevision(xmlDocPtr doc,xmlNodePtr revision,llink** l,xmlChar** string,xmlChar** redID,node* t,long* numr){
    xmlNodePtr contributor;
    int aux = 0;
    while(revision != NULL){
        if((!xmlStrcmp(revision->name,(const xmlChar*)"id"))){
            *redID = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
            aux = atoi(*redID);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
           if((encontraRev(t,&aux,numr)) == 0){
            contributor = revision -> xmlChildrenNode;
            parseContributor(doc,contributor,l);}
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"timestamp"))){
            *string = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
        }
        revision = xmlNextElementSibling(revision);
    }
}

node* parsePage(llink** l,xmlDocPtr doc, xmlNodePtr child, node* t){
    xmlChar* title;
    xmlChar* idD;
    xmlNodePtr revision;
    xmlChar* times;
    xmlChar* idS;
    int flag = 1;
    long numr=0;
    int numID=0;
    while(child != NULL){
        if((!xmlStrcmp(child->name,(const xmlChar*)"title"))){
            title=xmlNodeListGetString(doc,child->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
            idD = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
            numr = atol(idD);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"revision"))){
            revision = child -> xmlChildrenNode;
            parseRevision(doc,revision,l,&times,&idS,t,&numr);
            numID = atoi(idS);
        }
        if(numr != 0&&numID!=0){
            t = insert(numr,t,title,times,numID);
            numr=0;
            numID=0;
            xmlFree(title);
            xmlFree(idD);
            xmlFree(idS);
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
        cur = xmlNextElementSibling(cur);


    }
    return t;
}

node* parseDocs(char* ficheiro,llink** l,long** i,node** t){
    node* zx = *t; 
    xmlDocPtr doc;
    long* j = *i;
    llink* f = *l;
    doc = xmlParseFile(ficheiro);
    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    zx = oneParse(&f,doc,cur,zx,&j);
    *l=f;
    *i=j;
    zx;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return zx;
}