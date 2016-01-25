/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#if !defined INC_LIFT_VEC
#define INC_LIFT_VEC

#include "lift_arealloc.h"
#include "lift_free_and_null.h"

#include <string.h>
#include <stdio.h>


/** @file
    A vector generic type for C. It is modelled after the C++ (STL)
    vector. It is a macro implementation, but some care was taken
    to make it as safe as possible:

    - No variables are declared in the macros themselves
    - Most macros are expressions
    - There is a reasonable amount of checking done...
    - ...and most type errors will be caught, with maybe ugly compiler errors

    The only significant problem with this implementation is that _a_
    lot of parameters in these macros a evaluated more than once. So,
    you have to be careful not to pass expressions with side effects.

    @author Srdjan Veljkovic
    @copyright MIT License
 */
/** @example lift_vec_example.c */

/** Declare a vector for the given type @p typ.
    A lot of the time you should `typedef` this.
 */
#define LIFT_DECL_VEC(typ) struct { unsigned n; unsigned c; typ *p; }

/** Declare a variable of the vector of type @p typ, with the name
    (symbol) @p var.  Be aware that, while macros will work on this
    variable, it's type will not be the same as other variables
    declared with this macro in C99 and newer versions. To solve that,
    define a type with `typedef LIFT_DEL_VEC(typ)`, then a variable of
    such type and then use LIFT_VEC_INIT() to initialize it.

    @see LIFT_VEC_INIT
 */
#define LIFT_VEC_VAR(typ, var) LIFT_DECL_VECT(typ) =  { 0, 0, NULL }

/** Initializes a vector variable with symbol/name @var. 
 */
#define LIFT_VEC_INIT(var) memset(&(var), 0, sizeof (var))

/** Gives an iterator (pointer, really) to the begining of the vector
    @p var. This is the first element if vector is not empty. If the
    vector is empty, the only guarantee is that lift_vec_begin(v) ==
    lift_vec_end(v).
*/
#define lift_vec_begin(var) ((var).p)

/** Gives an iterator (pointer, really) to the end of the vector @p
    var. This points to an element one past the last element of the
    vector, if vectory is not empty.  If the vector is empty, the only
    guarantee is that lift_vec_begin(v) == lift_vec_end(v).
*/
#define lift_vec_end(var) ((var).p + (var).n)

/** Returns whether the given iterator @p iter is valid for the
    given vector @var. Iterator is valid if it is in the range
    [begin, end].
*/
#define LIFT_VEC_VALID_ITERATOR(var, iter) (((iter) >= lift_vec_begin(var)) && (((iter) <= lift_vec_end(var))))

/** Returns whether the given iterator @p iter is safe to dereference
    for the given vector @var. Iterator is safe if it is in the range
    [begin, end).
*/
#define LIFT_VEC_SAFE_ITERATOR(var, iter) (((iter) >= lift_vec_begin(var)) && (((iter) < lift_vec_end(var))))

/** Returns the number of elements in the vector @p var */
#define lift_vec_size(var) ((var).n)

/** Resizes the vector @p var to have @p newsize elements.
    If vector needs to be enlarged, the contents of the new elements
    is not defined.
    @todo This doesn't handle all cases yet
*/
#define lift_vec_resize(var, newsize)					\
    (((var.n < newsize) && lift_vec_reserve(var, newsize)) ?		\
     (									\
         (var).n = (newsize),                                           \
         (newsize))                                                     \
     : 0                                                                \
        )

/** Returns the current capacity of the vectory @p var */
#define lift_vec_capacity(var) ((var).c)

/** Returns whether the vectory @p var is empty (has no elements) */
#define lift_vec_empty(var) (0 == (var).n)

/** Reserves the memory for vectory @p var to have place for @p newcap
   elements.  */
#define lift_vec_reserve(var, newcap)                                   \
    ((((var).c < (newcap)) && lift_arealloc((var).p, (newcap)+1)) ?     \
     (									\
         (var).c = (newcap),                                            \
         (newcap))                                                      \
     : 0                                                                \
        )

/** Pushes the value @p val to the end of vector @p var, increasing 
    the vector's size. If successful, returns 0, otherwise -1.
*/
#define lift_vec_push_back(var,val)                                     \
    ((((var).n < (var).c) || lift_vec_reserve(var, ((var).c+1))) ?      \
     (									\
         (var).p[(var).n++] = val,                                      \
         0)                                                             \
     : -1                                                               \
        )

/** Removes the last element of the vectory @p var, if the vector
    is not empty. If the vector is not empty, returns NULL.
*/
#define lift_vec_pop_back(var)                                          \
    (((var).n > 0) ?                                                    \
     (                                                                  \
         --(var).n,                                                     \
         lift_vec_end(var))                                             \
     : NULL                                                             \
        )

/** Inserts the value @p val into the vector @p var at iterator/position
    @p pos. The @p pos has to be a valid pointer - which includes the
    "end" pointer (if you pass the end, you will insert at the end of
    the vector, just like lift_vec_push_back()).
    On success, increases the size of the vector @p var and returns the
    iterator at which the value @p val was inserted.
    On error, returns NULL.
*/
#define lift_vec_insert(var, pos, val)                                  \
    (LIFT_VEC_VALID_ITERATOR(var, pos) ?                                \
     ((((var).n < (var).c) || lift_vec_reserve(var, ((var).c+1))) ?     \
      (memmove((pos)+1, (pos), ((var).n - ((pos) - lift_vec_begin(var))) * sizeof *(var).p), \
       *(pos) = val,                                                    \
       ++(var).n,                                                       \
       (pos))                                                           \
      : NULL)                                                           \
     : NULL                                                             \
        )  

/** Erases the element of the vector @p var at iterator/position @p pos.
    The @p pos has to be a safe iterator - meaning, it can't be the "end".
    On success, decreases the size of the vector @p var and returns the
    iterator at which the value @p val was erased.
    On error, returns NULL.
 */
#define lift_vec_erase(var, pos)                                        \
    (LIFT_VEC_SAFE_ITERATOR(var, pos) ?                                 \
     (                                                                  \
         memmove((pos), (pos) + 1, ((var).n - 1 - ((pos) - lift_vec_begin(var))) * sizeof *(var).p), \
         --(var).n,                                                     \
         (pos))                                                         \
     : NULL                                                             \
        )  

/** Once you're done with the vector, use this macro to free
    any resources (memory) that was allocated during its use.
    After a call to this, vector is invalid.
 */
#define lift_vec_free(var) lift_nfree((var).p), (var).n = (var).c = 0

/** Allows you to set element at the front (beginning) of the vector. 
    Use like: `lift_vec_front(v) = 3;`.
*/
#define lift_vec_front(var) lift_vec_at(var, 0)

/** Returns the element at the front (beginning) of the vector */
#define lift_vec_front_get(var) (lift_vec_at(var, 0))

/** Allows you to set element at the back of the vector (last element). 
    Use like: `lift_vec_end(v) = 43;`.
*/
#define lift_vec_back(var) lift_vec_at((var), (var).n-1)

/** Returns the element at the front (beginning) of the vector */
#define lift_vec_back_get(var) (lift_vec_at(var, (var).n-1))

/** Returns the data (array pointer) of the vector @p var, which you can
    pass to some function that expects such things.
*/
#define lift_vec_data(var) (var).p

/** Returns whether the vector @p var is valid */
#define LIFT_VEC_VALID(var) ((var).p != NULL)

/** Returns whether it is safe to access the element at index
    @p idx of the vector @p var
*/
#define LIFT_VEC_SAFE(var,idx) (idx < lift_vec_size(var))

/** Gives the element at index @p idx of the vector @p var, checking
    if it is safe to access it.
 */
#define lift_vec_at(var,idx) assert(LIFT_VEC_SAFE(var,idx)), lift_vec_begin(var)[idx]

/** Returns the element at index @p idx of the vector @p var, checking
    if it is safe to access it.
*/
#define lift_vec_get(var,idx) (lift_vec_at(var,idx))

/** A helper macro to execute a for-each loop on the vector @p var,
    accessing by the index @p idx. You have to declare the variable
    @p idx.
*/
#define LIFT_VEC_FOR_EACH_IDX(idx, var) for (idx = 0; idx < lift_vec_size(var); ++idx)


/** A helper macro to execute a for-each loop on the vector @p var,
    accessing by the iterator/pointer @p it. You have to declare the variable
    @p it.
*/
#define LIFT_VEC_FOR_EACH_ITER(it, var)  \
    for (it = lift_vec_begin(var); it != lift_vec_end(var); ++it)


/** A helper macro to search for the value @p val in the vector @p var.
    The result will be stored in the iterator/pointer @p rslt, that
    you must provide.
    On success, it will give a safe iterator/position at which the
    given value was found.
    On failure, it will give the end iterator.

    @note this will only work if the type of the elements that are
    stored in the vector is such that its variables can be compared
    using the `==` operator

    @see lift_vec_find_if
*/
#define lift_vec_find(var, val, rslt)                                   \
    for (rslt = lift_vec_begin(var); rslt != lift_vec_end(var); ++rslt) { \
        if (*rslt == (val)) {                                           \
            break;                                                      \
        }                                                               \
    }

/** A helper macro to search for the element position in the vector @p var
    that satisfies the @p predicate.
    The result will be stored in the iterator/pointer @p rslt, that
    you must provide.
    On success, it will give a safe iterator/position at which the
    given value was found.
    On failure, it will give the end iterator.

    The @p predicate is an expression that can operate on pretty much
    anything, but is expected to operate on the @p rslt, which will
    hold the current iterator in the vector. Use like:

        lift_vec_find_if(v, *iter == 55, iter); // vector of integers
        lift_vec_find_if(v, iter->a == 55, iter); // vector of some structures

    @see lift_vec_find
*/
#define lift_vec_find_if(var, predicate, rslt)                          \
    for (rslt = lift_vec_begin(var); rslt != lift_vec_end(var); ++rslt) { \
        if (predicate) {                                                \
            break;                                                      \
        }                                                               \
    }

#define lift_vec_bsearch(var, val, rslt, aux)                           \
    for (rslt = lift_vec_begin(var), aux = lift_vec_end(var); rslt < aux; ) { \
        void *probe_ =  rslt + (aux - rslt) / 2;                        \
        if (val == *(rslt + (aux - rslt) / 2)) {                        \
            rslt = probe_;                                              \
            break;                                                      \
        }                                                               \
        else if (val < *(rslt + (aux - rslt) / 2)) {                    \
            aux = probe_;                                               \
        }                                                               \
        else {                                                          \
            rslt = (void*)((char*)probe_ + sizeof *rslt);               \
        }                                                               \
    }


/** A helper macro to printf-out the vector @p var */
#define LIFT_PRINTF(var) printf("'"#var "' lift_vec: size=%d, capacity=%d, data=%p\n", (var).n, (var).c, (var).p)


#endif /* !defined INC_LIFT_VEC */
