#include "list.h"

lst_iter_t lst_find(list_t lst, lst_elem_t val) {
    lst_iter_t t = lst_iter_by_index(lst, 0);
    size_t i;
    for (; t.box->next != NULL; t = next(t) ) {
        for (i = 0; i < t.box->count; ++i) {
            if( t.box->elems[i] == val ) {
                t.offset = i;
                return t;
            }
        }
    }
    /* Не нашли - возвращаем итератор на последний элемент */
    t.offset = t.box->count;
    return t;
}

void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)) {
    const size_t n = sizeof(lst->elems) / sizeof(*lst->elems);
    size_t i;

    while (lst = lst->next) {
        for (i = 0; i < n; i++) {
            lst->elems[i] = f(lst->elems[i]);
        }
    }
}
