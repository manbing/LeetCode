#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

struct node {
	char alphabet;
	unsigned int number;
	int priority;
};

struct max_heap {
	int size;
	struct node *root;
};

void swap(struct node *a, struct node *b)
{
	struct node tmp;

	memcpy(&tmp, a, sizeof(struct node));
	memcpy(a, b, sizeof(struct node));
	memcpy(b, &tmp, sizeof(struct node));
}

void heapify(struct max_heap *heap, int i)
{
	int l = LCHILD(i);
	int r = RCHILD(i);
	int largest = i;

	if (l < heap->size && heap->root[l].priority > heap->root[largest].priority)
		largest = l;

	if (r < heap->size && heap->root[r].priority > heap->root[largest].priority)
		largest = r;

	if (largest != i) {
		swap(&heap->root[i], &heap->root[largest]);
		heapify(heap, largest);
	}
}

void build_max_heap(struct max_heap *heap)
{
	int i  = 0;

	for (i = heap->size; i >= 0; i--) {
		heapify(heap, i);
	}
}

void show_heap(struct max_heap *heap)
{
	int i = 0;

	printf("[%s:%d]\n", __func__, __LINE__);
	printf("%d\n", heap->size);
	for (i = 0; i < heap->size; i++) {
		printf("%c\n", heap->root[i].alphabet);
		printf("priority = %d\n", heap->root[i].priority);
		printf("number = %d\n", heap->root[i].number);
		printf("\n");
	}

	printf("[%s:%d]\n", __func__, __LINE__);
}

char *reorganizeString(char *s)
{
	int length = 0, i = 0, j = 0;
	char *tmp = s, *retval = NULL;
	struct max_heap heap;

	memset(&heap, 0, sizeof(struct max_heap));
	
	while (*tmp != '\0') {
		length++;

		for (i = 0; i < heap.size; i++) {
			if (heap.root && heap.root[i].alphabet == *tmp) {
				heap.root[i].number++;
				heap.root[i].priority++;
				break;
			}
		}

		if (i == heap.size ) {
			heap.size++;
			heap.root = (struct node *)realloc(heap.root, (1 + heap.size) * sizeof(struct node));

			heap.root[i].alphabet = *tmp;
			heap.root[i].number++;
			heap.root[i].priority++;
		}

		tmp++;
	}

	build_max_heap(&heap);

	retval = (char *)calloc(length + 1, sizeof(char)); 

	j = 0;
	for (i = 1; i < heap.size; i++) {
		j += heap.root[i].number;
	}

	if (heap.root[0].number - 1 > j)
		return retval;

	j = 0;
	for (i = 0; i < heap.size; i++) {
		while (heap.root[i].number > 0) {
			retval[j] = heap.root[i].alphabet;
			heap.root[i].number--;
			
			j += 2;

			if (j >= length)
				j = 1;
		}
	}


	return retval;
}

int main(void)
{
	char *input = "xxxyyyyz";

	printf("intput = %s\n", input);
	printf("output = %s\n", reorganizeString(input));

	return 0;
}
