#include <stdlib.h>

#include "list.h"

int lst_new(list_t* p) {
    struct lst_node_* tmp;

    tmp = malloc(sizeof(*tmp));
    if (!tmp) {
        /* не удалось выделить память — ошибка */
        return 0;
    }
    
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->count = 0;
    *p = tmp;
    return 1;
}

void lst_free(list_t lst) {
    lst_clear(lst);
    free(lst);
}

lst_iter_t lst_iter_by_index(list_t lst, size_t i) {
    lst_iter_t t;
    size_t j;
    const size_t size = sizeof(lst->elems) / sizeof(*lst->elems);

    for (j = size; j < i; j += size) {
        lst = lst->next;
    }
    t.box = lst;
    t.offset = i % size;

    return t;
}

lst_elem_t lst_iter_deref(lst_iter_t t) {
    return t.box->elems[t.offset];
}

lst_elem_t lst_index(list_t lst, size_t i) {
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

int lst_append(list_t lst, lst_elem_t el) {
	list_t* p;
	while (lst->next) lst=lst->next;
	if (lst->count < sizeof(lst->elems)/sizeof(*(lst->elems))) {
		lst->elems[lst->count++] = el;
	} else {
		if (lst_new(p)) {
			(*p)->elems[0] = el;
			(*p)->count = 1;
			lst->next = *p;
			(*p)->prev = lst;
		} else return 0;
	}
	return 1;
}
