/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "lift_list.h"

#include <assert.h>


int main()
{
    typedef LIFT_DECL_LIST(int) listint_t;

    listint_t l;
    listint_t l_2;
    listint_t l_tr;
    listint_t *lhead;
    int data;

    LIFT_LIST_INIT(l);
    LIFT_LIST_INIT(l_2);
    LIFT_LIST_INIT(l_tr);

    assert(!lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(!lift_list_has_previous(&l_2));
    assert(!lift_list_has_next(&l_tr));
    assert(!lift_list_has_previous(&l_tr));

    lift_list_data(l) = 1;
    lift_list_data(l_2) = 2;
    lift_list_data(l_tr) = 3;
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(lift_list_data(l_tr) == 3);

    lift_list_link_before(&l_2, &l);
    assert(!lift_list_has_next(&l));
    assert(lift_list_has_previous(&l));
    assert(lift_list_has_next(&l_2));
    assert(!lift_list_has_previous(&l_2));
    assert(lift_list_next(&l_2) == &l);
    assert(lift_list_previous(&l) == &l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);

    lift_list_unlink(&l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(!lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(!lift_list_has_previous(&l_2));

    lift_list_link_after(&l_2, &l);
    assert(lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(lift_list_has_previous(&l_2));
    assert(lift_list_previous(&l_2) == &l);
    assert(lift_list_next(&l) == &l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);

    lift_list_unlink(&l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(!lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(!lift_list_has_previous(&l_2));

    lhead = &l;
    lift_list_link_after(&l_2, &l);
    lift_list_unlink_safe(&l, &lhead);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(!lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(!lift_list_has_previous(&l_2));
    assert(lhead == &l_2);

    LIFT_LIST_FOR_EACH(lhead, l) {
        assert(lift_list_data(*lhead) == 1);
    }
    lift_list_find(l, 1, lhead);
    assert(lhead == &l);
    lift_list_find(l, 2, lhead);
    assert(lhead == NULL);
    lift_list_find_if(l, lift_list_data(*lhead) == 1, lhead);
    assert(lhead == &l);
    lift_list_find_if(l, lift_list_data(*lhead) == 2, lhead);
    assert(lhead == NULL);

    lift_list_link_after(&l_2, &l);
    data = 1;
    LIFT_LIST_FOR_EACH(lhead, l) {
        assert(lift_list_data(*lhead) == data);
        if (1 == data) {
            data = 2;
        }
    }
    lift_list_find(l, 1, lhead);
    assert(lhead == &l);
    lift_list_find(l, 2, lhead);
    assert(lhead == &l_2);
    lift_list_find(l, 3, lhead);
    assert(lhead == NULL);
    lift_list_find(l_2, 1, lhead);
    assert(lhead == NULL);
    lift_list_find(l_2, 2, lhead);
    assert(lhead == &l_2);
    lift_list_find(l_2, 3, lhead);
    assert(lhead == NULL);
    lift_list_find_if(l, lift_list_data(*lhead) == 1, lhead);
    assert(lhead == &l);
    lift_list_find_if(l, lift_list_data(*lhead) == 2, lhead);
    assert(lhead == &l_2);
    lift_list_find_if(l, lift_list_data(*lhead) == 3, lhead);
    assert(lhead == NULL);
    lift_list_find_if(l_2, lift_list_data(*lhead) == 1, lhead);
    assert(lhead == NULL);
    lift_list_find_if(l_2, lift_list_data(*lhead) == 2, lhead);
    assert(lhead == &l_2);
    lift_list_find_if(l_2, lift_list_data(*lhead) == 3, lhead);
    assert(lhead == NULL);

    lift_list_link_after(&l_tr, &l);
    assert(lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(lift_list_has_previous(&l_2));
    assert(lift_list_has_next(&l_tr));
    assert(lift_list_has_previous(&l_tr));
    assert(lift_list_previous(&l_tr) == &l);
    assert(lift_list_next(&l) == &l_tr);
    assert(lift_list_previous(&l_2) == &l_tr);
    assert(lift_list_next(&l_tr) == &l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(lift_list_data(l_tr) == 3);

    data = 1;
    LIFT_LIST_FOR_EACH(lhead, l) {
        assert(lift_list_data(*lhead) == data);
        if (1 == data) {
            data = 3;
        }
        else if (3 == data) {
            data = 2;
        }
    }

    lift_list_unlink(&l_tr);
    assert(lift_list_has_next(&l));
    assert(!lift_list_has_previous(&l));
    assert(!lift_list_has_next(&l_2));
    assert(lift_list_has_previous(&l_2));
    assert(!lift_list_has_next(&l_tr));
    assert(!lift_list_has_previous(&l_tr));
    assert(lift_list_previous(&l_2) == &l);
    assert(lift_list_next(&l) == &l_2);
    assert(lift_list_data(l) == 1);
    assert(lift_list_data(l_2) == 2);
    assert(lift_list_data(l_tr) == 3);

    return 0;
}
