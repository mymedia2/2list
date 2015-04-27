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

/*	Звено двунаправленного развёрнутого списка списка.

	Содержит как сами элементы, так и указатели на предыдущее и следующее звенья.
	В инициализированном списке всегда находится одно первое звено, которое не
	меняет своего места.
*/
struct lst_node_ {
	/* Указатель на предыдущее звено или NULL, если данное звено первое. */
	struct lst_node_* prev;
	/* Указатель на следующее звено или NULL, если данное звено последнее. */
	struct lst_node_* next;
	/*	Количество валидных элементов в звене, относящихся к списку. К списку
		относятся только count первых элементов из массива elems.
	*/
	size_t count;
	/* Элементы звена. */
	lst_elem_t elems[10];
};

/*  Список.

    Тип предназначен для унификации пользовательского интерфейса библиотеки.
	Содержит указатели на первое и последнее звено.
*/
typedef struct {
	/*	Указатель на первое звено. Если список инициализирован (для него была
		вызвана lst_new, но не было lst_free), то оба этих указателя
		действительны и их можно разыменовывать. Если список пуст, то оба
		указателя содержат адрес одного и того же звена, в котором поле count
		равно 0.
	*/
	struct lst_node_* begin;
	/* Указатель на последнее звено. См. требования выше. */
	struct lst_node_* end;
	/*	Флаги списка. В зависимости от значения некоторых битов, могут
		использоваться различные алгоритмы для работы со списком. */
	int flags;
} list_t;

/*  Итератор. Указывает на очередной элемент списка или на элемент, следующий
    за последним.

    Данный итератор является двунаправленным итератором чтения/записи. Это
    означает, что элемент, на который указывает итератор, можно прочитать,
    изменить, а также можно перейти к следующему и предыдущему элементу.
*/
typedef struct {
	/* Указатель на звено. */
	struct lst_node_* box;
	/* Номер элемента в звене. */
	size_t offset;
} lst_iter_t;

list_t* lst_new(int flags);
void lst_free(list_t* lst);
int lst_append(list_t* lst, lst_elem_t el);
int lst_insert_before(lst_iter_t it, lst_elem_t el);
void lst_delete(lst_iter_t it);
void lst_clear(list_t* lst);

/* Возвращает итератор, указывающий на i-тый элемент списка lst. */
lst_iter_t lst_iter_by_index(list_t* lst, size_t i);

/* Возвращает i-тый элемент списка lst. */
lst_elem_t lst_index(list_t* lst, size_t i);

/* Возвращает количесво элементов со значением val в списке lst. */
size_t lst_count(list_t* lst, lst_elem_t val);

/* Возвращает копию списка lst, если не удалось скопировать, то возращает NULL*/
list_t* lst_copy(list_t* lst);

/*  Сравнивает два списка lst1 и lst2.

    Возвращает значение больше нуля, если lst1 "больше" lst2, равное нулю, если
    lst1 и lst2 "равны" и меньше нуля, если lst1 "меньше" lst2.
*/
int lst_compare(list_t lst1, list_t lst2);

/*	Возвращает итератор, указывающий на первое вхождение значения val в
	список lst, или нулевой итератор, если значение не найдено. */
lst_iter_t lst_find(list_t* lst, lst_elem_t val);

/*  Вызывает функцию f для всех элементов списка lst.

	Значение, которое возвращает f, кладётся на место того элемента.
*/
void lst_for_each(list_t* lst, lst_elem_t (*f)(lst_elem_t));

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_max(list_t* lst);

/* Возвращает наибольший элемент непустого списка lst. */
lst_elem_t lst_min(list_t* lst);

/* Случайным образов переставляет элементы в списке lst. */
void lst_random_shuffle(list_t lst);

/* Заменяет в списке lst все вхождения элемента from на to. */
int lst_replace(list_t* lst, lst_elem_t from, lst_elem_t to);

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

/*	Возвращает итератор, указывающий на первый элемент списка lst, или нулевой,
	если список пуст.
*/
lst_iter_t lst_iter_first(list_t* lst);

/*	Возвращает итератор, указывающий на последний элемент списка lst, или
	нулевой, если список пуст.
*/
lst_iter_t lst_iter_last(list_t* lst);

/* Возвращает элемент, на который указывает итератор */
lst_elem_t lst_iter_deref(lst_iter_t t);

/* Проверяет на NULL box итератора */
int lst_iter_is_null(lst_iter_t t);

/* Возвращает количество элементов в списке lst. */
size_t lst_size(list_t* lst);

#endif  /* LST_LIST_H */
