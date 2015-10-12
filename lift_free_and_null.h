/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#if !defined INC_LIFT_FREE_AND_NULL
#define INC_LIFT_FREE_AND_NULL


/** @file
    A safer alternative to free().
    @author Srdjan Veljkovic
    @copyright MIT license
*/

/** An alternative / wrapper to free(). It will NULL the pointer,
    not just free() it. Thus, you will not have a dangling
    pointer.

    Passing NULL or a pointer to NULL (pointer)
    will simply be ignored. Otherwise, free() will be
    called on `*ptrptr` and then it will be NULL-ed.

    @warning You must pass the address of your pointer, not
    the pointer itself. Since @p ptrptr is of `void*`, it
    will not detect if you pass the pointer, and we shall
    have undefined behavior.

    @remarks The advantage of this function versus a pure macro
    implementation is that we avoid the problem of multiple
    evaluation in the macro. That should make it easier to
    find bugs with not passing address of a pointer (but
    the pointer itself).

    We provida macro wrapper in @ref lift_nfree, that solves
    this usability problem.

    @remarks Declaring `ptrptr` to be of `void **` type
    would be much worse, as to silence warnings (or maybe
    errors) one would need to cast to `void**` always,
    which would enable passing _anything_.

    @param[in,out] ptrptr Pointer to the pointer to
    free and NULL
*/
void lift_free_and_null(void *ptrptr);
/** @example lift_free_and_null_example.c */

/** This macro solves the usability problem with lift_free_and_null().
    It is a _good_ macro, as it is simple and does not evaluate its
    argument more than once.

    Here we expect a pointer and you can't pass a variable. Of course,
    you may pass a pointer to pointer, but that may be valid input.

    There is an additional check - you can't pass a void pointer. That
    means that some strange, but valid code, will not compile. If you
    have such code, use lift_free_and_null(), but be careful.

    @param ptr The pointer to free (previously allocated by malloc()
    or realloc()). It will be set to NULL "in place"
    @return The size of what the @p ptr points to
*/
#define lift_nfree(ptr) lift_free_and_null(&(ptr)), sizeof *(ptr)
/** @example lift_free_and_null_example.c */


#endif /* !defined INC_LIFT_FREE_AND_NULL */
