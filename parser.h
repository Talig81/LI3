#ifndef PARSER_H
#define PARSER_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include "avl.h"
#include "linklist.h"


node* parseDocs(char* ficheiro,llink** l,long** i,node** b,llink** k);

#endif