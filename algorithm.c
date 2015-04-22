#include "list.h"

void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)) {
	const size_t n = sizeof(lst->elems) / sizeof(*lst->elems);
	size_t i;

	while (lst = lst->next) {
		for (i = 0; i < n; i++) {
			lst->elems[i] = f(lst->elems[i]);
		}
	}
}
