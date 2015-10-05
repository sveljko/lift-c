#include "lift_arealloc.h"

#include <limits.h>
#include <errno.h>


#define MAX_size_t ((size_t)~0)
#define SQRT_SIZE_MAX (1UL << ((CHAR_BIT/2) * sizeof(size_t)))


void *lift_arealloc_implementation(void *ptrptr, size_t members, size_t size)
{
    void *result;
    void **pp = ptrptr;

    if (NULL == ptrptr) {
	errno = ERANGE;
        return NULL;
    }
    if (((members >= SQRT_SIZE_MAX) || (size >= SQRT_SIZE_MAX)) &&
	((members > 0) && (size > MAX_size_t / members))) {
	errno = ERANGE;
        return NULL;
    }

    result = realloc(*pp, members * size);
    if (result != NULL) {
        *pp = result;
    }

    return result;
}
