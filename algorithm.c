#include "list.h"

lst_iter_t lst_find(list_t* lst, lst_elem_t val) {
    lst_iter_t it = lst_iter_first(lst);
    for (; !lst_iter_is_null(it); it = lst_iter_next(it)) {
		if (lst_iter_deref(it) == val) {
			return it;
		}
    }
    /* Не нашли - возвращаем нулевой итератор */
	it.box == NULL;
    return it;
}

#if 0
void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)) {
    size_t i;

    /* итерируемся по списку, пропуская первое звено */
    while (lst = lst->next) {
        for (i = 0; i < lst->count; i++) {
            lst->elems[i] = f(lst->elems[i]);
        }
    }
}
#endif
