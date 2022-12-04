/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int cmp(char *new_s, char *old_s)
{
	int retval = 0, i = 0, j = 0;
	int s_size = 0, s2_size = 0, largest_size = 0;
	int s_is_digital = 1, s2_is_digital = 1;
	long tmp, tmp2;
	char *saveptr = NULL;
	char *token = NULL;
	char *s_token[100] = { 0 }, *s2_token[100] = { 0 };
	char *endptr, *endptr2;
	char s[100] = { 0 }, s2[100] = { 0 };

	if (!new_s || !old_s)
		return -1;

	snprintf(s, sizeof(s), "%s", new_s);
	snprintf(s2, sizeof(s2), "%s", old_s);

	saveptr = s;
	while ((token = strtok_r(saveptr, " ", &saveptr))) {
		s_token[s_size++] = token;
	}

	saveptr = s2;
	while ((token = strtok_r(saveptr, " ", &saveptr))) {
		s2_token[s2_size++] = token;
	}

	// 1. The letter-logs come before all digit-logs.
	tmp = strtol(s_token[1], &endptr, 10);
	if (s_token[1] == endptr)
		s_is_digital = 0;

	tmp2 = strtol(s2_token[1], &endptr2, 10);
	if (s2_token[1] == endptr2)
		s2_is_digital = 0;

	if (!s_is_digital && s2_is_digital)
		return -1;
	else if (s_is_digital && !s2_is_digital)
		return 1;

	// 3. The digit-logs maintain their relative ordering.
	if (s_is_digital && s_is_digital)
		return 1;

	// 2. The letter-logs are sorted lexicographically by their contents. If their contents are the same, then sort them lexicographically by their identifiers.
	largest_size = (s_size > s2_size) ? s_size : s2_size;
	for (i = 1; i < largest_size; i++) {
		if (!s_token[i])
			return -1;

		if (!s2_token[i])
			return 1;

		if (strcmp(s_token[i], s2_token[i]) < 0) {
			return -1;
		} else if (strcmp(s_token[i], s2_token[i]) > 0) {
			return 1;
		}
	}

	if (strcmp(s_token[0], s2_token[0]) <= 0)
		return -1;

	return 0;
}

void insert(char *log, char **table, int table_size, int pos)
{
	char **src = &table[pos];
	char **dest = &table[pos + 1];
	char *tmp[100] = { 0 };

	memcpy(tmp, src, sizeof(char *) * (table_size - pos));
	memcpy(dest, tmp, sizeof(char *) * (table_size - pos));
	table[pos] = log;
}

char **reorderLogFiles(char **logs, int logsSize, int *returnSize)
{
	int i = 0, j = 0, size = 0;
	char **retval = (char **)calloc(logsSize, sizeof(char *));

	for (i = 0; i < logsSize; i++) {
		for (j = 0; j < logsSize; j++) {
			if (cmp(logs[i], retval[j]) < 0) {
				insert(logs[i], retval, size, j);
				size++;
				break;
			}
		}
	}

	*returnSize = size;
	return retval;
}
