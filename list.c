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
