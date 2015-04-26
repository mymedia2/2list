#include <stdio.h>
#include "list.h"

int main() {
	list_t* L;
	list_t* T;
	lst_iter_t p;
	int i;

	L = lst_new(0);
	for (i = 0; i < 13; i++) {
		lst_append(L, i);
		lst_append(L, 42);
		lst_append(L, 13);
	}

	printf("L = { ");
	for (p = lst_iter_first(L); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		printf("%ld, ", lst_iter_deref(p));
	}
	printf("}\n");

	printf("lst_size(L) == %zd\n", lst_size(L));

	for (i = 5; i < 30; i += 4) {
		printf("L[%d] == %ld\n", i, lst_index(L, i));
	}

	T = lst_copy(L);
	lst_free(L);

	printf("T = { ");
	for (p = lst_iter_first(T); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		printf("%ld, ", lst_iter_deref(p));
	}
	printf("}\n");

	printf("max == %ld, min == %ld\n", lst_max(T), lst_min(T));

	lst_free(T);

	return 0;
}
