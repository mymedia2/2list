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
