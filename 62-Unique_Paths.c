static int **map = NULL;

static int __uniquePaths(int m, int n)
{
	int *target = (*(map + m - 1) + n - 1);

	if (n == 1 || m == 1)
		return 1;

	if (!(*target))
		*target = __uniquePaths(m - 1, n) + __uniquePaths(m, n - 1);

	return *target;
}

int uniquePaths(int m, int n)
{
	int i = 0;
	map = (int **)calloc(m, sizeof(int *));

	for (i = 0; i < m; i++) {
		map[i] = (int *)calloc(n, sizeof(int));
	}

	return __uniquePaths(m, n);
}
