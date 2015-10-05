#if !defined INC_LIFT_REALLOC
#define INC_LIFT_REALLOC

/** @file
 * Safe alternative for realloc() for arrays. Part of LIFT, but can
 * be used on its own - doesn't depend on anything from LIFT.
 * @author Srdjan Veljkovic
 * @copyright MIT License
 */


#include <stdlib.h>


/**
 * A safe alternative to realloc() for arrays. It avoids the problems
 * of overflow (@p members * @size may overflow) and "leaking" the
 * previously allocated memory in case of failure. In case you're not
 * aware of it, here is the offending code:
 *
 *     char *s = malloc(100);
 *     s = realloc(s, 200);
 *
 * If realloc() fails, `s` will now be NULL, and previously malloc()-
 * ated memory is leaked, there is no way to free it now.
 *
 * The only problem that lift_arealloc() doesn't solve is that
 * passing an invalid pointer (not NULL or "really" allocated)
 * results in undefined behavior.
 *
 * @warning Don't forget to pass the address of your pointer,
 * rather than the pointer itself, even though the formal
 * parameter type for @ptrptr is `void*`.
 *
 * So, to fix the realloc() problem cited above, we would:
 *
 *     char *s = malloc(100);
 *     if (NULL == lift_arealloc(&s, 200, sizeof(char)) {
 *         // handle reallocation failure, but `s` stayed the same
 *     }
 *
 * @note The downside is that may simply forget to pass the address
 * of your pointer, and pass the pointer itself, and there is no
 * way that we can detect that. Declaring @p ptrptr to be a `void**`
 * would have actually been worse, as that would require cast
 * if you want to avoid warnings (or even errors) for passing a
 * pointer to, say, `int*`, instead of to `void*`. So, passing
 * something like `3`, because you cast it to `void**` would
 * not be detected.
 *
 * To help with these usability issues, you should probably use
 * @ref lift_arealloc macro instead of this function.
 *
 * @remark On detecting overflow or any other invalid usage, it will _not_
 * call realloc and will return NULL and set `errno` to ERANGE.
 * If realloc() returns NULL, @p ptrptr will not be changed. Otherwise,
 * the result of realloc() will be written to `*ptrptr`.
 *
 * @param[in,out] ptrptr Pointer to pointer to be reallocated. NULL is invalid.
 * If not NULL, and other checks pass, `*ptrptr` will passed to realloc().
 *
 * @param[in] members The number of members of the new array. If the result of
 * multiply with @p size doesn't overflow, that result will be passed to
 * realloc(). Also, if it or @size is 0, the function may fail.
 *
 * @param[in] size Size of a member of the new array. If the result of
 * multiply with @p members doesn't overflow, that result will be passed to
 * realloc(). Also, if it or @members is 0, the function may fail.
 *
 * @return On internal or realloc() failure, will return NULL. Otherwise,
 * will return the result of realloc().
 *
 */
void *lift_arealloc_implementation(void *ptrptr, size_t members, size_t size);
/** @example lift_arealloc_example.c */


/** This macro makes lif_arealloc_implementation() a lot easier to use and less
 * error prone. It is a _good_ macro, as it is very simple and
 * doesn't evaluate its arguments more than once.
 *
 * We fix two usability issues:
 * 1. You may pass a pointer (to a value) instead of a pointer to pointer
 * 2. You may pass a wrong (element) size
 *
 * Here we accept a pointer, and you can't pass a value.
 * You can, of course pass a pointer to pointer, but, that may be valid
 * input, so we can't reject that.
 *
 * The size of an element is deduced to be `sizeof *ptr`.
 *
 * @param ptr The pointer to reallocate - it will be changed "in place",
 * if need be.
 * @param members The number of members of the new array
 * @return Pointer to the new array or NULL on failure to (re)allocate
 */
#define lift_arealloc(ptr, members) lift_arealloc_implementation(&(ptr),(members), sizeof *(ptr))
/** @example lift_arealloc_example.c */


#endif /* #defined INC_LIFT_REALLOC */
