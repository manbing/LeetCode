static inline void swap(int *a, int *b)
{
	int tmp = 0;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void tanspose(int **matrix, int row, int col)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < row; i++) {
		for (j = i; j < col; j++) {
			int *target = (*(matrix + i) + j);
			int *target2 = (*(matrix + j) + i);
			swap(target, target2);
		}
	}
}

static void mirror(int **matrix, int row, int col)
{
	int i = 0;
	int j = 0;
	int mid = col / 2;

	for (i = 0; i < row; i++) {
		for (j = 0; j < col / 2; j++) {
			int *target = (*(matrix + i) + j);
			int *target2 = (*(matrix + i) + (col - j - 1));
			swap(target, target2);
		}
	}
}

void rotate(int **matrix, int matrixSize, int *matrixColSize)
{
	tanspose(matrix, matrixSize, *matrixColSize);
	mirror(matrix, matrixSize, *matrixColSize);
}
