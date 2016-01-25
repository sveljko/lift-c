#if !defined INC_LIFT
#define INC_LIFT

/** @mainpage LIFT

    LIFT is a collectiong of useful C modules.  It isn't a framework
    or a Toolkit. Most modules are either self-sufficient (depend only
    on parts of C standard library, or, in some cases, parts of
    standard library for a given system (POSIX, Windows...)), or
    depend on a few other LIFT modules.

    For a reasonably type-safe realloc for arrays (and, in most cases
    you use realloc for arrays), check out @ref lift_arealloc.h.

    For a reasonably type-safe free that also NULL-ifies the pointer,
    check out @ref lift_free_and_null.h.

    For a reasonably type-safe and efficient generic vector, with an
    interface inspired by C++ STL, check out @ref lift_vec.h.

    For a minimalistic, type-safe and efficient generic list, with
    interface having no resemblense of C++ STL, check out @ref
    lift_list.h.
*/

#include "lift_arealloc.h"
#include "lift_free_and_null.h"
#include "lift_vec.h"

/** @file */


#endif /* defined INC_LIFT */
