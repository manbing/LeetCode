/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **buffer = NULL;
int *element_size = NULL;
int buff_num = 0;
int *stack = NULL;
int stack_index = -1;

static void push(int value)
{
	stack_index++;
	if (stack_index >= 0)
		*(stack + stack_index) = value;
}

static void pop()
{
	if (stack_index >= 0)
		stack_index--;
}

static void copy()
{
	buff_num++;
	buffer = (int **)realloc(buffer, buff_num * sizeof(int *));
	element_size = (int *)realloc(element_size, buff_num * sizeof(int));

	*(element_size + buff_num - 1) = stack_index + 1;

	if (stack_index >= 0) {
	*(buffer + buff_num - 1) = (int *)calloc(stack_index + 1, sizeof(int));
	memcpy(*(buffer + buff_num - 1), stack,
	       (stack_index + 1) * sizeof(int));
	}
}

static void __get_all_subsets(int *nums, int numsSize, int index)
{
	if (index == numsSize)
		return;

	__get_all_subsets(nums, numsSize, index + 1);
	push(*(nums + index));
	copy();
	__get_all_subsets(nums, numsSize, index + 1);
	pop();
}

int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	buffer = NULL;
	element_size = NULL;
	buff_num = 0;
	stack = NULL;
	stack_index = -1;

	stack = (int *)calloc(numsSize, sizeof(int));
	copy();
	__get_all_subsets(nums, numsSize, 0);
	*returnSize = buff_num;
	*returnColumnSizes = element_size;
	return buffer;
}

int main(void)
{
	int **retval = NULL;
	int nums[] = { 1, 2, 3 };
	int nums_size = 0;
	int *nums_size2 = NULL;
	int i = 0, j = 0;

	retval = subsets(nums, sizeof(nums) / sizeof(nums[0]), &nums_size,
			 &nums_size2);

	for (i = 0; i < nums_size; i++) {
		printf("{");
		for (j = 0; j < *(nums_size2 + i); j++) {
			printf("%d, ", *(*(retval + i) + j));
		}
		printf("}\n");
	}

	return 0;
}
