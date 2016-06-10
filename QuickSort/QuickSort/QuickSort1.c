#include <stdio.h>

int g_nums[] = { 1,5,1,1,6,4 };

void swap(int* nums, int a, int b) {
	int temp = nums[a];
	nums[a] = nums[b];
	nums[b] = temp;
}

void QuickSort1(int* nums, int l, int u) {
	int i, m;
	m = l;

	if (l >= u) return;

	for (i = l + 1; i <= u; i++) {
		if (nums[i] < nums[l]) {
			swap(nums, ++m, i);
		}
	}
	swap(nums, l, m);

	QuickSort1(nums, l, m - 1);
	QuickSort1(nums, m + 1, u);
}

int main()
{
	QuickSort1(g_nums, 0, sizeof(g_nums)/sizeof(g_nums[0]) - 1);

	return 0;
}

