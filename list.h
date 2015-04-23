#ifndef LST_LIST_H
#define LST_LIST_H

#include <stddef.h>

/*  Тип элементов в списке.

    Пользователь библиотеки может определить какой тип элементов будет в
    списке. Для этого нужно перед включенимем этого заголовочного файла
    определить макрос LST_MY_ELEM_T и тип lst_elem_t, а также перекомпилировать
    реализацию всех функций.

    Если пользователь не определит макрос перед включением заголовка, то по
    умолчанию будет использоваться long.
*/
#ifndef LST_MY_ELEM_T
    typedef long lst_elem_t;
#endif

/*  Звено двунаправленного списка с заглавным звеном.

    Содержит как сам элемент, так и указатели на предыдущее и следующее звенья.
    В инициализированном списке всегда находится одно первое звено, которое не
    меняет своего места. Все операции происходять после него. Поле elem у этого
    звена не используется.
*/
struct lst_node_ {
    lst_elem_t elems[10];
    size_t count;
    struct lst_node_* prev;
    struct lst_node_* next;
};

/*  Список.

    Тип предназначен для унификации пользовательского интерфейса библиотеки.
*/
typedef struct lst_node_* list_t;

/*  Итератор. Указывает на очередной элемент списка или на элемент, следующий
    за последним.

    Данный итератор является двунаправленным итератором чтения/записи. Это
    означает, что элемент, на который указывает итератор, можно прочитать,
    изменить, а также можно перейти к следующему и предыдущему элементу.
*/
typedef struct {
    /* указатель на звено */
    struct lst_node_* box;
    /* Номер элемента */
    size_t offset;  
} lst_iter_t;

/*  Создаёт и инициализирует список, на который указывает p.

    В случае успеха возвращает ненулевое значение, иначе 0.
*/
int lst_new(list_t* p);

/* Уничтожает список lst и освобождает память. */
void lst_free(list_t lst);

/*  Вставляет элемент el в конец списка lst.

    В случае успеха возвращает ненулевое значение, иначе 0.
*/
int lst_append(list_t lst, lst_elem_t el);

/*  Вставляет элемент el перед тем, на который указывает it.

    В случае успеха возвращает ненулевое значение, иначе 0.
*/
int lst_insert_before(lst_iter_t it, lst_elem_t el);

/* Удаляет элемент, на который указывает it. */
void lst_delete(lst_iter_t it);

/* Возвращает итератор, указывающий на i-тый элемент списка lst. */
lst_iter_t lst_iter_by_index(list_t lst, size_t i);

/* Возвращает i-тый элемент списка lst. */
lst_elem_t lst_index(list_t lst, size_t i);

/* Очищает список lst. */
void lst_clear(list_t lst);

/*  Выполняет бинарный поиск значения val в списке lst.

    Возвращает итератор, указывающий на найденный элемент. Список должен быть
    отсортирован.
*/
lst_iter_t lst_binsearch(list_t lst, lst_elem_t val);

/* Возвращает количесво элементов со значением val в списке lst. */
size_t lst_count(list_t lst, lst_elem_t val);

/* Возвращает копию списка lst. */
list_t lst_copy(list_t lst);

/*  Сравнивает два списка lst1 и lst2.

    Возвращает значение больше нуля, если lst1 "больше" lst2, равное нулю, если
    lst1 и lst2 "равны" и меньше нуля, если lst1 "меньше" lst2.
*/
int lst_compare(list_t lst1, list_t lst2);

/* Возвращает итератор, указывающий на первое вхождение значения val в список lst. */
lst_iter_t lst_find(list_t lst, lst_elem_t val);

/*  Вызывает функцию f для всех элементов списка lst.

    Значение, которое возвращает f, кладётся на место того элемента. */
void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t));

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_max(list_t lst);

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_min(list_t lst);

/* Случайным образов переставляет элементы в списке lst. */
void lst_random_shuffle(list_t lst);

/* Заменяет в списке lst все вхождения элемента from на to. */
int lst_replace(list_t lst, lst_elem_t from, lst_elem_t to);

/* Удаляет из списка lst все вхождения элемента val. */
int lst_remove(list_t lst, lst_elem_t val);

/* Сортирует список lst. */
void lst_sort(list_t lst);

/* Обменивает два списка lst1 и lst2 за константное время. */
void lst_swap(list_t lst1, list_t lst2);

/* Переходит на следующий элемент */
lst_iter_t lst_iter_next(lst_iter_t t);

/* Переходит на предыдущий элемент */
lst_iter_t lst_iter_prev(lst_iter_t t); 

/* Возвращает элемент, на который указывает итератор */
lst_elem_t lst_iter_deref(lst_iter_t t);

/* Проверяет на NULL box итератора */
int lst_iter_is_null( lst_iter_t t );

#endif  /* LST_LIST_H */
