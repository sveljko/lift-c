/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#if !defined INC_LIFT_LIST
#define INC_LIFT_LIST

#include <string.h>


/** @file lift_list.h

    A doubly linked list generic type for C. It is a macro
    implementation, but some care was taken to make it as safe as
    possible:

    - No variables are declared in the macros themselves
    - Most macros are expressions
    - There is a reasonable amount of checking done...
    - ...and most type errors will be caught, with maybe ugly compiler errors

    The only significant problem with this implementation is that _a_
    lot of parameters in these macros a evaluated more than once. So,
    you have to be careful not to pass expressions with side effects.

    This implementation goes for minimalism. One of the reasons for
    this is the macro implementation. 

    Hence, it doesn't do any memory management of the list elements at
    all. It's up to the user to allocate and deallocate the elements
    and take care of their lifetime.

    This doesn't follow the C++ STL interface. Some other list
    implementation in LIFT might follow the STL interface, if a way
    can be found for the implementation to be of similar type safety
    and (macro) complexity.

    @author Srdjan Veljkovic
    @copyright MIT License
 */
/** @example lift_list_example.c */

/** Declare a list (node) for the given type @p typ.
    A lot of the time you should `typedef` this.
 */
#define LIFT_DECL_LIST(typ) struct LiftList_##typ { struct LiftList_##typ *next; struct LiftList_##typ *prev; typ data; }

/** Declare a variable of the list (node) of type @p typ, with the name
    (symbol) @p var.  Be aware that, while macros will work on this
    variable, it's type will not be the same as other variables
    declared with this macro in C99 and newer versions. To solve that,
    define a type with `typedef LIFT_DEL_LIST(typ)`, then a variable of
    such type and then use LIFT_LIST_INIT() to initialize it.

    @see LIFT_LIST_INIT
 */
#define LIFT_LIST_VAR(typ, var) LIFT_DECL_LIST(typ) var =  { NULL, NULL }

/** Initializes a list (node) variable with symbol/name @p var. 
    This is the default initalization, which initializes the
    data to all 0.

    @warning The data initializaiton may not be a good value for your
    type, so you may need to change it after executing this.
 */
#define LIFT_LIST_INIT(var) memset(&(var), 0, sizeof (var))

/** Gives an iterator (node pointer, really) to the next element of
    the list node @p var. 
*/
#define lift_list_next(var) ((var)->next)

/** Gives an iterator (node pointer, really) to the previous element of
    the list node @p var. 
*/
#define lift_list_previous(var) ((var)->prev)

/** Predicate giving indication whether there is an element
    after the given @p var list node. */
#define lift_list_has_next(var) (lift_list_next(var) != NULL)

/** Predicate giving indication whether there is an element
    before the given @p var list node. */
#define lift_list_has_previous(var) (lift_list_previous(var) != NULL)

/** Links the element @p to_link before the @p before_this element,
    keeping any other elements in the list in the same order.
*/
#define lift_list_link_before(to_link, before_this) (to_link)->next = (before_this), (to_link)->prev = (before_this)->prev, (before_this)->prev ? (before_this)->prev->next = (to_link) : NULL, (before_this)->prev = (to_link)

/** Links the element @p to_link after the @after_this element,
    keeping any other elements in the list in the same order.
*/
#define lift_list_link_after(to_link, after_this) (to_link)->prev = (after_this), (to_link)->next = (after_this)->next, (after_this)->next ? (after_this)->next->prev = (to_link) : NULL, (after_this)->next = (to_link)

/** Unlinks the list node @p var from the list it is in. Has no
    effect if @p var is not in any list.

    @warning This may be a problem if @p var is the head of the list, as
    you may loose information of what element is the head after
    this. So, only use this if you know it is not a problem for you.
    Otherwise, use lift_list_unlink_safe()
 */
#define lift_list_unlink(var) ((var)->next) ? (var)->next->prev = (var)->prev : NULL,  ((var)->prev) ? (var)->prev->next = (var)->next : NULL, (var)->prev = (var)->next = NULL

/** Unlinks the list node @p var from the list it is in, with the @p
    head_pointer being the pointer to the list it is in (may be
    pointer to @p var). Has no effect if @p var is not in any list.

    If @p var is not in the list whose head is @p head_pointer,
    it will still unlink itself from the list, without giving any
    indication that the parameters are incorrect.
*/
#define lift_list_unlink_safe(var, head_pointer) ((var) == *(head_pointer)) ? *(head_pointer) = (var)->next : NULL, lift_list_unlink(var)

/** Gives the data of the list element @p var */
#define lift_list_data(var) ((var).data)

/** A helper macro to execute a for-each loop on the list @p var,
    accessing by the iterator/pointer @p it. You have to declare the
    variable @p it.
*/
#define LIFT_LIST_FOR_EACH(it, var)  \
    for (it = &(var); it != NULL; it = lift_list_next(it))

/** A helper macro to search for the value @p val in the list @p var.
    The result will be stored in the iterator/pointer @p rslt, that
    you must provide.
    On success, it will give a safe iterator/position at which the
    given value was found.
    On failure, it will give NULL.

    @note this will only work if the type of the elements that are
    stored in the list is such that its variables can be compared
    using the `==` operator

    @see lift_list_find_if
*/
#define lift_list_find(var, val, rslt)                                  \
    for (rslt = &(var); rslt != NULL; rslt = lift_list_next(rslt)) {    \
        if (rslt->data == (val)) {                                      \
            break;                                                      \
        }                                                               \
    }

/** A helper macro to search for the element position in the list @p var
    that satisfies the @p predicate.
    The result will be stored in the iterator/pointer @p rslt, that
    you must provide.
    On success, it will give a safe iterator/position at which the
    given value was found.
    On failure, it will give NULL.

    The @p predicate is an expression that can operate on pretty much
    anything, but is expected to operate on the @p rslt, which will
    hold the current iterator in the vector. Use like:

        lift_list_find_if(v, iter->data == 55, iter); // list of integers
        lift_list_find_if(v, iter->data->a == 55, iter); // list of structures

    @see lift_list_find
*/
#define lift_list_find_if(var, predicate, rslt)                          \
    for (rslt = &(var); rslt != NULL; rslt = lift_list_next(rslt)) {    \
        if (predicate) {                                                \
            break;                                                      \
        }                                                               \
    }



#endif /* !defined INC_LIFT_LIST */
