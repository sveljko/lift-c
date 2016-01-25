/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
#include "lift_vec.h"

#include <assert.h>


int main()
{
    size_t idx;
    typedef LIFT_DECL_VEC(int) vecint_t;

    vecint_t v;
    int *iter;
    LIFT_VEC_INIT(v);

    assert(!LIFT_VEC_VALID(v));
    assert(lift_vec_size(v) == 0);
    assert(lift_vec_empty(v));
    assert(lift_vec_begin(v) == lift_vec_end(v));

    LIFT_PRINTF(v);
    lift_vec_push_back(v,3);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 0));
    assert(lift_vec_size(v) == 1);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 1 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(3 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));

    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert(idx == 0);
    }
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert(*iter == 3);
    }

    lift_vec_push_back(v,4);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 1));
    assert(lift_vec_size(v) == 2);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 2 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(4 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(4 == lift_vec_get(v, 1));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert((idx == 0) || (idx == 1));
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert((idx == 0) || (idx == 1));
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 4); break;
        }
        ++idx;
    }

    lift_vec_push_back(v,5);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 2));
    assert(lift_vec_size(v) == 3);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 3 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(5 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(4 == lift_vec_get(v, 1));
    assert(5 == lift_vec_get(v, 2));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 4); break;
        case 2: assert(*iter == 5); break;
        }
        ++idx;
    }

    lift_vec_pop_back(v);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 1));
    assert(lift_vec_size(v) == 2);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 2 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(4 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(4 == lift_vec_get(v, 1));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert((idx == 0) || (idx == 1));
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert((idx == 0) || (idx == 1));
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 4); break;
        }
        ++idx;
    }

    lift_vec_push_back(v,6);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 2));
    assert(lift_vec_size(v) == 3);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 3 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(6 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(4 == lift_vec_get(v, 1));
    assert(6 == lift_vec_get(v, 2));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 4); break;
        case 2: assert(*iter == 6); break;
        }
        ++idx;
    }

    lift_vec_insert(v, lift_vec_begin(v) + 2, 5);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 3));
    assert(lift_vec_size(v) == 4);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 4 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(6 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(4 == lift_vec_get(v, 1));
    assert(5 == lift_vec_get(v, 2));
    assert(6 == lift_vec_get(v, 3));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert(idx <= 3);
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert(idx <= 3);
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 4); break;
        case 2: assert(*iter == 5); break;
        case 3: assert(*iter == 6); break;
        }
        ++idx;
    }

    lift_vec_erase(v, lift_vec_begin(v)+1);
    LIFT_PRINTF(v);
    assert(LIFT_VEC_VALID(v));
    assert(LIFT_VEC_SAFE(v, 2));
    assert(lift_vec_size(v) == 3);
    assert(!lift_vec_empty(v));
    assert(lift_vec_begin(v) + 3 == lift_vec_end(v));
    assert(3 == *lift_vec_begin(v));
    assert(3 == lift_vec_front_get(v));
    assert(6 == lift_vec_back_get(v));
    assert(3 == lift_vec_get(v, 0));
    assert(5 == lift_vec_get(v, 1));
    assert(6 == lift_vec_get(v, 2));
    LIFT_VEC_FOR_EACH_IDX(idx, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
    }
    idx = 0;
    LIFT_VEC_FOR_EACH_ITER(iter, v) {
        assert((idx == 0) || (idx == 1) || (idx == 2));
        switch (idx) {
        case 0: assert(*iter == 3); break;
        case 1: assert(*iter == 5); break;
        case 2: assert(*iter == 6); break;
        }
        ++idx;
    }

    lift_vec_find(v, 5, iter);
    assert(iter == lift_vec_begin(v) + 1);
    assert(*iter == 5);
    lift_vec_find(v, 3, iter);
    assert(iter == lift_vec_begin(v));
    assert(*iter == 3);
    lift_vec_find(v, 6, iter);
    assert(iter == lift_vec_begin(v) + 2);
    assert(*iter == 6);
    lift_vec_find(v, 555, iter);
    assert(iter == lift_vec_end(v));

    lift_vec_find_if(v, *iter == 5, iter);
    assert(iter == lift_vec_begin(v) + 1);
    assert(*iter == 5);
    lift_vec_find_if(v, *iter == 555, iter);
    assert(iter == lift_vec_end(v));

    lift_vec_pop_back(v);
    lift_vec_pop_back(v);
    lift_vec_pop_back(v);
    assert(LIFT_VEC_VALID(v));
    assert(lift_vec_size(v) == 0);
    assert(lift_vec_empty(v));
    assert(lift_vec_begin(v) == lift_vec_end(v));

    lift_vec_free(v);
    assert(!LIFT_VEC_VALID(v));
    LIFT_PRINTF(v);

    return 0;
}
