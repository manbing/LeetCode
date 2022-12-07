struct node {
	int value;
	int pos;
};

int minimumSwaps(int *nums, int numsSize)
{
	int i = 0;
	struct node min = { 0 }, max = { 0 };

	min.value = INT_MAX;
	max.value = INT_MIN;

	for (i = 0; i < numsSize; i++) {
		if (nums[numsSize - i - 1] > max.value) {
			max.value = nums[numsSize - i - 1];
			max.pos = numsSize - i - 1;
		}

		if (nums[i] < min.value) {
			min.value = nums[i];
			min.pos = i;
		}
	}

	return min.pos + (numsSize - (max.pos + 1)) +
	       ((min.pos > max.pos) ? -1 : 0);
}
