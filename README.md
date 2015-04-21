# Двунаправленный список (учебный проект)
Этот проект выполнен в рамках учебного курса "Основы программирования".

## Список типов
```c
list_t
lst_elem_t
lst_iter_t
```

## Список функций
```c
int lst_new(list_t* p);
void lst_delete(list_t lst);
int lst_append(list_t lst, elem_t el);
int lst_insert_after(lst_iter_t it, elem_t el);
void lst_remove(lst_iter_t it);
lst_iter_t lst_iter_by_index(list_t lst, size_t i);
lst_elem_t lst_index(list_t lst, size_t i);
void lst_erase(list_t lst);
```

## Список алгоритмов
```c
lst_iter_t lst_binsearch(list_t lst, lst_elem_t val);
size_t lst_count(list_t lst, lst_elem_t val);
list_t lst_copy(list_t lst);
int lst_compare(list_t lst1, list_t lst2);
lst_iter_t lst_find(list_t lst, lst_elem_t val);
void lst_for_each(list_t lst, lst_elem_t (*f)(lst_elem_t));
lst_elem_t lst_max(list_t lst);
lst_elem_t lst_min(list_t lst);
void lst_random_shuffle(list_t lst);
int lst_replace(list_t lst, lst_elem_t from, lst_elem_t to);
int lst_remove(list_t lst, lst_elem_t val);
void lst_sort(list_t lst);
void lst_swap(list_t lst1, list_t lst2);
```
