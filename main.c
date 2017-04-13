#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include <string.h>

int main()
{
    node *t , *p;
    int i;
    int j = 0;
    const int max = 10;

    printf("--- C AVL Tree Demo  ---\n");

    t = NULL;
    char * cenas = "ccenas";
    char * oi = (char * )malloc(sizeof(char)*strlen(cenas)+1);
    strcpy( oi, cenas);


    printf("Insert: ");
    for( i = 0; i < max; i++, j = ( j + 7 ) % max )
    {

        t = insert( j, t, oi);
    }
    int n = 0;
    n = (int) countNodes(t);
    printf("numero: %d\n",n);
    dispose(t);

    return 0;
}
