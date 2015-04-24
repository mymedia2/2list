#include <stdio.h>
#include "list.h"

int main() {
	list_t L, T;
	int i;
	lst_elem_t v = 24;

	lst_new(&L);
	for (i = 0; i < 13; i++) {
		lst_append(L, 42);
		lst_append(L, 13);
	}
	printf("%zd\n", lst_size(L));
	lst_replace(L, 42, 24); 
	lst_iter_t p;
	for (p = lst_iter_first(L); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		printf("%ld ", lst_iter_deref(p));
	}
	printf("\n");
	T = lst_copy(L);
	for (p = lst_iter_first(T); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		printf("%ld ", lst_iter_deref(p));
	}
	printf("\n");
	printf ("Элемент %zd встречается в списке L %zd раз\n", v, lst_count(L, 24));
	lst_free(T);
	lst_free(L);

	return 0;
}
