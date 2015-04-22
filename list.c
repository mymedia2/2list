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
