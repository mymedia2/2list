# Двунаправленный список
Этот проект выполнен в рамках учебного курса "Основы программирования".

## Содержаие
### Список типов
```c
typedef ... list_t;
typedef ... lst_elem_t;
typedef ... lst_iter_t;
```

### Список функций
```c
int lst_new(list_t* p); // Коля
void lst_free(list_t lst); // Коля
int lst_append(list_t lst, lst_elem_t el); // Вероника
int lst_insert_before(lst_iter_t it, lst_elem_t el); // Дима Т.
void lst_delete(lst_iter_t it); // Ксюша
lst_iter_t lst_iter_by_index(list_t lst, size_t i); // Дима Т.
lst_elem_t lst_index(list_t lst, size_t i); // Дима Т.
void lst_clear(list_t lst); // Ксюша
```

### Список алгоритмов
```c
lst_iter_t lst_binsearch(list_t lst, lst_elem_t val); // Коля
size_t lst_count(list_t lst, lst_elem_t val); // Бок
list_t lst_copy(list_t lst); // Вероника
int lst_compare(list_t lst1, list_t lst2); // Коля
lst_iter_t lst_find(list_t lst, lst_elem_t val); // Дима Т.
void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t)); // Коля
lst_elem_t lst_max(list_t lst); // Ксюша
lst_elem_t lst_min(list_t lst); // Ксюша
void lst_random_shuffle(list_t lst); // Дима Р.
int lst_replace(list_t lst, lst_elem_t from, lst_elem_t to); // Бок
int lst_remove(list_t lst, lst_elem_t val); // Бок
void lst_sort(list_t lst); // Дима Р.
void lst_swap(list_t lst1, list_t lst2); // Вероника
```

## Рекомендации по оформлению кода
 * Разделяйте пробелом управляющие конструкции (if/while/for) и скобку. Пробелы между круглыми скобками и их содержимым не ставьте. Открывающая фигурная скобка должна быть в конце строки после закрывающей круглой скобки и пробела. Всегда, когда это возможно, пишите составную инструкцию. Так будет проще модифицировать код, например, добавлять ещё какие-то действия.
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
 * Имена типов, функций, переменных и пр. пишутся в нижнем регистре, имена макросов-констант — заглавными буквами. Слова разделяются нижним подчёркиванием. Имена, которые попадают в глобальную область видимости, предварять префиксом ```lst_```.
