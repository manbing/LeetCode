int min(int a, int b)
{
	return (a > b) ? b : a;
}

int coinChange(int *coins, int coinsSize, int amount)
{
	int *dp = (int *)calloc(amount + 1, sizeof(int));
	int i = 0, j = 0;

	for (i = 1; i <= amount; i++)
		*(dp + i) = INT_MAX;

	for (i = 0; i <= amount; i++) {
		for (j = 0; j < coinsSize; j++) {
			int tmp = i - *(coins + j);
			int *target = dp + i;
			if (tmp >= 0) {
				*target =
					min(*target, (*(dp + tmp) >= INT_MAX) ?
							     INT_MAX :
							     *(dp + tmp) + 1);
			}
		}
	}

	return (dp[amount] == INT_MAX) ? -1 : dp[amount];
}
