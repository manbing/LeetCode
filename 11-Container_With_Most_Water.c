#define MIN(x, y) (x) < (y) ? (x) : (y)
#define MAX(x, y) (x) > (y) ? (x) : (y)

int maxArea(int *height, int heightSize)
{
	int left = 0, right = heightSize - 1;
	int retval = 0;
	int size = 0;
	int volume = 0;

	for (size = heightSize - 1; size > 0; size--) {
		volume = (MIN(height[left], height[right])) * size;
		retval = MAX(retval, volume);

		if (height[left] < height[right])
			left++;
		else
			right--;
	}

	return retval;
}
