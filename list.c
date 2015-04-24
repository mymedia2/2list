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

void lst_clear(list_t lst) {
    struct lst_node_* t, *p;
    t = lst;
    /* Удаляем элементы в первой ноде */
    t->count = 0;
    /* Удаляем весь остальной список*/
    t = t->next;
    while(t != NULL) {
        p = t;
        t = t->next;
        free(p);
    }
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

size_t lst_size(list_t lst) {
    list_t counter_lst = lst;
    size_t counter = 0;
    while ((counter_lst->next) != NULL) {
        counter_lst = counter_lst->next;
        counter++; //Считаем кол-во объектов с списке
    }

    counter *= 10; ///У нас 10 элементов в объекте, так что считаем число counter*10;
    counter += counter_lst->count; //Элементы в последнем звене;
    return counter;
}

int lst_append(list_t lst, lst_elem_t el) {
    list_t p;
    if (lst->count == 0) {
        lst->elems[lst->count++] = el;
        
    } else {
        
        while (lst->next) lst=lst->next;
        if (lst->count < sizeof(lst->elems) / sizeof(*lst->elems)) {
            lst->elems[lst->count++] = el;
        } else {
        /*Здесь функция lst_new(p) создает не список, а звено*/
            if (lst_new(&p)) {
                p->elems[0] = el;
                p->count = 1;
                lst->next = p;
                p->prev = lst;
            } else return 0;
        }
    }
    return 1;
}

list_t lst_copy(list_t lst) {
    list_t* p;
    if (lst_new(p)) {
        lst_iter_t it = lst_iter_by_index(lst, 0);
        for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
            lst_append(*p, lst_iter_deref(it));
        }
        return *p;
    } else return NULL;
}

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_max(list_t lst) {
    lst_elem_t max;
    lst_iter_t it = lst_iter_by_index(lst, 0);
    max = lst_iter_deref(it);

    for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
        if (max < lst_iter_deref(it)) max = lst_iter_deref(it);
    }
    return max;
}

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_min(list_t lst) {
    lst_elem_t min;
    lst_iter_t it = lst_iter_by_index(lst, 0);
    min = lst_iter_deref(it);

    for (; !lst_iter_is_null(it); it = lst_iter_next(it) ) {
        if (lst_iter_deref(it) < min) min = lst_iter_deref(it);
    }
    return min;
}

lst_iter_t lst_iter_first(list_t lst) {
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
            it.box->elems[m] = it.box->elems[++m];
        }
        (it.box->count)--;
    }
}

void lst_swap_d(list_t lst, int first, int second) { //Подаются номера элементов
    int boost, firstD = (first - 1) / 10.0, secondD = (second - 1) / 10.0;
    list_t firstP = lst, secondP = lst;
    
    while (firstD-- > 0) { //Находим ссылку на звено первого элемента
        firstP = firstP->next;
    }
    
    while (secondD-- > 0) { //Находим ссылку на звено второго элемента
        secondP = secondP->next;
    }
    
    firstD = first % 10; //для экономии используем те же переменные для нахождения элемента в звене
    secondD = second % 10;
    
    boost = secondP->elems[secondD]; //меняем местами
    boost = secondP->elems[secondD]; //меняем местами
    secondP->elems[secondD] = firstP->elems[firstD];
    firstP->elems[firstD] = boost;
}    
   
