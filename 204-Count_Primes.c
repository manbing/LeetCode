#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef MALLOC_IN_ARRAY
static int *head = NULL;
static int prime_size = 0;
#else
struct prime {
	int value;
	struct prime *next;
};

static struct prime *head = NULL;
static struct prime *tail = NULL;
#endif

static bool is_prime(int n)
{
	int i = 0;
	int half = n / 2;

	if (n <= 1)
		return false;

#ifdef MALLOC_IN_ARRAY
	for (i = 0; i < prime_size && head[i] <= half; i++) {
		if (!(n % head[i]))
			return false;
	}
#else
	struct prime *tmp = head;

	while (tmp && tmp->value <= half) {
		if (!(n % tmp->value))
			return false;

		tmp = tmp->next;
	}
#endif

	return true;
}

static void stash(int p)
{
#ifdef MALLOC_IN_ARRAY
	head = (int *)realloc(head, ++prime_size * sizeof(int));
	head[prime_size - 1] = p;
#else
	struct prime *tmp = (struct prime *)calloc(1, sizeof(struct prime));
	tmp->next = NULL;
	tmp->value = p;

	if (!head)
		head = tail = tmp;
	else {
		tail->next = tmp;
		tail = tmp;
	}
#endif
}

static void release()
{
#ifdef MALLOC_IN_ARRAY
	if (head) {
		free(head);
		head = NULL;
		prime_size = 0;
	}
#else
	if (head) {
		struct prime *tmp;

		tmp = head->next;
		free(head);
		while (tmp) {
			head = tmp;
			tmp = head->next;
			free(head);
		}

		head = NULL;
	}
#endif
}

int countPrimes(int n)
{
	int retval = 0;
	int i = 0;

	for (i = 0; i < n; i++) {
		if (is_prime(i)) {
			stash(i);
			retval += 1;
		}
	}

	//release();
	return retval;
}

int main(void)
{
	int input = 499979;

	printf("%d ->  %d\n", input, countPrimes(input));

	return 0;
}
