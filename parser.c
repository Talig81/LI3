#include "parser.h"
#include <stdbool.h>


bool palavra(char c){
    return (c == ' ' || c == '\n' || c == '\t');
}

long parseText(xmlDocPtr doc, xmlNodePtr texto,long* nW){
    char* text=(char*) xmlNodeGetContent(texto);
    long nBytes=0;
    long nWords=0;
    bool inWord = false;
    int i;
    for(i = 0; text[i] != '\0'; i++){
        if (inWord == false && !palavra(text[i])){
            inWord = true;
            nWords += 1; 
        }
        if (inWord == true && palavra(text[i])){
            inWord = false;
        }
    }
    *nW = nWords;
    nBytes = i - 1;
    return nBytes;
}

void parseContributor(xmlDocPtr doc, xmlNodePtr contributor,LLINK* l){
    xmlChar* user = NULL;
    xmlChar* idC = NULL;
    long numb=0;
    while(contributor != NULL){
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"username"))){
            user = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(contributor->name,(const xmlChar*)"id"))){
            idC = xmlNodeListGetString(doc,contributor->xmlChildrenNode,1);  
            numb = atol((const char*)idC);
            (*l) = insertUno((*l),numb,(char*)user);
        }    
        contributor = xmlNextElementSibling(contributor);
    }
}

char* parseRevision(xmlDocPtr doc,xmlNodePtr revision,LLINK* l,xmlChar** string,NODE* t,long* idArt,long* qtBytes,long* a){
    xmlNodePtr contributor,texto;
    xmlChar* idRev;
    int* aux = malloc(sizeof(int));
    while(revision != NULL){
        if((!xmlStrcmp(revision->name,(const xmlChar*)"id"))){
            idRev = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
            (*aux) = atoi((const char*)idRev);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
            if(encontraRev((*t),aux,(*idArt))==0){
                contributor = revision -> xmlChildrenNode;
                parseContributor(doc,contributor,l);  
            }
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"timestamp"))){
            *string = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
        }
        if ((!xmlStrcmp(revision->name, (const xmlChar *)"text")) && revision->type == 1){
            texto = revision -> xmlChildrenNode;
            *qtBytes= parseText(doc,texto,a);
        }   
        revision = xmlNextElementSibling(revision);
    }
    return (char*)idRev;
}

NODE parsePage(LLINK* l,xmlDocPtr doc, xmlNodePtr child, NODE* t){
    xmlChar* title;
    xmlChar* idPoin;
    xmlNodePtr revision;
    xmlChar* times;
    char* idparseRev = NULL;
    long idArt =0;
    long bytes = 0;
    int idRev=0;
    long *a = malloc(sizeof(long));
    *a = 0;
    while(child != NULL){
        if((!xmlStrcmp(child->name,(const xmlChar*)"title"))){
            title=xmlNodeListGetString(doc,child->xmlChildrenNode,1);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"id"))){
            idPoin = xmlNodeListGetString(doc,child->xmlChildrenNode,1);
            idArt = atol((const char*)idPoin);
        }
        if((!xmlStrcmp(child->name,(const xmlChar*)"revision"))){
            revision = child -> xmlChildrenNode;
            idparseRev = parseRevision(doc,revision,l,&times,t,&idArt,&bytes,a);
            idRev = atoi((const char*)idparseRev);
        }
        if(idArt != 0&&idRev!=0){
            (*t) = insert(idArt,(*t),(char*)title,(char*)times,idRev,a,&bytes);
            a = 0;
            idArt=0;
            idRev=0;
            xmlFree(title);
            xmlFree(idPoin);
            xmlFree(idparseRev);
        }
        child = xmlNextElementSibling(child);
    }
    return (*t);

}

NODE oneParse(LLINK *l,xmlDocPtr doc, xmlNodePtr cur, NODE* t,long** j){
    xmlNodePtr child;
    while(cur != NULL){
        child = cur -> xmlChildrenNode;
        (*t) = parsePage(l,doc,child,t);
        (**j)++;
        cur = xmlNextElementSibling(cur);
    }
    return (*t);
}

NODE parseDocs(char* ficheiro,LLINK* l,long** i,NODE* t){
    xmlDocPtr doc;
    long* j = *i;
    doc = xmlParseFile(ficheiro);
    xmlKeepBlanksDefault(0);
    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    (*t) = oneParse(l,doc,cur,t,&j);
    *i = j;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return (*t);
}