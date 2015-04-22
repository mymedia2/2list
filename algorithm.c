#include "list.h"

void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)) {
	size_t i;

	/* итерируемся по списку, пропуская первое звено */
	while (lst = lst->next) {
		for (i = 0; i < lst->count; i++) {
			lst->elems[i] = f(lst->elems[i]);
		}
	}
}
