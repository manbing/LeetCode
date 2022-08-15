#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
static char dictionary[8][5] = { { 'a', 'b', 'c' }, { 'd', 'e', 'f' },
				 { 'g', 'h', 'i' }, { 'j', 'k', 'l' },
				 { 'm', 'n', 'o' }, { 'p', 'q', 'r', 's' },
				 { 't', 'u', 'v' }, { 'w', 'x', 'y', 'z' } };

static char **__letterCombinations(char **output, char *digits, int *count,
				   char *buffer, int length)
{
	if (digits[0] == '\0')
		return NULL;
	else if (digits[length] == '\0') {
		int tmp = *count;

		buffer[length] = '\0';
		output = realloc(output, (tmp + 1) * sizeof(char *));
		output[tmp] = strdup(buffer);
		*count += 1;
	} else {
		int dict_index = digits[length] - '2';
		int i = 0;

		for (i = 0; dictionary[dict_index][i] > 0; i++) {
			buffer[length] = dictionary[dict_index][i];
			output = __letterCombinations(output, digits, count,
						      buffer, length + 1);
		}
	}

	return output;
}

char **letterCombinations(char *digits, int *returnSize)
{
	char buffer[5] = { 0 };
	char **output = NULL;

	*returnSize = 0;

	return __letterCombinations(output, digits, returnSize, buffer, 0);
}

int main(void)
{
	char *digits = "23";
	int returnSize = 0;
	int i = 0;
	char **output = NULL;

	output = letterCombinations(digits, &returnSize);

	printf("returnSize = %d\n", returnSize);
	for (i = 0; i < returnSize; i++) {
		printf("%s\n", output[i]);
	}

	return 0;
}
