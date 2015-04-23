#include <stdio.h>
#include "list.h"

int main() {
	list_t L;

	lst_new(&L);
	lst_append(L, 1);
	lst_append(L, 2);
	lst_append(L, 42);
	lst_append(L, 13);
	lst_free(L);

	return 0;
}
