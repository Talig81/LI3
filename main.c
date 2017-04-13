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
    int conta = 0;
    char * cenas = "ccenas";
    char * oi = (char * )malloc(sizeof(char)*strlen(cenas)+1);
    strcpy( oi, cenas);


    printf("Insert: ");
    for( i = 0; i < max; i++, j = ( j + 7 ) % max )
    {

        t = insert( j, t, &conta, oi);
        printf("%d ",j);

    }
    printf(" intoergerg the tree\n\n");

    display_avl(t);

    dispose(t);

    return 0;
}
