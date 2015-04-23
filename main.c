#include <stdio.h>
#include "list.h"

int main() {
	list_t L;
	int i;

	lst_new(&L);
	for (i = 0; i < 1000; i++) {
		lst_append(L, 42);
		lst_append(L, 13);
	}
	printf("%d\n", (int)lst_size(L));

	lst_free(L);

	return 0;
}
