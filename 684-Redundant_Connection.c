struct vertice {
	bool visited;
	struct vertice **next;
};

static bool __check_cyclic(struct vertice *root, struct vertice *vertice)
{
	bool retval = false;
	int i = 0;

	vertice->visited = true;

	for (i = 0; vertice->next[i]; i++) {
		if (!(vertice->next[i])->visited)
			retval |= __check_cyclic(vertice, vertice->next[i]);
		else if (root != vertice->next[i])
			return true;
	}
	return retval;
}

static bool check_cyclic(struct vertice *vertices, size_t size, int *edge)
{
	int i = 0, x = edge[0] - 1, y = edge[1] - 1;

	for (i = 0; vertices[x].next[i]; i++) {
	}
	vertices[x].next[i] = &vertices[y];

	for (i = 0; vertices[y].next[i]; i++) {
	}
	vertices[y].next[i] = &vertices[x];

	//reinit
	for (i = 0; i < size; i++) {
		vertices[i].visited = false;
	}

	return __check_cyclic(NULL, &vertices[x]);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findRedundantConnection(int **edges, int edgesSize, int *edgesColSize,
			     int *returnSize)
{
	int i = 0;
	struct vertice *vertices = NULL;
	int *retval = NULL;

	//init
	vertices = (struct vertice *)calloc(edgesSize, sizeof(struct vertice));
	for (i = 0; i < edgesSize; i++) {
		vertices[i].next = (struct vertice *)calloc(
			edgesSize, sizeof(struct vertice));
	}

	//do
	for (i = 0; i < edgesSize; i++) {
		if (check_cyclic(vertices, edgesSize, edges[i])) {
			retval = (int *)calloc(2, sizeof(int));
			retval[0] = edges[i][0];
			retval[1] = edges[i][1];
			*returnSize = 2;
			break;
		}
	}

	//free
	for (i = 0; i < edgesSize; i++) {
		free(vertices[i].next);
	}
	free(vertices);

	return retval;
}
