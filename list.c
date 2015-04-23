#include <stdlib.h>

#include "list.h"

int lst_new(list_t* p) {
    struct lst_node_* tmp;

    tmp = malloc(sizeof(*tmp));
    if (!tmp) {
        /* не удалось выделить память — ошибка */
        return 0;
    }

    *p = tmp;
    return 1;
}

void lst_free(list_t lst) {
    lst_clear(lst);
    free(lst);
}

lst_iter_t lst_iter_by_index(list_t lst, size_t i) {
    lst_iter_t t;
    size_t j;
    const size_t size = sizeof(lst->elems) / sizeof(*lst->elems);

    for (j = size; j < i; j += size) {
        lst = lst->next;
    }
    t.box = lst;
    t.offset = i % size;

    return t;
}

lst_elem_t lst_iter_deref(lst_iter_t t) {
    return t.box->elems[t.offset];
}

lst_elem_t lst_index(list_t lst, size_t i) {
    return lst_iter_deref(lst_iter_by_index(lst, i));
}

lst_iter_t next(lst_iter_t t) {
    lst_iter_t l;
    l.offset = (t.offset + 1) % t.box->count;
    if(l.offset == 0) l.box = t.box->next;
    else l.box = t.box;
    return l;
}

lst_iter_t prev(lst_iter_t t) {
    lst_iter_t l;
    if( t.offset != 0 ) {
        l.offset = t.offset - 1;
        l.box = t.box;
    } else {
        l.box = t.box->prev;
        l.offset = l.box->count;
    }
    return l;
}
