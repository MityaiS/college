#include <stdlib.h>
#include <stdio.h>

short HandleRow(int *row, int c, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (c <= row[i])
		{
			return 1;
		}
	}
	return 0;
}

short HandleMatrix(int **matrix, int *arr, int size)
{
	short flag = 1;
	for (int i = 0; i < size; ++i)
	{
		flag = HandleRow(matrix[i], arr[i], size);
		if (flag)
		{
			return flag;
		}
	}
	return 0;
}

int WriteFile(const char *fileName, int *arr, int size)
{
	FILE *file;
	file = fopen(fileName, "w");
	if (!file)
	{
		printf("File isn't opened!\n");
		return -1;
	}
	for (int i = 0; i < size; ++i)
	{
		fprintf(file, "%d ", arr[i]);
	}

	fclose(file);
}

void FreeMemory(int **matrix, int *result, int size)
{
	for (int i = 0; i < size; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
	free(result);
}

int GetMinElement(int *arr, int size)
{
	int min = *arr;
	for (int i = 1; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

void ChangeArray(int **matrix, int *arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = GetMinElement(matrix[i], size);
	}
}

short MainTask(int **matrix, int *arr, int size)
{
	if (HandleMatrix(matrix, arr, size))
	{
		return 1;
	}
	ChangeArray(matrix, arr, size);
	return 0;
}