/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "lift_free_and_null.h"

#include <stdio.h>
#include <stdlib.h>


int main()
{
    char *s = malloc(100);
    printf("s = %p; after malloc()\n", s);
    free(s);
    printf("s = %p; after free()\n", s);

    s = malloc(1000);
    printf("s = %p; after another malloc()\n", s);
    lift_free_and_null(&s);
    printf("s = %p; after lift_free_and_null()\n", s);

    s = malloc(10000);
    printf("s = %p; after yet another malloc()\n", s);
    lift_nfree(s);
    printf("s = %p; after lift_nfree()\n", s);

    return 0;
}
