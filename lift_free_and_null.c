/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "lift_free_and_null.h"

#include <stdlib.h>


void lift_free_and_null(void *ptrptr)
{
    void **pp = ptrptr;
    if ((NULL != pp) && (NULL != *pp)) {
        free(*pp);
        *pp = NULL;
    }
}
