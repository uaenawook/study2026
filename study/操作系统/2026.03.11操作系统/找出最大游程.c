//找出最大游程即：同一个数字连续出现的最大次数
#include<stdio.h>
int main()
{
	int arr[] = {2,3,2,7,7,3,6,6,6,6,4,7,9,2,2,2,1 };
	int arrSize = sizeof(arr) / sizeof(int);
	int New, val, len, MaxLen;
	val = arr[0];
	len = 1;
	MaxLen = 1;
	for (int i = 1; i < arrSize; i++)
	{
		New = arr[i];
		if (val == New)
		{
			len++;
		}
		else {
			len = 1;
			val = New;
		}
		if (len > MaxLen)
		{
			MaxLen = len;
		}
	}
	printf("%d\n", MaxLen);
	return 0;
}