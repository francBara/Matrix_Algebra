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
