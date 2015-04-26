#include <stdio.h>

static char heap[512][32];
static unsigned short ex = 0;

extern void* malloc(size_t b) {
	fprintf(stderr, "Вызван malloc(%zd)\n", b);
	if (b > 512) return NULL;
	return heap[ex++];
}

extern void free(void* t) {
	fprintf(stderr, "Вызван free(%p)\n", t);
}
