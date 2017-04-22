#include "parser.h"
#define SIZE 20


int getPos(long* array, long numb){
    int i = 0;
    while(i<SIZE){
        if(numb > array[i]) return i;
        i++;
    }
return -1;
}

int sort_ordn(long* array, long numb){
    int j = getPos(array,numb);
    if(j==-1) return -1;
    long temp = array[j];
    long aux;
    array[j] = numb;
    for(int i=j+1;i<SIZE;i++){
        aux = array[i];
        array[i] = temp;
        temp = aux;
    }
    return j;
}

void sort_iDs(long* array,long numb,int pos){
    if(pos == -1) return;
    long temp = array[pos];
    long aux;
    array[pos] = numb;
    for(int i=pos+1;i<SIZE;i++){
        aux = array[i];
        array[i] = temp;
        temp = aux;
    }
}
void parseContributor(xmlDocPtr doc, xmlNodePtr contributor,LLINK l){
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
            l = insertUno(l,numb,user);
            xmlFree(user);
            xmlFree(idC);
        }    
        contributor = xmlNextElementSibling(contributor);
    }
}

void parseRevision(xmlDocPtr doc,xmlNodePtr revision,LLINK l,xmlChar** string,xmlChar** redID,NODE t,long* numr){
    xmlNodePtr contributor;
    int aux = 0;
    while(revision != NULL){
        if((!xmlStrcmp(revision->name,(const xmlChar*)"id"))){
            *redID = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
            aux = atoi(*redID);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"contributor"))){
           
            contributor = revision -> xmlChildrenNode;
            parseContributor(doc,contributor,l);
        }
        if((!xmlStrcmp(revision->name,(const xmlChar*)"timestamp"))){
            *string = xmlNodeListGetString(doc,revision->xmlChildrenNode,1);
        }
        revision = xmlNextElementSibling(revision);
    }
}

NODE parsePage(LLINK l,xmlDocPtr doc, xmlNodePtr child, NODE t){
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

NODE oneParse(LLINK l,xmlDocPtr doc, xmlNodePtr cur, NODE t,long** j,long* qtBytes,long* idsBytes){
    xmlNodePtr child;
    while(cur != NULL){
        child = cur -> xmlChildrenNode;
        t = parsePage(l,doc,child,t,*qtBytes,*idsBytes);
        (**j)++;
        cur = xmlNextElementSibling(cur);


    }
    return t;
}

NODE parseDocs(char* ficheiro,LLINK l,long** i,NODE t){
    NODE zx = t; 
    xmlDocPtr doc;
    long* j = *i;
    LLINK f = l;
    long qtBytes[20];
    long idsBytes[20];
    for(int iter = 0 ; iter<SIZE; iter++){
        qtBytes[iter] = (long)malloc(sizeof(long));
        idsBytes[iter] = (long)malloc(sizeof(long));
        idsBytes[iter] = qtBytes[iter] = 0;
    }
    doc = xmlParseFile(ficheiro);
    xmlNodePtr cur;
    cur = xmlDocGetRootElement(doc);
    cur = cur -> xmlChildrenNode;
    cur = xmlNextElementSibling(cur);
    cur = xmlNextElementSibling(cur);
    zx = oneParse(f,doc,cur,zx,&j,*qtBytes,*idsBytes);
    l = f;
    t = zx;
    *i = j;
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return zx;
}