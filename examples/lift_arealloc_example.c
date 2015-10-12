/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "lift_arealloc.h"

#include <stdio.h>
#include <assert.h>


int main()
{
    int *v = NULL;
    if (NULL == lift_arealloc_implementation(&v, 4, sizeof *v)) {
        printf("Failed to allocate memory\n");
        return -1;
    }
    v[0] = v[1] = v[2] = v[3] = 4443;

    if (NULL == lift_arealloc_implementation(&v, 8, sizeof *v)) {
        printf("Failed to re-allocate memory\n");
	return -1;
    }
    if (NULL == lift_arealloc_implementation(&v, (size_t)~0, sizeof *v)) {
        printf("Failed to re-allocate memory, as expected\n");
    }
    v[4] = v[5] = v[6] = v[7] = 443;

    if (NULL == lift_arealloc(v, 6)) {
        printf("Failed to re-allocate memory\n");
	return -1;
    }
    if (NULL == lift_arealloc(v, (size_t)~0)) {
        printf("Failed to re-allocate memory, as expected\n");
    }

    assert(v[5] == 443);

    free(v);

    puts("lift_arealloc() example finished normally");

    return 0;
}
