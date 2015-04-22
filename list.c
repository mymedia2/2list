#include "list.h"

lst_iter_t lst_iter_by_index(list_t lst, size_t i) {
    lst_iter_t t;
    size_t j;
    for (j = 10; j < i; j += 10) { 
        lst = lst->next;
    }
    t.box = lst;
    t.offset = i % 10;
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
    l.box = t.box->next;
    l.offset = 0;
    return l;
}

lst_iter_t prev(lst_iter_t t) {
    lst_iter_t l;
    l.box = t.box->prev;
    l.offset = 0;
    return l;
}
