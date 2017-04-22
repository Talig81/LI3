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


NODE parseDocs(char* ficheiro,LLINK l,long** i,NODE t);

#endif