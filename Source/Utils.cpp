#include "Utils.h"

bool isIn(int arr[], int size, int num)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (num == arr[i])
			return true;
	}
	return false;
}

int mcm(int n1, int n2)
{
	if (n1 == n2)
		return n1;
	else if (n1 % n2 == 0)
		return n1;
	else if (n2 % n1 == 0)
		return n2;
	else
		return n1 * n2;
}

int mcd(int n1, int n2)
{
	if (n1 == n2)
		return n1;
	if (n1 % n2 == 0)
		return n2;
	if (n2 % n1 == 0)
		return n1;
	if (n1 % 11 == 0 && n2 % 11 == 0)
		return 11;
	if (n1 % 7 == 0 && n2 % 7 == 0)
		return 7;
	if (n1 % 5 == 0 && n2 % 5 == 0)
		return 5;
	if (n1 % 3 == 0 && n2 % 3 == 0)
		return 3;
	if (n1 % 2 == 0 && n2 % 2 == 0)
		return 2;
	return 1;
}
