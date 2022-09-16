#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#ifdef ARRAY
static int *head = NULL;
static int prime_size = 0;
#elif LINKED_LIST
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

        return true;
}

static void stash(int p)
{
#ifdef ARRAY
        ++prime_size;
        head[prime_size - 1] = p;
#elif LINKED_LIST
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

        return retval;
}

int main(void)
{
        int input = 499979;
#ifdef ARRAY
        head = (int *)realloc(head, INT_MAX * sizeof(int));
#endif
        printf("%d ->  %d\n", input, countPrimes(input));

        return 0;
}
