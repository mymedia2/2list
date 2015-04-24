#include <stdio.h>
#include "list.h"

int main() {
    list_t L;
    int i;

    lst_new(&L);
    for (i = 0; i < 93; i++) {
        lst_append(L, i);
    }
    printf("%zd\n", lst_size(L));
    lst_swap_d(L,1,2);
    lst_swap_d(L,3,90);
    
    
    lst_iter_t p;
    for (p = lst_iter_first(L); !lst_iter_is_null(p); p = lst_iter_next(p)) {
        printf("%ld ", lst_iter_deref(p));
               printf("\n");
    }
    printf("\n");

    lst_free(L);

    return 0;
}
