typedef bool uint1_t;

static bool get_next_value(int **board, int row_size, int col_size, int i,
			   int j)
{
	int live = 0, die = 0;

	if ((i - 1) >= 0 && (j - 1) >= 0)
		live += (*(*(board + i - 1) + (j - 1)) & 1) ? 1 : 0;

	if ((i - 1) >= 0)
		live += (*(*(board + i - 1) + (j)) & 1) ? 1 : 0;

	if ((i - 1) >= 0 && (j + 1) < col_size)
		live += (*(*(board + i - 1) + (j + 1)) & 1) ? 1 : 0;

	if ((j - 1) >= 0)
		live += (*(*(board + i) + (j - 1)) & 1) ? 1 : 0;

	if ((j + 1) < col_size)
		live += (*(*(board + i) + (j + 1)) & 1) ? 1 : 0;

	if ((i + 1) < row_size && (j - 1) >= 0)
		live += (*(*(board + i + 1) + (j - 1)) & 1) ? 1 : 0;

	if ((i + 1) < row_size)
		live += (*(*(board + i + 1) + (j)) & 1) ? 1 : 0;

	if ((i + 1) < row_size && (j + 1) < col_size)
		live += (*(*(board + i + 1) + (j + 1)) & 1) ? 1 : 0;

	if (*(*(board + i) + (j))) {
		if (live < 2)
			return false;
		else if (live == 2 || live == 3)
			return true;
		else if (live > 3)
			return false;
	} else {
		if (live == 3)
			return true;
		else
			return false;
	}

	return false;
}

void gameOfLife(int **board, int boardSize, int *boardColSize)
{
	int i = 0, j = 0;
	int col_size = *boardColSize;
	uint1_t value = 0;

	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < col_size; j++) {
			value = get_next_value(board, boardSize, col_size, i,
					       j);
			*(*(board + i) + j) += value << 1;
		}
	}

	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < col_size; j++) {
			value = *(*(board + i) + j) & (1 << 1);
			*(*(board + i) + j) = value;
		}
	}
}
