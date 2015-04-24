#include <stdio.h>
#include "list.h"

int main() {
	list_t L;
	int i;

	lst_new(&L);
	for (i = 0; i < 13; i++) {
		lst_append(&L, i);
		lst_append(&L, 42);
		lst_append(&L, 13);
	}
//	printf("%zd\n", lst_size(&L));

	lst_iter_t p;
	for (p = lst_iter_first(&L); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		printf("%ld ", lst_iter_deref(p));
	}
	printf("\n");

	for (i = 5; i < 30; i += 4) {
		printf("%ld ", lst_index(&L, i));
	}
	printf("\n");

	lst_free(&L);

	return 0;
}
