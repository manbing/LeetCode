/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define START_POSITION 0
#define END_POSITION 1

static void find_start_end(int *nums, int left, int right, int target,
			   int *retval)
{
	int mid = (left + right) / 2;

	if (nums[mid] <= target && mid + 1 <= right) {
		find_start_end(nums, mid + 1, right, target, retval);
	}

	if (nums[mid] >= target && left <= mid - 1) {
		find_start_end(nums, left, mid - 1, target, retval);
	}

	if (nums[mid] == target) {
		if (retval[START_POSITION] == -1)
			retval[START_POSITION] = mid;

		if (retval[END_POSITION] == -1)
			retval[END_POSITION] = mid;

		if (retval[START_POSITION] > mid)
			retval[START_POSITION] = mid;

		if (retval[END_POSITION] < mid)
			retval[END_POSITION] = mid;
	}
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
	int *retval = (int *)calloc(2, sizeof(int));
	int start = -1, end = -1;

	*returnSize = 2;
	retval[0] = -1;
	retval[1] = -1;

	if (numsSize > 0)
		find_start_end(nums, 0, numsSize - 1, target, retval);

	return retval;
}
