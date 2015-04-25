# Двунаправленный список
Этот проект выполнен в рамках учебного курса "Основы программирования".

## Содержаие
### Типы
```c
typedef ... list_t;
typedef ... lst_elem_t;
typedef ... lst_iter_t;
```

### Интерфейс
```c
int lst_new(list_t* p); // Коля
void lst_free(list_t lst); // Коля
int lst_append(list_t lst, lst_elem_t el); // Вероника
int lst_insert_before(lst_iter_t it, lst_elem_t el); // Дима Т.
void lst_delete(lst_iter_t it); // Ксюша
lst_iter_t lst_iter_by_index(list_t lst, size_t i); // Дима Т.
lst_elem_t lst_index(list_t lst, size_t i); // Дима Т.
void lst_clear(list_t lst); // Ксюша
lst_iter_t lst_iter_next(lst_iter_t t); // Дима Т.
lst_iter_t lst_iter_prev(lst_iter_t t); // Дима Т.
lst_elem_t lst_iter_deref(lst_iter_t t); // Дима Т.
int lst_iter_is_null(lst_iter_t t); // Дима Т.
size_t lst_size(list_t lst); // Дима Р.
```

### Алгоритмы
```c
lst_iter_t lst_binsearch(list_t lst, lst_elem_t val); // Коля (не будем делать)
size_t lst_count(list_t lst, lst_elem_t val); // Бок
list_t lst_copy(list_t lst); // Вероника (сделано)
int lst_compare(list_t lst1, list_t lst2); // Коля
lst_iter_t lst_find(list_t lst, lst_elem_t val); // Дима Т.
void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)); // Коля
lst_elem_t lst_max(list_t lst); // Ксюша (сделано)
lst_elem_t lst_min(list_t lst); // Ксюша (сделано)
void lst_random_shuffle(list_t lst); // Дима Р.
int lst_replace(list_t lst, lst_elem_t from, lst_elem_t to); // Бок (сделано)
int lst_remove(list_t lst, lst_elem_t val); // Бок
void lst_sort(list_t lst); // Дима Р.
void lst_swap(list_t lst1, list_t lst2); // Вероника
```

## Рекомендации по оформлению кода
 * Разделяйте пробелом управляющие конструкции (такие как if/while/for) и скобку. Пробелы между круглыми скобками и их содержимым не ставьте. Открывающая фигурная скобка должна быть в конце строки после закрывающей круглой скобки и пробела. Всегда, когда это возможно, пишите составную инструкцию. Так будет проще модифицировать код, например, добавлять ещё какие-то действия.
```c
if (условие) {
	операторы
} else if (условие) {
	операторы
} else {
	операторы
}
```
 * Однако после имени функции или макроса с параметрами пробел не ставится.
```c
printf("Hello, world!");
```
 * Длина строки в файле с кодом не более 80 символов.
 * В качестве отступов — табуляция, впрочем, вы можете использовать и пробелы, для си это не важно.
 * Имена типов, функций, переменных и пр. пишутся в нижнем регистре, имена макросов-констант — заглавными буквами. Слова разделяются нижним подчёркиванием. Имена, которые попадают в глобальную область видимости, предварять префиксом `lst_`.

## Тесты
### lst_new
<!-- doctest: run -->
```c
list_t L;
if (!lst_new(&L)) {
	/* ошибка при создании списка  */
	abort();
}
/* работаем со списком */
lst_free(L);
```

### lst_free
<!-- doctest: pass -->
```c
list_t L;
if (!lst_new(&L)) {
	/* ошибка при создании списка  */
	abort();
}
/* работаем со списком */
lst_free(L);
```

### lst_append
<!-- doctest: before -->
**Список:** `96 78 84 61 57 30 43 50 71`

<!-- doctest: code -->
```c
lst_append(L, 42);
lst_append(L, 13);
```

<!-- doctest: after -->
**Результат:** `96 78 84 61 57 30 43 50 71 42 13`

### lst_insert_before
<!-- doctest: before -->
**Список:** `28 13 74 2 52 58 68 95 65`

<!-- doctest: code -->
```c
lst_iter_t p = lst_find(L, 68);
lst_insert_before(p, 42);
p = lst_iter_by_index(L, 3);
lst_insert_before(p, 13);
```

<!-- doctest: after -->
**Результат:** `28 13 74 13 2 52 58 42 68 95 65`

### lst_delete
<!-- doctest: before -->
**Список:** `64 54 89 76 52 71 4 23 24 52 94 69 29 22`

<!-- doctest: code -->
```c
lst_delete(lst_find(L, 52));
lst_delete(lst_iter_by_index(L, 2));
lst_delete(lst_iter_by_index(L, 11));
```

<!-- doctest: after -->
**Результат:** `64 54 76 71 4 23 24 52 94 69 29`

### lst_iter_by_index
### lst_index
<!-- doctest: before -->
**Список:** `19 0 69 79 46 23 93 11 31 42 65 90 26 7 89`

<!-- doctest: assert -->
```c
lst_index(L, 6) == 93;
lst_index(L, 11) == 90;
```

### lst_clear
<!-- doctest: pass -->
**Список:** `65 15 44 42 51 4 74 40 75`

<!-- doctest: pass -->
```c
lst_clear(L);
```

<!-- doctest: after -->
**Результат:** ` `

### lst_count
<!-- doctest: before -->
**Список:** `37 13 78 74 13 29 71 6 13 51 90 32 13 95`

<!-- doctest: assert -->
```c
lst_count(L, 13) == 4;
```

### lst_copy
### lst_compare
### lst_find
### lst_for_each
<!-- doctest: pass -->
**Список:** `56 15 69 24 16`

<!-- doctest: pass -->
```c
lst_elem_t func(lst_elem_t l) {
	return l + 1;
}
...
lst_for_each(L, func);
```

<!-- doctest: pass -->
**Результат:** `57 16 70 25 17`

### lst_max
<!-- doctest: before -->
**Список:** `39 53 48 27 17 83 75 15 28`

<!-- doctest: assert -->
```c
lst_max(L) == 83;
```

### lst_min
<!-- doctest: before -->
**Список:** `39 53 48 27 17 83 75 15 28`

<!-- doctest: assert -->
```c
lst_min(L) == 15;
```

### lst_random_shuffle
### lst_replace
<!-- doctest: before -->
**Список:** `35 60 69 4 69 82 42 69 90 32 87 69 76`

<!-- doctest: code -->
```c
lst_replace(L, 69, 42);
```

<!-- doctest: after -->
**Результат:** `35 60 42 4 42 82 42 42 90 32 87 42 76`

### lst_remove
<!-- doctest: pass -->
**Список:** `66 42 56 42 29 1 73 42 97 34 42 63`

<!-- doctest: pass -->
```c
lst_remove(L, 42);
```

<!-- doctest: after -->
**Результат:** `66 56 29 1 73 97 34 63`

### lst_sort
<!-- doctest: pass -->
**Список:** `61 78 91 19 40 11 63 62 42 55 15 35`

<!-- doctest: pass -->
```c
lst_sort(L);
```

<!-- doctest: after -->
**Результат:** `11 15 19 35 40 42 55 61 62 63 78 91`


### lst_size
<!-- doctest: before -->
**Список:** `72 64 62 75 20 15 68 64 74 57 16 24 84 97 43 54 92 26 27`

<!-- doctest: assert -->
```c
lst_size(L) == 19;
```
