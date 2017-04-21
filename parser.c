#include "parser.h"
#include <stdbool.h>


bool space(char c){
    return (c == ' ' || c == '\n' || c == '\t');
}

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

void parseText(xmlDocPtr doc, xmlNodePtr texts,int* in){
    char* text = (char*)xmlNodeGetContent(texts);
    long nBytes=0;
    int nWords=0;
    bool inWord = false;
    int i;
    for(i=0;text[i]!='\0';i++){
        if(inWord == false && !space(text[i])){
            inWord=true;
            nWords += 1;
        }
        if(inWord == true && space(text[i]))
            inWord = false;
    }
    (*in)=nWords;
    nBytes = i - 1;

}

void parseRevision(xmlDocPtr doc,xmlNodePtr revision,llink** l,xmlChar** string,xmlChar** redID,int* in){
    xmlNodePtr contributor;
    int i=0;
    while(revision != NULL){
        if((!xmlStrcmp(revision->name,(const xmlChar*)"id"))){
            *redID = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
            contributor = revision -> xmlChildrenNode;
            parseContributor(doc,contributor,l);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"timestamp"))){
            *string = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"text"))){
            parseText(doc, revision,&i);
        }
        revision = xmlNextElementSibling(revision);
    }
    (*in) = i;
}

node* parsePage(llink** l,xmlDocPtr doc, xmlNodePtr child, node* t,llink** k){
    xmlChar* title;
    xmlChar* idD;
    xmlNodePtr revision;
    xmlChar* times;
    xmlChar* idS;
    int numW=0;
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
            parseRevision(doc,revision,l,&times,&idS,&numW);
            numID = atoi(idS);
        }
        if(numr != 0&&numID!=0){
            t = insert(numr,t,title,times,numID);
            (*k) = insertUno((*k),numW,title);
            numr=0;
            numID=0;
        }
        child = xmlNextElementSibling(child);
    }
    return t;

}

node* oneParse(llink** l,xmlDocPtr doc, xmlNodePtr cur, node* t,long** j,llink** k){
    xmlNodePtr child;
    while(cur != NULL){
        child = cur -> xmlChildrenNode;
        t = parsePage(l,doc,child,t,k);
        (**j)++;
        cur = xmlNextElementSibling(cur);


    }
    return t;
}

node* parseDocs(char* ficheiro,llink** l,long** i,node** b,llink** k){
    node* t = *b;
    xmlDocPtr doc;
    long* j = *i;
    llink* f = *l;
    llink* x = *k;
    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(ficheiro);
    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    t = oneParse(&f,doc,cur,t,&j,&x);
    *l=f;
    *i=j;
    *b = t;
    *k = x;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return t;
}