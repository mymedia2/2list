#include <assert.h>
#include <stdlib.h>

#include "list.h"

list_t* lst_new(int arg_flags) {
	list_t* list;
	struct lst_node_* node;

	/* создаём список и его первое звено */
	list = malloc(sizeof(*list));
	if (!list) {
		/* не удалось выделить память — ошибка */
		return NULL;
	}
	node = malloc(sizeof(*node));
	if (!node) {
		/*	не удалось выделить память — ошибка,
			нужно освободить уже выделенную память для списка */
		free(list);
		return NULL;
	}

	/*	проставление ссылок в структуре list_t
		и инициализация первого звена */
	list->begin = list->end = node;
	list->flags = arg_flags;
	node->count = 0;
	node->next = node->prev = NULL;

	return list;
}

void lst_free(list_t* lst) {
	lst_clear(lst);
	/*	в данной реализации подразумевается, что в пустом списке всегда
		есть одно звено, в котором поле count равно 0 */
	assert(lst->begin == lst->end);
	free(lst->begin);
}

void lst_clear(list_t* lst) {
	struct lst_node_* tmp;
	struct lst_node_* ptr;

	/* удаляем элементы в первом звене */
	lst->begin->count = 0;

	/* удаляем весь остальной список */
	tmp = lst->begin->next;
	while (tmp) {
		ptr = tmp;
		tmp = tmp->next;
		free(ptr);
	}

	/* синхронизируем указатели в списке */
	lst->end = lst->begin;
}

int lst_append(list_t* list, lst_elem_t el) {
	struct lst_node_* const last_node = list->end;
	const size_t n = sizeof(last_node->elems) / sizeof(*last_node->elems);

	if (last_node->count < n) {
		/* в последнем звене ещё есть место — вставляем элемент туда */
		last_node->elems[last_node->count++] = el;
	} else {
		/* последнее звено полностью заполнено — создаём новое */
		struct lst_node_* tmp;

		tmp = malloc(sizeof(*tmp));
		if (!tmp) {
			/* не удалось выделить память — ошибка */
			return 0;
		}

		/* инициализируем вновь созданное звено */
		tmp->elems[0] = el;
		tmp->count = 1;
		tmp->prev = last_node;
		tmp->next = NULL;

		/* прицепляем новое звено к списку */
		last_node->next = list->end = tmp;
	}

	return 1;
}

lst_iter_t lst_iter_by_index(list_t* list, size_t index) {
	lst_iter_t it;
	struct lst_node_* curr = list->begin;

	while (index >= curr->count) {
		index -= curr->count;
		curr = curr->next;
	}

	it.box = curr;
	it.offset = index;

	return it;
}

lst_elem_t lst_iter_deref(lst_iter_t t) {
    return t.box->elems[t.offset];
}

lst_elem_t lst_index(list_t* lst, size_t i) {
    return lst_iter_deref(lst_iter_by_index(lst, i));
}

lst_iter_t lst_iter_next(lst_iter_t t) {
    lst_iter_t l;
    l.offset = (t.offset + 1) % t.box->count;
    if (l.offset == 0) l.box = t.box->next;
    else l.box = t.box;
    return l;
}

lst_iter_t lst_iter_prev(lst_iter_t t) {
    lst_iter_t l;
    if (t.offset != 0) {
        l.offset = t.offset - 1;
        l.box = t.box;
    } else {
        l.box = t.box->prev;
        l.offset = l.box->count;
    }
    return l;
}

int lst_iter_is_null( lst_iter_t t ) {
    return t.box == NULL;
}

#if zero
int lst_insert_before(lst_iter_t it, lst_elem_t el) {
    const size_t n = sizeof(it.box->elems) / sizeof(lst_elem_t); 
    if (it.box->count < n && it.offset != 0) {
        /* массив не заполнен, сдвигаем другие элементы */
        int i;
        for (i = (it.box->count)++; i >= it.offset; --i) {
            it.box->elems[i] = it.box->elems[i-1];
        }
        it.box->elems[it.offset] = el;
    } else if(it.box->prev && it.box->prev->count < n){
        /* массив в предыдущем звене не заполнен */
        it.box->prev->elems[(it.box->prev->count)++] = el;
    } else {
        /* добавление нового звена */
        /* TODO сделать, чтобы это не была копипаста из lst_new */
        struct lst_node_* tmp;

        tmp = malloc(sizeof(*tmp));
        if (!tmp) {
            /* не удалось выделить память — ошибка */
            return 0;
        }
        
        tmp->count = 0;
        tmp->elems[tmp->count] = el;
        tmp->prev = it.box->prev;
        tmp->next = it.box;
        it.box->prev = tmp;
    }
}
#endif // zero

size_t lst_size(list_t* lst) {
	lst_iter_t p;
	size_t counter = 0;

	for (p = lst_iter_first(lst); !lst_iter_is_null(p); p = lst_iter_next(p)) {
		counter++;
	}

	return counter;
}

list_t* lst_copy(list_t* lst) {
	list_t* p;

	if (p = lst_new(0)) {
		lst_iter_t it = lst_iter_by_index(lst, 0);
		for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
			lst_append(p, lst_iter_deref(it));
		}
	}
	return p;
}

int lst_replace(list_t* lst, lst_elem_t from, lst_elem_t to) {
	lst_iter_t it = lst_iter_by_index(lst, 0);
	for (; !lst_iter_is_null(it); it = lst_iter_next(it)) {
		if (lst_iter_deref(it) == from) { 
			it.box->elems[it.offset] = to;
		}
	}
	return 0;
}

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_max(list_t* lst) {
	lst_elem_t max;
	lst_iter_t it = lst_iter_by_index(lst, 0);
	max = lst_iter_deref(it);

	for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
		if (max < lst_iter_deref(it)) max = lst_iter_deref(it);
	}
	return max;
}

/* Возвращает наименьший элемент непустого списка lst. */
lst_elem_t lst_min(list_t* lst) {
	lst_elem_t min;
	lst_iter_t it = lst_iter_by_index(lst, 0);
	min = lst_iter_deref(it);

	for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
		if (lst_iter_deref(it) < min) min = lst_iter_deref(it);
	}
	return min;
}

lst_iter_t lst_iter_first(list_t* lst) {
	return lst_iter_by_index(lst, 0);
}

void lst_delete(lst_iter_t it) {
	size_t k, m;
	k = it.box->count;
	if (k == 1) {
		struct lst_node_ *t;
		t = it.box;
		t->next = it.box->next;
		t = it.box->next;
		t->prev = it.box->prev;
		t = it.box;
		free (t);
	} else {
		m = it.offset;
		while (m < k) {
			it.box->elems[m] = it.box->elems[m+1];
			m++;
		}
		it.box->count--;
	}
}

size_t lst_count(list_t* lst, lst_elem_t val) {
	lst_iter_t it = lst_iter_first(lst);
	size_t kol = 0;
	for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
		if (lst_iter_deref(it) == val) {
			kol = kol + 1;
		}
	}
	return kol;
}
